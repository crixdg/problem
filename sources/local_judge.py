#!/usr/bin/env python3
"""
Local Judge for Library Checker Problems
Usage: python3 local_judge.py -p aplusb -s solution.cpp
"""

import argparse
import subprocess
import sys
import os
import tempfile
import time
from pathlib import Path
from typing import List, Tuple, Optional

class Color:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    RESET = '\033[0m'
    BOLD = '\033[1m'

def print_colored(text: str, color: str = ''):
    print(f"{color}{text}{Color.RESET}")

def find_problem_path(problem_name: str, repo_path: Path) -> Optional[Path]:
    """Find the problem directory"""
    search_dirs = ['sample', 'datastructure', 'graph', 'math', 'string', 'tree',
                   'convolution', 'polynomial', 'linear_algebra', 'number_theory']

    for dir_name in search_dirs:
        path = repo_path / dir_name / problem_name
        if path.exists() and (path / 'info.toml').exists():
            return path

    for info_file in repo_path.rglob('info.toml'):
        if info_file.parent.name == problem_name:
            return info_file.parent

    return None

def compile_solution(solution_file: Path, output_binary: Path, verbose: bool = False) -> bool:
    """Compile C++ solution"""
    print_colored(f"📦 Compiling {solution_file.name}...", Color.CYAN)

    compile_cmd = ['g++', '-std=c++20', '-O0', '-o', str(output_binary), str(solution_file)]

    if verbose:
        print_colored(f"    Command: {' '.join(compile_cmd)}", Color.BLUE)

    try:
        result = subprocess.run(compile_cmd, capture_output=True, text=True, timeout=30)

        if result.returncode != 0:
            print_colored(f"Compilation Error:", Color.RED + Color.BOLD)
            print(result.stderr)
            return False

        print_colored(f"Compilation successful!", Color.GREEN)
        return True

    except subprocess.TimeoutExpired:
        print_colored("Compilation timeout!", Color.RED)
        return False
    except FileNotFoundError:
        print_colored("g++ not found! Install g++.", Color.RED)
        return False

def run_test_case(binary: Path, input_file: Path, expected_output_file: Path,
                  checker: Path, time_limit: float, verbose: bool = False) -> Tuple[str, float, str]:
    """Run a test case. Returns (status, time, message)"""

    try:
        with open(input_file, 'r') as f:
            input_data = f.read()

        start_time = time.time()
        result = subprocess.run([str(binary)], input=input_data, capture_output=True,
                              text=True, timeout=time_limit)
        elapsed_time = time.time() - start_time

        if result.returncode != 0:
            return 'RE', elapsed_time, f"Runtime Error (exit code: {result.returncode})"

        with tempfile.NamedTemporaryFile(mode='w', delete=False, suffix='.out') as tmp:
            tmp.write(result.stdout)
            output_file = Path(tmp.name)

        try:
            checker_result = subprocess.run(
                [str(checker), str(input_file), str(output_file), str(expected_output_file)],
                capture_output=True, text=True, timeout=5)

            if checker_result.returncode == 0:
                return 'AC', elapsed_time, 'Accepted'
            else:
                msg = checker_result.stdout.strip() or checker_result.stderr.strip() or 'Wrong Answer'
                return 'WA', elapsed_time, msg
        finally:
            output_file.unlink()

    except subprocess.TimeoutExpired:
        return 'TLE', time_limit, f'Time Limit Exceeded (>{time_limit}s)'
    except Exception as e:
        return 'RE', 0.0, f'Runtime Error: {str(e)}'

def run_all_tests(problem_path: Path, solution_binary: Path,
                  time_limit: float, verbose: bool = False) -> Tuple[int, int]:
    """Run all tests. Returns (passed, total)"""

    in_dir = problem_path / 'in'
    out_dir = problem_path / 'out'
    checker = problem_path / 'checker'

    if not in_dir.exists():
        print_colored("Test cases not found. Run: ./generate.py -p <problem>", Color.RED)
        return 0, 0

    if not checker.exists():
        print_colored("Checker not found. Run: ./generate.py -p <problem>", Color.RED)
        return 0, 0

    input_files = sorted(in_dir.glob('*.in'))

    if not input_files:
        print_colored("No test cases found!", Color.RED)
        return 0, 0

    print_colored(f"\nRunning {len(input_files)} test cases...\n", Color.CYAN + Color.BOLD)

    passed = 0
    total = len(input_files)

    for i, input_file in enumerate(input_files, 1):
        test_name = input_file.stem
        output_file = out_dir / f"{test_name}.out"

        if not output_file.exists():
            print_colored(f"  [{i}/{total}] {test_name}:  SKIP", Color.YELLOW)
            continue

        status, elapsed, message = run_test_case(solution_binary, input_file, output_file,
                                                checker, time_limit, verbose)

        if status == 'AC':
            status_str = f"{Color.GREEN}✓ AC{Color.RESET}"
            passed += 1
        elif status == 'WA':
            status_str = f"{Color.RED}✗ WA{Color.RESET}"
        elif status == 'TLE':
            status_str = f"{Color.YELLOW}⏱ TLE{Color.RESET}"
        else:
            status_str = f"{Color.YELLOW}⚠ RE{Color.RESET}"

        time_str = f"{elapsed:.3f}s"
        print(f"  [{i}/{total}] {test_name:20s} {status_str}  {time_str:8s}", end='')

        if verbose or status != 'AC':
            print(f"  {message}")
        else:
            print()

    return passed, total

def main():
    parser = argparse.ArgumentParser(description='Local Judge for Library Checker')
    parser.add_argument('-p', '--problem', required=True, help='Problem name')
    parser.add_argument('-s', '--solution', required=True, type=Path, help='Solution file')
    parser.add_argument('--repo-path', type=Path, default=Path.cwd(), help='Repo path')
    parser.add_argument('--time-limit', type=float, default=5.0, help='Time limit')
    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose')

    args = parser.parse_args()

    if not args.solution.exists():
        print_colored(f"Solution not found: {args.solution}", Color.RED)
        sys.exit(1)

    print_colored(f"Looking for problem: {args.problem}", Color.CYAN)
    problem_path = find_problem_path(args.problem, args.repo_path)

    if not problem_path:
        print_colored(f"Problem '{args.problem}' not found!", Color.RED)
        sys.exit(1)

    print_colored(f"Found: {problem_path.relative_to(args.repo_path)}", Color.GREEN)
    print_colored(f" Time limit: {args.time_limit}s", Color.CYAN)

    with tempfile.TemporaryDirectory() as tmpdir:
        solution_binary = Path(tmpdir) / 'solution'

        if not compile_solution(args.solution, solution_binary, args.verbose):
            sys.exit(1)

        passed, total = run_all_tests(problem_path, solution_binary, args.time_limit, args.verbose)

    print()
    print_colored("=" * 60, Color.CYAN)

    if passed == total:
        print_colored(f"All tests passed! ({passed}/{total})", Color.GREEN + Color.BOLD)
        sys.exit(0)
    else:
        print_colored(f"{total - passed} failed. ({passed}/{total} passed)", Color.RED + Color.BOLD)
        sys.exit(1)

if __name__ == '__main__':
    main()
