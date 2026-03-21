#!/bin/bash
set -e

problem_set=("a" "b" "c" "d")

if [ -z "$1" ]; then
  echo "Usage: $0 <contest_name>"
  exit 1
fi

contest_name="lc$1" # weekly or biweekly
mkdir -p "${contest_name}"
for problem in "${problem_set[@]}"; do
  if [ ! -f "${contest_name}/${problem}.cc" ]; then
    cp z.cc "${contest_name}/${problem}.cc"
  fi
  problem_window_name="${contest_name}-${problem}"
  if ! tmux list-windows | grep -Eq "^[0-9]+: ${problem_window_name}"; then
    tmux new-window -n "${problem_window_name}" "nvim ${contest_name}/${problem}.cc"
    tmux split-window -h -t "${problem_window_name}" -c "${contest_name}"
  fi
done
