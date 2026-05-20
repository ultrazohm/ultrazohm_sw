#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR"

FORCE_BUILD=0

usage() {
  cat <<'EOF'
Usage: ./build.sh [--force|-f] [--help|-h]

Options:
  -f, --force    Rebuild even if UZ_GUI.jar is newer than src/ and lib/
  -h, --help     Show this help text
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    -f|--force)
      FORCE_BUILD=1
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown argument: $1" >&2
      usage >&2
      exit 1
      ;;
  esac
  shift
done

require_cmd() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Missing required command: $1" >&2
    exit 1
  fi
}

report_jar_lock_error() {
  echo "Build blocked: UZ_GUI.jar is locked by another process, likely a running JavaScope instance. Close JavaScope and retry." >&2
}

report_jar_failure() {
  local output="$1"
  if [[ -n "$output" ]]; then
    printf '%s\n' "$output" >&2
  fi
  if grep -Eiq 'Permission denied|AccessDeniedException|FileSystemException' <<<"$output"; then
    report_jar_lock_error
  else
    echo "JAR creation failed. See the output above for details." >&2
  fi
}

require_cmd javac
require_cmd jar

JDK_RELEASE=21

LIBS=(
  "lib/jfreechart-1.5.6.jar"
  "lib/flatlaf-3.7.jar"
)

for lib in "${LIBS[@]}"; do
  if [[ ! -f "$lib" ]]; then
    echo "Missing dependency: $lib" >&2
    exit 1
  fi
done

if [[ "$FORCE_BUILD" -eq 0 && -f UZ_GUI.jar ]]; then
  if ! find src lib -type f -newer UZ_GUI.jar -print -quit | grep -q .; then
    echo "Build up to date; skipping."
    exit 0
  fi
fi

mkdir -p build/classes
if [[ -f UZ_GUI.jar ]]; then
  if ! rm_output=$(rm -f UZ_GUI.jar 2>&1); then
    report_jar_failure "$rm_output"
    exit 1
  fi
fi
rm -f build/manifest.mf

echo "Compiling Java sources..."
mapfile -t SOURCES < <(find src -type f -name '*.java')
if [[ ${#SOURCES[@]} -eq 0 ]]; then
  echo "No Java source files found under src/" >&2
  exit 1
fi

CLASSPATH=$(IFS=:; echo "${LIBS[*]}")
javac --release "$JDK_RELEASE" -Xlint:unchecked -d build/classes -sourcepath src -cp "$CLASSPATH" "${SOURCES[@]}"

echo "Copying resources..."
if command -v rsync >/dev/null 2>&1; then
  rsync -a --exclude '*.java' src/ build/classes/
else
  while IFS= read -r -d '' file; do
    rel="${file#src/}"
    dest="build/classes/$rel"
    mkdir -p "$(dirname "$dest")"
    cp "$file" "$dest"
  done < <(find src -type f ! -name '*.java' -print0)
fi

echo "Writing build timestamp..."
mkdir -p build/classes/UZ_GUI
cat > build/classes/UZ_GUI/build-info.properties <<EOF
build.timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
EOF

CLASS_PATH_LINE=$(IFS=' '; echo "${LIBS[*]}")
cat > build/manifest.mf <<EOF
Manifest-Version: 1.0
Main-Class: UZ_GUI.Start
Class-Path: ${CLASS_PATH_LINE}
EOF

echo "Creating JAR..."
# Non-verbose jar creation (avoid per-file entry spam)
if ! jar_output=$(jar -cfm UZ_GUI.jar build/manifest.mf -C build/classes . 2>&1); then
  report_jar_failure "$jar_output"
  exit 1
fi

echo "Build successful: UZ_GUI.jar"
