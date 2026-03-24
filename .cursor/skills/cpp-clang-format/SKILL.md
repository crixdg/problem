---
name: cpp-clang-format
description: Formats and aligns C++ edits with the repository clang-format configuration. Use when editing .cc, .cpp, .h, or .hpp files, when the user mentions clang-format or C++ style, or before finishing substantive C++ changes in a repo that has .clang-format.
---

# C++ and clang-format

## Instructions

1. **Discover config**: If the workspace has `.clang-format` (repo root or parent), treat it as authoritative. Do not invent a different style.
2. **After editing C++**: Run `clang-format -i <paths>` on every file you changed (or `clang-format -i` on a list of files). Use the same `clang-format` major version the project expects if documented; otherwise use the system default.
3. **Do not** manually reformat large regions to “look nice” when `clang-format` will do it—edit for logic, then format.
4. **If no `.clang-format`**: Prefer LLVM or Google style only if the user asks; otherwise match surrounding files (indent, brace style, line breaks).

## This repository

Root `.clang-format` uses LLVM base with: `InsertBraces: true`, `ColumnLimit: 0`, template declarations kept on one line, and short blocks/if/loops allowed on one line where the config permits. After changes under `templates/` or other C++ paths here, always run `clang-format -i` on those files from the repo root so the config is picked up.

## Quick check

```bash
clang-format --version
clang-format -n path/to/file.cc   # dry run, prints diffs if any
clang-format -i path/to/file.cc   # apply in place
```
