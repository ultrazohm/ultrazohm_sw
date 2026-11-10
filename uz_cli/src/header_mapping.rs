//! Read the repository's JavaScope header contract without a C compiler or Vitis.
use crate::profile::{
    ChannelMapping, JavascopeMetadata, PlatformStateMapping, Profile, ProfileSettings,
    ReceiveField, Repository, SendField, SlowSignalType, UserButton,
};
use anyhow::{Context, Result, ensure};
use std::{
    collections::BTreeMap,
    fs,
    path::{Path, PathBuf},
    process::Command,
};

const HEADERS: [&str; 5] = [
    "vitis/software/Baremetal/src/include/javascope.h",
    "vitis/software/Baremetal/src/include/javascope_status.h",
    "vitis/software/shared/APU_RPU_shared.h",
    "vitis/software/FreeRTOS/main.h",
    "vitis/software/FreeRTOS/defines.h",
];

// JavaScope's JavascopeHeaderParser strips comments per line, intentionally
// retaining the entries inside the large visualization-config block comment.
fn clean_line(line: &str) -> String {
    let mut line = line.split("//").next().unwrap_or_default().to_owned();
    while let Some(start) = line.find("/*") {
        if let Some(end) = line[start + 2..].find("*/") {
            line.replace_range(start..start + 2 + end + 2, "");
        } else {
            line.truncate(start);
            break;
        }
    }
    line.chars()
        .filter(|c| !c.is_whitespace())
        .collect::<String>()
        .trim_end_matches([',', ';'])
        .to_owned()
}

fn section(text: &str, start: &str, end: &str) -> Result<Vec<String>> {
    let lines: Vec<_> = text.lines().map(clean_line).collect();
    let starts: Vec<_> = lines
        .iter()
        .enumerate()
        .filter(|(_, line)| *line == start)
        .collect();
    let ends: Vec<_> = lines
        .iter()
        .enumerate()
        .filter(|(_, line)| *line == end)
        .collect();
    ensure!(
        starts.len() == 1 && ends.len() == 1,
        "expected exactly one {start} and {end} marker, found {} and {}",
        starts.len(),
        ends.len()
    );
    let (first, last) = (starts[0].0, ends[0].0);
    ensure!(first < last, "{end} precedes {start}");
    Ok(lines[first..last]
        .iter()
        .filter(|s| !s.is_empty())
        .cloned()
        .collect())
}

/// Omitted display sections are allowed; a present section must be unambiguous and complete.
fn display_section(
    text: &str,
    prefix: &str,
    counts: std::ops::RangeInclusive<usize>,
    identifiers: bool,
) -> Result<Option<Vec<String>>> {
    let start = format!("{prefix}_ZEROVALUE=0");
    let end = format!("{prefix}_ENDMARKER");
    if !text
        .lines()
        .map(clean_line)
        .any(|line| line == start || line == end)
    {
        return Ok(None);
    }
    let entries = section(text, &start, &end)?;
    ensure!(
        counts.contains(&(entries.len() - 1)),
        "{prefix} expected {}..={} entries after the zero marker, found {}",
        counts.start(),
        counts.end(),
        entries.len() - 1
    );
    Ok(Some(
        entries
            .into_iter()
            .skip(1)
            .map(|entry| {
                if identifiers {
                    entry.split('=').next().unwrap().to_owned()
                } else {
                    entry.replace("=0", "") // JavaScope COMPACT_TEXT behavior.
                }
            })
            .collect(),
    ))
}

fn slow_display_name(name: &str) -> String {
    name.replace("JSSD_", "")
        .replace("FLOAT_", "")
        .replace("INT_", "")
}

