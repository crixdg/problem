#!/bin/bash
# Update "modified:" in /** ... */ file headers (DD.MM.YYYY HH:MM:SS), or print a new header.
set -euo pipefail

usage() {
  echo "Usage:"
  echo "  $0 FILE [FILE...]              # set modified: to now (first ~10 lines)"
  echo "  $0 --header [DESCRIPTION]      # print header block to stdout (modified = now)"
  exit "${1:-0}"
}

ts() { date +"%d.%m.%Y %H:%M:%S"; }

print_header() {
  local desc="${1:-}"
  cat <<EOF
/**
 *    author: crixdg
 *    modified: $(ts)
 *    created: $(ts)
 *    description: ${desc}
 */
EOF
}

if [[ $# -eq 0 ]] || [[ "${1:-}" == -h ]] || [[ "${1:-}" == --help ]]; then
  usage
fi

if [[ "$1" == --header ]]; then
  shift
  print_header "${*:-}"
  exit 0
fi

pat='^[[:space:]]*\*[[:space:]]*modified:[[:space:]]*'

for f in "$@"; do
  if [[ ! -f "$f" ]]; then
    echo "skip (not a file): $f" >&2
    continue
  fi
  if ! grep -q "$pat" "$f"; then
    echo "no 'modified:' line in first pass: $f" >&2
    continue
  fi
  # Only touch early lines (typical file header).
  sed -i "1,10{s/${pat}.*/ *    modified: $(ts)/}" "$f"
done
