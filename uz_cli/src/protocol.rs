//! The unchanged JavaScope little-endian wire adapter. No TCP packet assumptions.
use anyhow::{Result, ensure};
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Frame {
    pub status: u32,
    pub slow_raw: Vec<u32>,
    pub slow_ids: Vec<u32>,
    pub channels: Vec<Vec<f32>>,
}

pub fn encode_command(id: u32, value: f32) -> Result<[u8; 8]> {
    ensure!(value.is_finite(), "command value must be finite float32");
    let mut bytes = [0; 8];
    bytes[..4].copy_from_slice(&id.to_le_bytes());
    bytes[4..].copy_from_slice(&value.to_le_bytes());
    Ok(bytes)
}

pub fn decode_frame(
    bytes: &[u8],
    channels: usize,
    samples: usize,
    slow_count: u32,
) -> Result<Frame> {
    ensure!(
        channels == 20 && (1..=4096).contains(&samples),
        "unsupported frame geometry"
    );
    ensure!(
        bytes.len() == 4 + (channels + 2) * samples * 4,
        "incorrect frame length"
    );
    let words: Vec<u32> = bytes
        .chunks_exact(4)
        .map(|b| u32::from_le_bytes(b.try_into().unwrap()))
        .collect();
    let slow_ids = words[1 + (channels + 1) * samples..]
        .iter()
        .map(|&w| {
            let f = f32::from_bits(w);
            ensure!(
                f.is_finite() && f >= 0.0 && f.fract() == 0.0 && f < slow_count as f32,
                "invalid slow ID {f}; framing/profile mismatch (cannot resynchronize)"
            );
            Ok(f as u32)
        })
        .collect::<Result<Vec<_>>>()?;
    Ok(Frame {
        status: words[0],
        slow_raw: words[1..1 + samples].to_vec(),
        slow_ids,
        channels: words[1 + samples..1 + (channels + 1) * samples]
            .chunks_exact(samples)
            .map(|c| c.iter().map(|&v| f32::from_bits(v)).collect())
            .collect(),
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn golden_command() {
        assert_eq!(
            encode_command(201, 3.0).unwrap(),
            [201, 0, 0, 0, 0, 0, 64, 64]
        );
        assert!(encode_command(4, f32::NAN).is_err());
    }
    #[test]
    fn column_major_and_raw_bits() {
        let mut b = 13u32.to_le_bytes().to_vec();
        for x in 0..44 {
            b.extend_from_slice(&(x as f32).to_le_bytes());
        }
        b[4 + 42 * 4..4 + 43 * 4].copy_from_slice(&2.0f32.to_le_bytes());
        b[4 + 43 * 4..].copy_from_slice(&3.0f32.to_le_bytes());
        let f = decode_frame(&b, 20, 2, 17).unwrap();
        assert_eq!(f.status, 13);
        assert_eq!(f.channels[0], [2.0, 3.0]);
        assert_eq!(f.channels[19], [40.0, 41.0]);
        assert_eq!(f.slow_ids, [2, 3]);
        assert_eq!(f.slow_raw[1], 1.0f32.to_bits());
        assert!(decode_frame(&b[..b.len() - 1], 20, 2, 17).is_err());
        b[4 + 43 * 4..].copy_from_slice(&f32::NAN.to_le_bytes());
        assert!(decode_frame(&b, 20, 2, 17).is_err());
    }
}
