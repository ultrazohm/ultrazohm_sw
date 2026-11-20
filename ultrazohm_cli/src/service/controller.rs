//! Persistent control endpoint with replaceable acquisition sessions.
use super::*;
use crate::profile::ChannelMapping;
use std::collections::VecDeque;
use std::io::{Read, Seek, SeekFrom};

struct Job {
    id: String,
    request_id: String,
    action: String,
    fingerprint: String,
    phase: Arc<Mutex<String>>,
    result: Option<Value>,
    log: PathBuf,
    worker: Option<thread::JoinHandle<Result<Option<Session>>>>,
}
impl Job {
    fn status(&self) -> Value {
        json!({"id":self.id,"request_id":self.request_id,"action":self.action,
            "phase":*self.phase.lock().unwrap(),"state":if self.worker.is_some(){"running"}else if self.result.as_ref().is_some_and(|v|v["ok"]==true){"succeeded"}else{"failed"},"result":self.result})
    }
}

pub(super) fn run(
    mut config: Config,
    shutdown: Arc<AtomicBool>,
    listener: TcpListener,
    ready: impl FnOnce(),
) -> Result<()> {
    let service_id = format!("{}-{}", now_ns(), std::process::id());
    let session_stop = Arc::new(AtomicBool::new(false));
    let mut session = Some(Session::new(config.clone(), session_stop)?);
    let health = Arc::new(Mutex::new(State::default()));
    // Transport lifetime is independent of acquisition and graceful shutdown.
    let transport_stop = Arc::new(AtomicBool::new(false));
    let control = control::ControlServer::new(listener, transport_stop.clone(), health.clone())?;
    let mut jobs: VecDeque<Job> = VecDeque::new();
    let mut last_error: Option<String> = None;
    let mut finalization_error: Option<String> = None;
    let mut configuration_valid = true;
    let stop_requested = Arc::new(AtomicBool::new(false));
    let mut cleanup: Option<thread::JoinHandle<Result<()>>> = None;
    ready();
    loop {
        if transport_stop.load(Ordering::SeqCst) {
            shutdown.store(true, Ordering::SeqCst);
            last_error = health.lock().unwrap().error.clone();
        }
        if cleanup.as_ref().is_some_and(|w| w.is_finished())
            && let Err(e) = cleanup
                .take()
                .unwrap()
                .join()
                .unwrap_or_else(|_| Err(anyhow::anyhow!("session finalization panicked")))
        {
            finalization_error = Some(format!("{e:#}"));
            last_error = Some(format!("{e:#}"));
        }
        if let Some(job) = jobs.back_mut()
            && job.worker.as_ref().is_some_and(|w| w.is_finished())
        {
            let result = job
                .worker
                .take()
                .unwrap()
                .join()
                .unwrap_or_else(|_| Err(anyhow::anyhow!("firmware worker panicked")));
            let result = result.and_then(|replacement| {
                if let Some(mut replacement) = replacement {
                    control.invalidate_session();
                    if (shutdown.load(Ordering::SeqCst) || stop_requested.load(Ordering::SeqCst))
                        && replacement.connection.is_some()
                    {
                        replacement.stop_device();
                    }
                    configuration_valid = true;
                    config = replacement.config.clone();
                    let error = replacement.context.state.lock().unwrap().error.clone();
                    session = Some(replacement);
                    if let Some(error) = error {
                        bail!(error);
                    }
                }
                Ok(())
            });
            job.result = Some(match result {
                Ok(()) => json!({"ok":true}),
                Err(e) => {
                    last_error = Some(format!("{e:#}"));
                    json!({"ok":false,"error":format!("{e:#}")})
                }
            });
            *job.phase.lock().unwrap() = "complete".into();
        }
        let busy = cleanup.is_some() || jobs.back().is_some_and(|j| j.worker.is_some());
        if shutdown.load(Ordering::SeqCst) && !busy {
            if let Some(s) = session.take() {
                s.context.shutdown.store(true, Ordering::SeqCst);
                cleanup = Some(thread::spawn(move || s.finish()));
                continue;
            }
            break;
        }
        if session.as_ref().is_some_and(|s| {
            s.context.shutdown.load(Ordering::SeqCst)
                || s.connection
                    .as_ref()
                    .is_some_and(|c| c.acquisition.is_finished())
        }) {
            let old = session.take().unwrap();
            old.context.shutdown.store(true, Ordering::SeqCst);
            cleanup = Some(thread::spawn(move || old.finish()));
            continue;
        }
        let Some(pending) = control.next(Duration::from_millis(50)) else {
            continue;
        };
        let result = (|| -> Result<Reply> {
            match &pending.request.command {
                Operation::Status => {
                    let mut status = if let Some(s) = session.as_mut() {
                        match s.handle(Request {
                            api_version: API_VERSION,
                            command: Operation::Status,
                        })? {
                            Reply::Json(v) => v,
                            _ => unreachable!(),
                        }
                    } else {
                        ok_reply(json!({"state":{"connected":false}}))
                    };
                    status["service_id"] = json!(service_id);
                    status["session_id"] = json!(session.as_ref().map(|s| &s.run_id));
                    status["output"] =
                        json!(session.as_ref().and_then(|s| s.config.output.as_ref()));
                    status["repository"] = json!(config.repo);
                    status["device_target"] = json!(config.device);
                    status["firmware_available"] = json!(
                        config.repo.is_some()
                            && crate::vitis::selected_xsct(config.xsct.as_deref()).is_ok()
                    );
                    status["active_job"] = jobs
                        .back()
                        .filter(|j| j.worker.is_some())
                        .map_or(Value::Null, Job::status);
                    status["error"] = json!(last_error);
                    status["configuration_valid"] = json!(configuration_valid);
                    status["lifecycle"] = json!(if shutdown.load(Ordering::SeqCst) {
                        "shutting_down"
                    } else if cleanup.is_some() {
                        "finalizing"
                    } else if busy {
                        "firmware_job"
                    } else if session.is_some() {
                        "ready"
                    } else {
                        "disconnected"
                    });
                    status["shutting_down"] = json!(shutdown.load(Ordering::SeqCst));
                    Ok(Reply::Json(status))
                }
                Operation::Jobs => Ok(Reply::Json(ok_reply(
                    json!({"jobs":jobs.iter().map(Job::status).collect::<Vec<_>>()}),
                ))),
                Operation::Job { id, offset } => {
                    let job = jobs.iter().find(|j| &j.id == id).context("unknown job")?;
                    let mut file = fs::File::open(&job.log)?;
                    file.seek(SeekFrom::Start(*offset as u64))?;
                    let mut bytes = Vec::new();
                    file.take(32_768).read_to_end(&mut bytes)?;
                    Ok(Reply::Json(ok_reply(
                        json!({"job":job.status(),"log":String::from_utf8_lossy(&bytes),"next_offset":offset+bytes.len()}),
                    )))
                }
                Operation::Shutdown => {
                    stop_requested.store(true, Ordering::SeqCst);
                    shutdown.store(true, Ordering::SeqCst);
                    if let Some(s) = session.as_mut() {
                        let mut reply = match s.handle(Request {
                            api_version: API_VERSION,
                            command: Operation::Shutdown,
                        })? {
                            Reply::Json(v) => v,
                            _ => unreachable!(),
                        };
                        reply["shutdown_requested"] = json!(true);
                        reply["deferred"] = json!(busy);
                        return Ok(Reply::Json(reply));
                    }
                    Ok(Reply::Json(ok_reply(
                        json!({"shutdown_requested":true,"deferred":busy}),
                    )))
                }
                Operation::Stop => {
                    stop_requested.store(true, Ordering::SeqCst);
                    if let Some(s) = session.as_mut()
                        && s.connection.is_some()
                    {
                        return s.handle(pending.request);
                    }
                    Ok(Reply::Json(ok_reply(json!({"outcome":"disconnected"}))))
                }
                Operation::Firmware {
                    action,
                    request_id,
                    device,
                    no_reconnect,
                } => {
                    let fingerprint = serde_json::to_string(&pending.request.command)?;
                    if let Some(job) = jobs.iter().find(|j| &j.request_id == request_id) {
                        ensure!(
                            job.fingerprint == fingerprint,
                            "request ID already used for another action"
                        );
                        return Ok(Reply::Json(ok_reply(json!({"job":job.status()}))));
                    }
                    ensure!(!shutdown.load(Ordering::SeqCst), "service is shutting down");
                    ensure!(!busy, "another firmware job is running");
                    ensure!(
                        ["generate", "build", "build-clean", "flash"].contains(&action.as_str()),
                        "unsupported firmware action"
                    );
                    ensure!(
                        !request_id.is_empty() && request_id.len() <= 128,
                        "invalid request ID"
                    );
                    let repo =
                        crate::vitis::repository(Some(config.repo.as_ref().context(
                            "service has no firmware checkout; start serve --repo PATH",
                        )?))?;
                    let xsct = crate::vitis::selected_xsct(config.xsct.as_deref())?;
                    let script = std::env::var_os("UZ_CLI_TCL_DIR")
                        .map(PathBuf::from)
                        .unwrap_or_else(|| repo.join("tcl_scripts"))
                        .join("vitis_headless.tcl");
                    ensure!(
                        script.is_file(),
                        "Vitis entry script not found: {}",
                        script.display()
                    );
                    let headers = crate::header_mapping::HEADERS
                        .iter()
                        .map(|p| fs::read(repo.join(p)).ok())
                        .collect::<Vec<_>>();
                    if action == "flash" {
                        ChannelMapping::load_repository(None, Some(&repo))?;
                    }
                    if let Some(device) = device {
                        let _: SocketAddr = device
                            .parse()
                            .context("device must be numeric address:port")?;
                    }
                    let lock_path = repo.join("artifacts");
                    fs::create_dir_all(&lock_path)?;
                    crate::artifacts::ensure_ignore_file(&lock_path)?;
                    let lock = fs::OpenOptions::new()
                        .create(true)
                        .truncate(false)
                        .read(true)
                        .write(true)
                        .open(lock_path.join("firmware.lock"))?;
                    lock.try_lock().context("firmware workspace is in use")?;
                    let id = format!("{}-{}", service_id, now_ns());
                    let log = lock_path.join(format!("firmware-{id}.log"));
                    let output = fs::File::create(&log)?;
                    fs::write(
                        lock_path.join(format!("firmware-{id}.inputs.json")),
                        serde_json::to_vec_pretty(
                            &json!({"service_id":service_id,"request":pending.request,"headers":headers}),
                        )?,
                    )?;
                    let phase = Arc::new(Mutex::new("preparing".to_string()));
                    let worker_phase = phase.clone();
                    let mut next = config.clone();
                    if let Some(s) = session.as_ref() {
                        next.profile = s.config.profile.clone();
                        next.ack = s.context.ack.load(Ordering::SeqCst);
                        next.device = s
                            .context
                            .state
                            .lock()
                            .unwrap()
                            .device
                            .clone()
                            .or(next.device);
                        for (channel, name) in s.selections.as_object().into_iter().flatten() {
                            if let (Ok(channel), Some(name)) = (channel.parse(), name.as_str()) {
                                next.profile.initial_channels.insert(channel, name.into());
                            }
                        }
                    }
                    if let Some(device) = device {
                        next.device = Some(device.clone());
                    }
                    if action == "flash" && !no_reconnect {
                        ensure!(
                            next.device.is_some(),
                            "flash needs a known device, --device ADDRESS:PORT, or --no-reconnect"
                        );
                    }
                    let reconnect = !no_reconnect;
                    let old = if action == "flash" {
                        configuration_valid = false;
                        config = next.clone();
                        control.invalidate_session();
                        session.take()
                    } else {
                        None
                    };
                    stop_requested.store(false, Ordering::SeqCst);
                    let action_copy = action.clone();
                    let worker_stop = stop_requested.clone();
                    let worker_shutdown = shutdown.clone();
                    let worker = thread::spawn(move || -> Result<Option<Session>> {
                        let _lock = lock;
                        if let Some(old) = old {
                            *worker_phase.lock().unwrap() = "finalizing".into();
                            old.context.shutdown.store(true, Ordering::SeqCst);
                            old.finish()?;
                        }
                        if worker_shutdown.load(Ordering::SeqCst) {
                            return Err(coded(
                                "interrupted",
                                "shutdown requested before programming",
                            ));
                        }
                        *worker_phase.lock().unwrap() = action_copy.clone();
                        crate::vitis::execute(
                            &action_copy,
                            Some(&repo),
                            if action_copy == "flash" {
                                Some("Run_UltraZohm")
                            } else {
                                None
                            },
                            Some(&output),
                            Some(&xsct),
                        )?;
                        if action_copy != "flash" {
                            return Ok(None);
                        }
                        *worker_phase.lock().unwrap() = "loading_configuration".into();
                        ensure!(
                            headers
                                == crate::header_mapping::HEADERS
                                    .iter()
                                    .map(|p| fs::read(repo.join(p)).ok())
                                    .collect::<Vec<_>>(),
                            "firmware headers changed during programming; acquisition remains disconnected"
                        );
                        let mapping = ChannelMapping::load_repository(None, Some(&repo))?;
                        let (profile, removed) = next.profile.remap(mapping)?;
                        next.profile = profile;
                        use std::io::Write;
                        let mut output = &output;
                        writeln!(
                            output,
                            "Removed channel assignments: {}",
                            serde_json::to_string(&removed)?
                        )?;
                        next.output = Some(session_output_for_repository(None, Some(&repo))?);
                        *worker_phase.lock().unwrap() = "reconnecting".into();
                        let target = next.device.take();
                        let mut replacement = Session::new(next, Arc::new(AtomicBool::new(false)))?;
                        replacement.config.device = target.clone();
                        if let Some(target) = target {
                            if !reconnect || worker_shutdown.load(Ordering::SeqCst) {
                                if worker_stop.load(Ordering::SeqCst)
                                    || worker_shutdown.load(Ordering::SeqCst)
                                {
                                    let stopped = (|| -> Result<()> {
                                        let mut socket = TcpStream::connect_timeout(
                                            &target.parse()?,
                                            Duration::from_secs(3),
                                        )?;
                                        socket.set_write_timeout(Some(Duration::from_secs(3)))?;
                                        socket.write_all(&encode_command(
                                            replacement.config.profile.command("Stop")?,
                                            0.0,
                                        )?)?;
                                        Ok(())
                                    })();
                                    if let Err(error) = stopped {
                                        replacement.context.state.lock().unwrap().error = Some(
                                            format!("Stop after programming failed: {error:#}"),
                                        );
                                    }
                                }
                                return Ok(Some(replacement));
                            }
                            if let Err(e) = replacement.connect(&target) {
                                replacement.context.state.lock().unwrap().error =
                                    Some(format!("programming succeeded, reconnect failed: {e:#}"));
                            } else if worker_stop.load(Ordering::SeqCst)
                                || worker_shutdown.load(Ordering::SeqCst)
                            {
                                replacement.stop_device();
                            }
                        }
                        Ok(Some(replacement))
                    });
                    last_error = None;
                    jobs.push_back(Job {
                        id,
                        request_id: request_id.clone(),
                        action: action.clone(),
                        fingerprint,
                        phase,
                        result: None,
                        log,
                        worker: Some(worker),
                    });
                    while jobs.len() > 64 {
                        jobs.pop_front();
                    }
                    Ok(Reply::Json(ok_reply(
                        json!({"job":jobs.back().unwrap().status()}),
                    )))
                }
                Operation::Connect { .. } if session.is_none() && !busy => {
                    ensure!(
                        configuration_valid,
                        "firmware configuration is uncertain after failed programming; retry flash or restart with verified configuration"
                    );
                    let mut next = config.clone();
                    next.device = None;
                    next.output =
                        Some(session_output_for_repository(None, config.repo.as_deref())?);
                    session = Some(Session::new(next, Arc::new(AtomicBool::new(false)))?);
                    session.as_mut().unwrap().handle(pending.request)
                }
                _ => {
                    ensure!(!shutdown.load(Ordering::SeqCst), "service is shutting down");
                    let s = session
                        .as_mut()
                        .context("acquisition unavailable; inspect status and firmware job")?;
                    s.handle(pending.request)
                }
            }
        })();
        let _ = pending.reply.send(result);
    }
    let result = if let Some(s) = session {
        s.context.shutdown.store(true, Ordering::SeqCst);
        s.finish()
    } else {
        Ok(())
    };
    transport_stop.store(true, Ordering::SeqCst);
    result.and(control.finish())?;
    if let Some(error) = finalization_error {
        bail!(error);
    }
    Ok(())
}
