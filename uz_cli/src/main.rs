fn main() -> std::process::ExitCode {
    std::process::ExitCode::from(ultrazohm_cli_lib::cli::run(std::env::args()) as u8)
}