fn javascope_metadata(
    header: &str,
    labels: &[String],
    slow_signals: &BTreeMap<String, u32>,
) -> Result<JavascopeMetadata> {
    let send_units = display_section(header, "SND_LABELS", 20..=20, false)?;
    let button_labels = display_section(header, "MYBUTTONS_LABELS", 8..=8, false)?;
    let receive_labels = display_section(header, "RCV_FLD", 20..=20, false)?;
    let receive_units = display_section(header, "RCV_LABELS", 20..=20, false)?;
    let display = display_section(header, "SLOWDAT_DISPLAY", 20..=21, true)?;
    let display = display.map(|entries| entries.iter().enumerate().map(|(index, entry)| {
        let normalized = slow_display_name(entry);
        let matches: Vec<_> = slow_signals.keys()
            .filter(|name| slow_display_name(name) == normalized).collect();
        ensure!(matches.len() == 1,
            "SLOWDAT_DISPLAY slot {}: signal {entry:?} has {} matches in JS_SlowData (expected one)",
            index + 1, matches.len());
        Ok((*matches[0]).clone())
    }).collect::<Result<Vec<_>>>()).transpose()?;
    let at =
        |entries: &Option<Vec<String>>, i: usize| entries.as_ref().and_then(|v| v.get(i)).cloned();
    Ok(JavascopeMetadata {
        send_fields: labels
            .iter()
            .skip(1)
            .enumerate()
            .map(|(i, label)| SendField {
                slot: i as u32 + 1,
                command: format!("Set_Send_Field_{}", i + 1),
                label: label.replace("=0", ""),
                unit: at(&send_units, i),
            })
            .collect(),
        buttons: (0..8)
            .map(|i| UserButton {
                slot: i as u32 + 1,
                command: format!("My_Button_{}", i + 1),
                label: at(&button_labels, i),
            })
            .collect(),
        receive_fields: (0..20)
            .map(|i| ReceiveField {
                slot: i as u32 + 1,
                label: at(&receive_labels, i),
                unit: at(&receive_units, i),
                signal: at(&display, i),
            })
            .collect(),
        unused_slow_data_display: display.unwrap_or_default().into_iter().skip(20).collect(),
        slow_signal_types: slow_signals
            .keys()
            .map(|name| (name.clone(), SlowSignalType::from_identifier(name)))
            .collect(),
    })
}

fn identifier(name: &str) -> bool {
    let mut chars = name.chars();
    chars
        .next()
        .is_some_and(|c| c == '_' || c.is_ascii_alphabetic())
        && chars.all(|c| c == '_' || c.is_ascii_alphanumeric())
}

fn number(expression: &str, definitions: &BTreeMap<String, String>, depth: usize) -> Result<u32> {
    ensure!(
        depth < 32,
        "cyclic or excessively nested constant: {expression}"
    );
    if let Some(value) = definitions.get(expression) {
        return number(value, definitions, depth + 1);
    }
    if let Some(inner) = expression
        .strip_prefix("UINT32_C(")
        .and_then(|s| s.strip_suffix(')'))
    {
        return number(inner, definitions, depth + 1);
    }
    if let Some(inner) = expression
        .strip_prefix('(')
        .and_then(|s| s.strip_suffix(')'))
    {
        return number(inner, definitions, depth + 1);
    }
    let literal = expression.trim_end_matches(['u', 'U', 'l', 'L']);
    let (radix, digits) = if let Some(digits) = literal
        .strip_prefix("0x")
        .or_else(|| literal.strip_prefix("0X"))
    {
        (16, digits)
    } else if literal.len() > 1 && literal.starts_with('0') {
        (8, &literal[1..])
    } else {
        (10, literal)
    };
    u32::from_str_radix(digits, radix).with_context(|| format!(
        "unsupported integer expression {expression:?}; use integer literals, UINT32_C, or named constants"))
}

fn enum_table(text: &str, start: &str, end: &str) -> Result<BTreeMap<String, u32>> {
    let mut result = BTreeMap::new();
    let mut definitions = BTreeMap::new();
    let mut next = 0_u32;
    for entry in section(text, start, end)? {
        let (name, value) = match entry.split_once('=') {
            Some((name, value)) => (name, number(value, &definitions, 0)?),
            None => (entry.as_str(), next),
        };
        ensure!(
            identifier(name),
            "invalid enum entry {entry:?}; use one entry per line"
        );
        ensure!(
            result.insert(name.to_owned(), value).is_none(),
            "duplicate enum name {name}"
        );
        definitions.insert(name.to_owned(), value.to_string());
        next = value.checked_add(1).context("enum value overflow")?;
    }
    Ok(result)
}

fn defines(text: &str) -> Result<BTreeMap<String, String>> {
    let mut result = BTreeMap::new();
    for line in text.lines() {
        let line = line.trim();
        let Some(rest) = line
            .strip_prefix('#')
            .map(str::trim_start)
            .and_then(|s| s.strip_prefix("define"))
        else {
            continue;
        };
        if !rest.starts_with(char::is_whitespace) {
            continue;
        }
        let mut fields = rest.trim().splitn(2, char::is_whitespace);
        let name = fields.next().unwrap_or_default();
        let value = clean_line(fields.next().unwrap_or_default());
        if identifier(name) && !value.is_empty() {
            ensure!(
                result.insert(name.to_owned(), value).is_none(),
                "duplicate definition {name}"
            );
        }
    }
    Ok(result)
}

