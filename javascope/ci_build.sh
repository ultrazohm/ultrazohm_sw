#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")/.."

# Compare the whole push, including pushes containing multiple commits.
# Other events and unavailable history build conservatively. In particular,
# a PR's before SHA need not represent its target branch or merge base.
before="${DRONE_COMMIT_BEFORE:-}"
after="${DRONE_COMMIT_AFTER:-}"
if [[ "${DRONE_BUILD_EVENT:-}" == push && -n "$before" && -n "$after" ]] &&
   git cat-file -e "$before^{commit}" 2>/dev/null &&
   git cat-file -e "$after^{commit}" 2>/dev/null; then
  if git diff --quiet "$before" "$after" -- javascope/; then
    echo "No changes under javascope/; skipping JavaScope build."
    exit 0
  else
    result=$?
    if [[ "$result" -ne 1 ]]; then
      echo "Could not compare push commits; building JavaScope."
    fi
  fi
else
  echo "No reliable push comparison available; building JavaScope."
fi

# Images and resources under javascope/ may be stored in Git LFS.
git lfs pull --include="javascope/**" --exclude=""
exec bash javascope/build.sh -f
