//! Read the repository's JavaScope header contract without a C compiler or Vitis.
use crate::profile::{ChannelMapping, PlatformStateMapping, Profile, ProfileSettings, Repository};
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
        .map(|path| fs::read_to_string(root.join(path)).with_context(|| format!("reading {path}")))
        .collect::<Result<Vec<_>>>()?;
    let header = &texts[0];
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
    let status_defines = defines(&texts[1])?;
    let mask = number("JAVASCOPE_PLATFORM_STATE_MASK", &status_defines, 0)?;
    let shift = mask.trailing_zeros();
    ensure!(
        shift <= 30 && mask == (3_u32 << shift),
        "platform-state mask must select two adjacent bits"
    );
    let mut values = BTreeMap::new();
    for name in status_defines.keys().filter(|name| {
        name.starts_with("JAVASCOPE_PLATFORM_") && name.as_str() != "JAVASCOPE_PLATFORM_STATE_MASK"
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
    let mut geometry = BTreeMap::new();
    for text in &texts[2..] {
        for (name, value) in defines(text)? {
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