fn git(root: &Path, args: &[&str]) -> Option<String> {
    let output = Command::new("git")
        .arg("-C")
        .arg(root)
        .args(args)
        .output()
        .ok()?;
    output
        .status
        .success()
        .then(|| String::from_utf8_lossy(&output.stdout).trim().to_owned())
}

pub fn generate(root: &Path) -> Result<ChannelMapping> {
    let texts = HEADERS
        .iter()
        .map(|path| match fs::read_to_string(root.join(path)) {
            Ok(text) => Ok(Some(text)),
            Err(error) if *path == HEADERS[1] && error.kind() == std::io::ErrorKind::NotFound => {
                Ok(None)
            }
            Err(error) => Err(error).with_context(|| format!("reading {path}")),
        })
        .collect::<Result<Vec<_>>>()?;
    let header = texts[0].as_deref().unwrap();
    let observables = enum_table(header, "JSO_ZEROVALUE=0", "JSO_ENDMARKER")?;
    let slow_signals = enum_table(header, "JSSD_ZEROVALUE=0", "JSSD_ENDMARKER")?;
    let commands = enum_table(header, "GUI_BTN_ZEROVALUE=0", "GUI_BTN_ENDMARKER")?;
    let labels = section(header, "SND_FLD_ZEROVALUE=0", "SND_FLD_ENDMARKER")?;
    ensure!(
        labels.len() == 21,
        "send-field section must contain the zero marker and 20 labels"
    );
    let mut variables = BTreeMap::new();
    for (index, label) in labels.iter().skip(1).enumerate() {
        let name = label.replace("=0", ""); // JavaScope COMPACT_TEXT behavior.
        let command = format!("Set_Send_Field_{}", index + 1);
        let id = *commands
            .get(&command)
            .with_context(|| format!("missing {command}"))?;
        ensure!(
            !name.is_empty() && variables.insert(name.clone(), id).is_none(),
            "empty or duplicate send-field label {name:?}; variable names must be unique"
        );
    }
    let javascope = Some(javascope_metadata(header, &labels, &slow_signals)?);
    let platform_state = if let Some(status_header) = &texts[1] {
        let status_defines = defines(status_header)?;
        let mask = number("JAVASCOPE_PLATFORM_STATE_MASK", &status_defines, 0)?;
        let shift = mask.trailing_zeros();
        ensure!(
            shift <= 30 && mask == (3_u32 << shift),
            "platform-state mask must select two adjacent bits"
        );
        let mut values = BTreeMap::new();
        for name in status_defines.keys().filter(|name| {
            name.starts_with("JAVASCOPE_PLATFORM_")
                && name.as_str() != "JAVASCOPE_PLATFORM_STATE_MASK"
        }) {
            let bits = number(name, &status_defines, 0)?;
            ensure!(
                bits & !mask == 0,
                "{name} sets bits outside the platform-state mask"
            );
            let label = name
                .trim_start_matches("JAVASCOPE_PLATFORM_")
                .to_ascii_lowercase();
            ensure!(
                values.insert(bits >> shift, label).is_none(),
                "duplicate platform-state code in {name}"
            );
        }
        let platform_state = PlatformStateMapping {
            mask,
            shift,
            values,
        };
        platform_state.validate()?;
        Some(platform_state)
    } else {
        None
    };
    let mut geometry = BTreeMap::new();
    for text in &texts[2..] {
        for (name, value) in defines(text.as_deref().unwrap())? {
            ensure!(
                geometry.insert(name.clone(), value).is_none(),
                "duplicate definition {name}"
            );
        }
    }
    let mut commit = git(root, &["rev-parse", "HEAD"]).unwrap_or_else(|| "unknown".into());
    let mut status_args = vec!["status", "--porcelain", "--"];
    status_args.extend(HEADERS);
    if git(root, &status_args).is_some_and(|status| !status.is_empty()) {
        commit.push_str("-dirty");
    }
    let mapping = ChannelMapping {
        api_version: 1,
        name: "generated-javascope".into(),
        repository: Repository {
            name: "ultrazohm/ultrazohm_sw".into(),
            commit,
        },
        channels: number("JS_CHANNELS", &geometry, 0)? as usize,
        samples_per_packet: number("NETWORK_SEND_FIELD_SIZE", &geometry, 0)? as usize,
        observables,
        slow_signals,
        variables,
        commands,
        javascope,
        legacy_javascope_header: platform_state.is_none(),
        platform_state,
    };
    // Validate against the CLI's supported wire contract, without depending on
    // the default runtime profile's selection of user-customizable observables.
    let mut settings = ProfileSettings::load(None)?;
    settings.initial_channels.clear();
    Profile::from_mapping(settings, mapping.clone())?;
    Ok(mapping)
}

