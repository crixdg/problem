#!/bin/bash
set -euo pipefail

AUTHOR="crixdg"

usage() {
	echo "Usage:"
	echo "  $0 FILE [FILE...]"
	echo "    - update '*    timestamp:' in header if it exists"
	echo "    - otherwise prepend a new header block"
	exit "${1:-0}"
}

ts() { date +"%d.%m.%Y %H:%M:%S"; }

print_header() {
	cat <<EOF
/**
 *    author: ${AUTHOR}
 *    timestamp: $(ts)
 **/
EOF
}

if [[ $# -eq 0 ]] || [[ "${1:-}" == -h ]] || [[ "${1:-}" == --help ]]; then
	usage
fi

files=()
for arg in "$@"; do
	files+=("$arg")
done

pat='^[[:space:]]*\*[[:space:]]*timestamp:[[:space:]]*'

for f in "${files[@]}"; do
	if [[ ! -f "$f" ]]; then
		echo "skip (not a file): $f" >&2
		continue
	fi
	if grep -Eq "$pat" "$f"; then
		# Only touch early lines (typical file header).
		sed -i "1,20{s/${pat}.*/ *    timestamp: $(ts)/}" "$f"
	else
		tmp="$(mktemp)"
		print_header >"$tmp"
		printf "\n" >>"$tmp"
		cat "$f" >>"$tmp"
		mv "$tmp" "$f"
	fi
done
