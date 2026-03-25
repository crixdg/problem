#!/bin/bash
set -euo pipefail

AUTHOR="crixdg"

usage() {
	echo "Usage:"
	echo "  $0 FILE [FILE...]              # set modified: to now (first ~10 lines)"
	echo "  $0 --header [DESCRIPTION]      # print header block to stdout (modified = now)"
	echo "  $0 FILE [FILE...] --header [DESCRIPTION] # add new header block to head of each FILE"
	exit "${1:-0}"
}

ts() { date +"%d.%m.%Y %H:%M:%S"; }

print_header() {
	local desc="${1:-}"
	local compact="${desc//[[:space:]]/}"
	echo "/**"
	echo " *    author: ${AUTHOR}"
	echo " *    modified: $(ts)"
	echo " *    created: $(ts)"
	if [[ -n "$compact" ]]; then
		echo " *    description: ${desc}"
	fi
	echo " **/"
}

if [[ $# -eq 0 ]] || [[ "${1:-}" == -h ]] || [[ "${1:-}" == --help ]]; then
	usage
fi

files=()
desc=""
have_header=false
i=1
while [[ $i -le $# ]]; do
	arg="${!i}"
	if [[ "$arg" == --header ]]; then
		have_header=true
		((++i))
		desc_parts=()
		while [[ $i -le $# ]]; do
			desc_parts+=("${!i}")
			((++i)) || true
		done
		desc="${desc_parts[*]}"
		break
	fi
	files+=("$arg")
	((++i)) || true
done

if [[ "$have_header" == true ]] && [[ ${#files[@]} -eq 0 ]]; then
	print_header "$desc"
	exit 0
fi

if [[ "$have_header" == true ]]; then
	for f in "${files[@]}"; do
		if [[ ! -f "$f" ]]; then
			echo "skip (not a file): $f" >&2
			continue
		fi
		tmp="$(mktemp)"
		print_header "$desc" >"$tmp"
		cat "$f" >>"$tmp"
		mv "$tmp" "$f"
	done
	exit 0
fi

pat='^[[:space:]]*\*[[:space:]]*modified:[[:space:]]*'

for f in "${files[@]}"; do
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