pub fn run(repo: Option<&Path>, output: Option<&Path>) -> Result<PathBuf> {
    let root = crate::vitis::repository(repo)?;
    let mapping = generate(&root)?;
    let output = output
        .map(Path::to_path_buf)
        .unwrap_or_else(|| root.join("artifacts/channel_mappings/javascope.json"));
    let bytes = format!("{}\n", serde_json::to_string_pretty(&mapping)?);
    if let Some(parent) = output.parent().filter(|p| !p.as_os_str().is_empty()) {
        fs::create_dir_all(parent).with_context(|| format!("creating {}", parent.display()))?;
    }
    fs::write(&output, bytes).with_context(|| format!("writing {}", output.display()))?;
    Ok(output)
}

#[cfg(test)]
mod tests {
    use super::*;
    const HEADER: &str = include_str!("../../vitis/software/Baremetal/src/include/javascope.h");

    fn metadata(header: &str) -> Result<JavascopeMetadata> {
        javascope_metadata(
            header,
            &section(header, "SND_FLD_ZEROVALUE=0", "SND_FLD_ENDMARKER")?,
            &enum_table(header, "JSSD_ZEROVALUE=0", "JSSD_ENDMARKER")?,
        )
    }

    fn without_section(header: &str, prefix: &str) -> String {
        let start = header.find(&format!("{prefix}_ZEROVALUE=0")).unwrap();
        let end_marker = format!("{prefix}_ENDMARKER");
        let end = header[start..].find(&end_marker).unwrap() + start + end_marker.len();
        format!("{}{}", &header[..start], &header[end..])
    }

    #[test]
    fn all_visualization_sections_and_legacy_zero_alias_are_preserved() {
        let data = metadata(HEADER).unwrap();
        assert_eq!(data.send_fields.len(), 20);
        assert_eq!(data.send_fields[0].label, "send_field_1");
        assert_eq!(data.send_fields[0].unit.as_deref(), Some("RPM"));
        assert_eq!(data.send_fields[19].command, "Set_Send_Field_20");
        assert_eq!(data.buttons[7].label.as_deref(), Some("MyButton8"));
        assert_eq!(data.buttons[7].command, "My_Button_8");
        assert_eq!(
            data.receive_fields[0].label.as_deref(),
            Some("receive_field_1")
        );
        assert_eq!(data.receive_fields[0].unit.as_deref(), Some("RPM"));
        assert_eq!(
            data.receive_fields[3].signal.as_deref(),
            Some("JSSD_FLOAT_i_q")
        );
        assert_eq!(
            data.receive_fields[5].signal.as_deref(),
            Some("JSSD_ZEROVALUE")
        );
        assert_eq!(data.unused_slow_data_display, ["JSSD_FLOAT_Error_Code"]);
        assert_eq!(
            data.slow_signal_types["JSSD_ZEROVALUE"],
            SlowSignalType::Uint32
        );
        assert_eq!(
            data.slow_signal_types["JSSD_FLOAT_i_q"],
            SlowSignalType::Float32
        );
    }

    #[test]
    fn custom_text_types_and_display_order_match_javascope() {
        let header = HEADER
            .replace("send_field_1,", "speed reference /* caption */, // note")
            .replace("MyButton1,", "Calibrate motor,")
            .replace("receive_field_1,", "Actual speed,")
            .replace("RPM,", "rad / s,")
            .replace("JSSD_FLOAT_i_q", "JSSD_INT_counter");
        let data = metadata(&header).unwrap();
        assert_eq!(data.send_fields[0].label, "speedreference");
        assert_eq!(data.send_fields[0].unit.as_deref(), Some("rad/s"));
        assert_eq!(data.buttons[0].label.as_deref(), Some("Calibratemotor"));
        assert_eq!(data.receive_fields[0].label.as_deref(), Some("Actualspeed"));
        assert_eq!(
            data.receive_fields[3].signal.as_deref(),
            Some("JSSD_INT_counter")
        );
        assert_eq!(
            data.slow_signal_types["JSSD_INT_counter"],
            SlowSignalType::Uint32
        );
    }

