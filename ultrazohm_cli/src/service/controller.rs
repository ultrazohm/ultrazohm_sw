//! Persistent control endpoint with replaceable acquisition sessions.
use super::*;
use crate::profile::ChannelMapping;
use std::collections::VecDeque;
use std::io::{Read, Seek, SeekFrom, Write};

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
    let service_id = config
        .launch_id
        .clone()
        .unwrap_or_else(|| format!("{}-{}", now_ns(), std::process::id()));
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
    let mut shutdown_started = false;
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
                    let error = replacement
                        .reconnect_error
                        .clone()
                        .or_else(|| replacement.context.state.lock().unwrap().error.clone());
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
                    let message = format!("Firmware job {} failed: {e:#}", job.id);
                    eprintln!("{message}");
                    if let Err(log_error) = fs::OpenOptions::new()
                        .append(true)
                        .open(&job.log)
                        .and_then(|mut file| {
                            writeln!(file, "{message}").and_then(|_| file.sync_all())
                        })
                    {
                        eprintln!("Could not persist firmware failure: {log_error}");
                    }
                    if shutdown.load(Ordering::SeqCst) {
                        finalization_error = Some(message);
                    }
                    last_error = Some(format!("{e:#}"));
                    json!({"ok":false,"error":format!("{e:#}")})
                }
            });
            *job.phase.lock().unwrap() = "complete".into();
        }
        let busy = cleanup.is_some() || jobs.back().is_some_and(|j| j.worker.is_some());
        if shutdown.load(Ordering::SeqCst) && !shutdown_started {
            shutdown_started = true;
            stop_requested.store(true, Ordering::SeqCst);
            if let Some(s) = session.as_mut() {
                if s.connection.is_some() && !s.shutdown_stop_sent {
                    s.stop_device();
                    s.shutdown_stop_sent = true;
                }
                s.context.shutdown.store(true, Ordering::SeqCst);
            }
        }
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
            config = snapshot_config(&old);
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
                            && crate::preferences::resolve_xsct(
                                config.xsct.as_deref(),
                                config.repo.as_deref()
                            )
                            .is_ok()
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
                Operation::Shutdown | Operation::OwnedShutdown { .. } => {
                    if let Operation::OwnedShutdown {
                        service_id: expected,
                    } = &pending.request.command
                    {
                        ensure!(expected == &service_id, "service identity mismatch");
                    }
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
                    let xsct = crate::preferences::resolve_xsct(
                        config.xsct.as_deref(),
                        config.repo.as_deref(),
                    )?;
                    let headers = crate::header_mapping::HEADERS
                        .iter()
                        .map(|p| fs::read(repo.join(p)).ok())
                        .collect::<Vec<_>>();
                    let firmware_mapping = if action == "flash" {
                        Some(ChannelMapping::load_repository(None, Some(&repo))?)
                    } else {
                        None
                    };
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
                        next = snapshot_config(s);
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
                        let cleanup_target = next.device.clone();
                        let mut programming_attempted = false;
                        let mut programmed_profile = None;
                        let result = (|| -> Result<Option<Session>> {
                            let build_action = if action_copy == "flash" {
                                "build"
                            } else {
                                &action_copy
                            };
                            *worker_phase.lock().unwrap() = build_action.into();
                            crate::vitis::execute(
                                build_action,
                                Some(&repo),
                                None,
                                Some(&output),
                                Some(&xsct),
                            )?;
                            if action_copy != "flash" {
                                return Ok(None);
                            }
                            ensure!(
                                headers
                                    == crate::header_mapping::HEADERS
                                        .iter()
                                        .map(|p| fs::read(repo.join(p)).ok())
                                        .collect::<Vec<_>>(),
                                "firmware headers changed during build; programming was not started"
                            );
                            let mapping =
                                firmware_mapping.expect("flash mapping validated before build");
                            let (profile, removed) = next.profile.remap(mapping)?;
                            next.profile = profile;
                            ensure!(
                                !worker_shutdown.load(Ordering::SeqCst),
                                "shutdown requested before programming"
                            );
                            *worker_phase.lock().unwrap() = "programming".into();
                            programming_attempted = true;
                            crate::vitis::execute(
                                "program-built",
                                Some(&repo),
                                Some("Run_UltraZohm"),
                                Some(&output),
                                Some(&xsct),
                            )?;
                            ensure!(
                                headers
                                    == crate::header_mapping::HEADERS
                                        .iter()
                                        .map(|p| fs::read(repo.join(p)).ok())
                                        .collect::<Vec<_>>(),
                                "firmware headers changed during programming"
                            );
                            // Only a successful programming operation with unchanged inputs
                            // establishes which mapping may be used for subsequent cleanup.
                            programmed_profile = Some(next.profile.clone());
                            *worker_phase.lock().unwrap() = "loading_configuration".into();
                            use std::io::Write;
                            let mut output = &output;
                            writeln!(
                                output,
                                "Removed channel assignments: {}",
                                serde_json::to_string(&removed)?
                            )?;
                            next.output =
                                Some(replacement_output(next.output.as_deref(), Some(&repo))?);
                            *worker_phase.lock().unwrap() = "reconnecting".into();
                            let target = next.device.take();
                            let mut replacement =
                                Session::new(next, Arc::new(AtomicBool::new(false)))?;
                            replacement.config.device = target.clone();
                            if let Some(target) = target {
                                if !reconnect || worker_shutdown.load(Ordering::SeqCst) {
                                    if worker_stop.load(Ordering::SeqCst)
                                        || worker_shutdown.load(Ordering::SeqCst)
                                    {
                                        let stopped = stop_after_programming(
                                            &target,
                                            &replacement.config.profile,
                                        );
                                        if let Err(error) = stopped {
                                            replacement.reconnect_error = Some(format!(
                                                "Stop after programming failed: {error:#}"
                                            ));
                                        }
                                    }
                                    return Ok(Some(replacement));
                                }
                                let deadline = Instant::now() + Duration::from_secs(20);
                                loop {
                                    match replacement.connect(&target) {
                                        Ok(()) => break,
                                        Err(e) if Instant::now() >= deadline => {
                                            // Connection failure is a job error, not a corrupt recording.
                                            replacement.reconnect_error = Some(format!(
                                                "programming succeeded, reconnect failed: {e:#}"
                                            ));
                                            break;
                                        }
                                        Err(_) => thread::sleep(Duration::from_millis(100)),
                                    }
                                }
                                if replacement.connection.is_some()
                                    && (worker_stop.load(Ordering::SeqCst)
                                        || worker_shutdown.load(Ordering::SeqCst))
                                {
                                    replacement.stop_device();
                                }
                            }
                            Ok(Some(replacement))
                        })();
                        if let Err(error) = result {
                            if programming_attempted && programmed_profile.is_none() {
                                return Err(error.context("Running firmware configuration is unknown; no network Stop sent after programming attempt"));
                            }
                            if let (Some(target), Some(profile)) =
                                (cleanup_target, programmed_profile)
                                && let Err(stop_error) = stop_after_programming(&target, &profile)
                            {
                                return Err(error.context(format!(
                                    "Post-programming Stop failed: {stop_error:#}"
                                )));
                            }
                            return Err(error);
                        }
                        result
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
                    next.output = Some(replacement_output(
                        config.output.as_deref(),
                        config.repo.as_deref(),
                    )?);
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

// The TCP listener may start after XSCT returns. Shutdown must allow the same
// boot window as normal reconnect, without starting acquisition or enabling anything.
fn stop_after_programming(target: &str, profile: &Profile) -> Result<()> {
    let address = target.parse()?;
    let command = encode_command(profile.command("Stop")?, 0.0)?;
    let deadline = Instant::now() + Duration::from_secs(20);
    loop {
        let remaining = deadline.saturating_duration_since(Instant::now());
        if remaining.is_zero() {
            bail!("timed out delivering Stop to {target}");
        }
        let attempt = (|| -> Result<()> {
            let mut socket =
                TcpStream::connect_timeout(&address, remaining.min(Duration::from_secs(3)))?;
            let remaining = deadline.saturating_duration_since(Instant::now());
            ensure!(!remaining.is_zero(), "Stop delivery deadline expired");
            socket.set_write_timeout(Some(remaining.min(Duration::from_secs(3))))?;
            socket.write_all(&command)?;
            Ok(())
        })();
        match attempt {
            Ok(()) => return Ok(()),
            Err(error) if Instant::now() >= deadline => return Err(error),
            Err(_) => thread::sleep(
                deadline
                    .saturating_duration_since(Instant::now())
                    .min(Duration::from_millis(100)),
            ),
        }
    }
}

fn snapshot_config(session: &Session) -> Config {
    let mut config = session.config.clone();
    config.ack = session.context.ack.load(Ordering::SeqCst);
    config.device = session
        .context
        .state
        .lock()
        .unwrap()
        .device
        .clone()
        .or(config.device);
    for (channel, name) in session.selections.as_object().into_iter().flatten() {
        if let (Ok(channel), Some(name)) = (channel.parse(), name.as_str()) {
            config.profile.initial_channels.insert(channel, name.into());
        }
    }
    config
}
