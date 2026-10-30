fn main() -> std::process::ExitCode {
    std::process::ExitCode::from(ultrazohm::cli::run(std::env::args()) as u8)
}
