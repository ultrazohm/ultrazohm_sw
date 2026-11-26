use std::{
    fs::{self, File},
    io::{self, Write},
    path::Path,
};

pub(crate) fn ensure_ignore_file(directory: &Path) -> io::Result<()> {
    fs::create_dir_all(directory)?;
    match File::create_new(directory.join(".gitignore")) {
        Ok(mut file) => file.write_all(b"*\n!*/\n!*.json\n"),
        Err(error) if error.kind() == io::ErrorKind::AlreadyExists => Ok(()),
        Err(error) => Err(error),
    }
}
