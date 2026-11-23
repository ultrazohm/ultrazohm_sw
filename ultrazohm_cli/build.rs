use std::{
    collections::hash_map::DefaultHasher,
    env, fs,
    hash::{Hash, Hasher},
    path::{Path, PathBuf},
};

fn collect(root: &Path, directory: &Path, files: &mut Vec<(String, Vec<u8>)>) {
    println!("cargo:rerun-if-changed={}", directory.display());
    for entry in fs::read_dir(directory)
        .expect("firmware resources")
        .map(Result::unwrap)
    {
        let path = entry.path();
        if path.is_dir() {
            collect(root, &path, files);
        } else if path
            .extension()
            .is_some_and(|v| v == "tcl" || v == "launch")
        {
            files.push((
                path.strip_prefix(root)
                    .unwrap()
                    .to_str()
                    .unwrap()
                    .replace('\\', "/"),
                fs::read(&path).unwrap(),
            ));
        }
    }
}

fn main() {
    let root = PathBuf::from(env::var_os("CARGO_MANIFEST_DIR").unwrap());
    let mut files = Vec::new();
    let staged = root.join("firmware_resources");
    if staged.is_dir() {
        collect(&staged, &staged, &mut files);
    } else {
        let scripts = root.join("../tcl_scripts");
        collect(&scripts, &scripts, &mut files);
        for name in [
            "Debug_UltraZohm.launch",
            "Run_UltraZohm.launch",
            "Debug_UltraZohm_fast_restart_PL_reset.launch",
        ] {
            let path = root.join("../vitis/software").join(name);
            println!("cargo:rerun-if-changed={}", path.display());
            files.push((format!("launch/{name}"), fs::read(path).unwrap()));
        }
    }
    files.sort_by(|a, b| a.0.cmp(&b.0));
    let mut hash = DefaultHasher::new();
    files.hash(&mut hash);
    let mut code = format!(
        "const RESOURCE_ID: &str = \"{:016x}\";\nconst RESOURCES: &[(&str, &[u8])] = &[\n",
        hash.finish()
    );
    for (name, contents) in files {
        code.push_str(&format!("({name:?}, &{contents:?}),\n"));
    }
    code.push_str("];\n");
    fs::write(
        PathBuf::from(env::var_os("OUT_DIR").unwrap()).join("firmware_resources.rs"),
        code,
    )
    .unwrap();
}