    #[test]
    fn missing_optional_sections_remain_unspecified() {
        let mut header = HEADER.to_owned();
        for prefix in [
            "SND_LABELS",
            "MYBUTTONS_LABELS",
            "RCV_FLD",
            "RCV_LABELS",
            "SLOWDAT_DISPLAY",
        ] {
            header = without_section(&header, prefix);
        }
        let data = metadata(&header).unwrap();
        assert!(data.send_fields.iter().all(|f| f.unit.is_none()));
        assert!(data.buttons.iter().all(|b| b.label.is_none()));
        assert!(
            data.receive_fields
                .iter()
                .all(|f| f.label.is_none() && f.unit.is_none() && f.signal.is_none())
        );
        assert!(data.unused_slow_data_display.is_empty());
    }

    #[test]
    fn bad_display_sections_and_references_are_errors() {
        for (from, to) in [
            ("MyButton8,", ""),
            ("MYBUTTONS_LABELS_ENDMARKER", ""),
            (
                "MYBUTTONS_LABELS_ENDMARKER",
                "MYBUTTONS_LABELS_ENDMARKER\nMYBUTTONS_LABELS_ENDMARKER",
            ),
            (
                "MYBUTTONS_LABELS_ZEROVALUE=0,",
                "MYBUTTONS_LABELS_ZEROVALUE=0,\nMYBUTTONS_LABELS_ZEROVALUE=0,",
            ),
            ("JSSD_FLOAT_ZEROVALUE,", "JSSD_FLOAT_missing,"),
            (
                "SLOWDAT_DISPLAY_ENDMARKER",
                "JSSD_ZEROVALUE,\nSLOWDAT_DISPLAY_ENDMARKER",
            ),
        ] {
            assert!(
                metadata(&HEADER.replace(from, to)).is_err(),
                "accepted {from} -> {to}"
            );
        }
        let ambiguous = HEADER.replace("JSSD_ENDMARKER", "JSSD_INT_i_q,\nJSSD_ENDMARKER");
        assert!(
            metadata(&ambiguous)
                .unwrap_err()
                .to_string()
                .contains("2 matches")
        );
    }

    #[test]
    fn new_mapping_roundtrips_and_old_mapping_loads_without_catalog_changes() {
        let mapping = generate(Path::new(env!("CARGO_MANIFEST_DIR")).parent().unwrap()).unwrap();
        let json = serde_json::to_value(&mapping).unwrap();
        let decoded: ChannelMapping = serde_json::from_value(json.clone()).unwrap();
        assert_eq!(serde_json::to_value(decoded).unwrap(), json);
        let mut old_json = json.clone();
        old_json.as_object_mut().unwrap().remove("javascope");
        let old: ChannelMapping = serde_json::from_value(old_json.clone()).unwrap();
        assert!(old.javascope.is_none());
        assert_eq!(serde_json::to_value(&old).unwrap(), old_json);
        let mut settings = ProfileSettings::load(None).unwrap();
        settings.initial_channels.clear();
        let old_profile = Profile::from_mapping(settings.clone(), old).unwrap();
        let new_profile = Profile::from_mapping(settings.clone(), mapping).unwrap();
        assert_eq!(
            serde_json::to_value(old_profile).unwrap(),
            serde_json::to_value(new_profile).unwrap()
        );
        let mut bad = json;
        bad["javascope"]["receive_fields"][0]["signal"] = "JSSD_missing".into();
        let bad: ChannelMapping = serde_json::from_value(bad).unwrap();
        assert!(Profile::from_mapping(settings, bad).is_err());
    }

    #[test]
    fn sections_match_javascope_comments_and_whitespace() {
        let text = "// start\nSTART = 0, // comment\n name /* units */ ,\nEND;\n";
        assert_eq!(
            section(text, "START=0", "END").unwrap(),
            ["START=0", "name"]
        );
        assert!(section(&(text.to_owned() + text), "START=0", "END").is_err());
        assert!(section(text, "START=0", "MISSING").is_err());
    }
    #[test]
    fn enum_literals_assignments_and_errors() {
        let values = enum_table("ZERO=0,\nA=0x10U,\nB,\nEND", "ZERO=0", "END").unwrap();
        assert_eq!(values["A"], 16);
        assert_eq!(values["B"], 17);
        assert!(enum_table("ZERO=0,\nA=1<<4,\nEND", "ZERO=0", "END").is_err());
        assert!(enum_table("ZERO=0,\nA, B,\nEND", "ZERO=0", "END").is_err());
        let definitions = BTreeMap::from([("A".into(), "B".into()), ("B".into(), "A".into())]);
        assert!(number("A", &definitions, 0).is_err());
        assert_eq!(
            number("UINT32_C(0xC0000000)", &BTreeMap::new(), 0).unwrap(),
            0xC0000000
        );
    }
}
