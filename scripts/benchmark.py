import csv
import re
import subprocess
from pathlib import Path


ROOT_DIR = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT_DIR / "build"
EXECUTABLE = BUILD_DIR / "heat2d"
RESULTS_FILE = ROOT_DIR / "benchmark_results.csv"


BENCHMARKS = [
    (500, 500, 500),
    (1000, 1000, 500),
    (1500, 1500, 500),
    (2000, 2000, 500),
]


def extract_execution_time(output: str) -> float:
    match = re.search(r"Execution time:\s+([0-9.]+)", output)

    if not match:
        raise ValueError("Could not extract execution time from program output.")

    return float(match.group(1))


def run_benchmark(rows: int, cols: int, iterations: int) -> float:
    command = [
        str(EXECUTABLE),
        str(rows),
        str(cols),
        str(iterations),
    ]

    completed_process = subprocess.run(
        command,
        cwd=BUILD_DIR,
        capture_output=True,
        text=True,
        check=True,
    )

    return extract_execution_time(completed_process.stdout)


def main() -> None:
    if not EXECUTABLE.exists():
        raise FileNotFoundError(
            f"Executable not found: {EXECUTABLE}\n"
            "Please build the project first with: cmake --build build"
        )

    results = []

    for rows, cols, iterations in BENCHMARKS:
        print(f"Running benchmark: {rows}x{cols}, iterations={iterations}")

        elapsed = run_benchmark(rows, cols, iterations)

        results.append({
            "rows": rows,
            "cols": cols,
            "iterations": iterations,
            "execution_time_seconds": elapsed,
        })

        print(f"  -> {elapsed:.6f} seconds")

    with RESULTS_FILE.open("w", newline="") as file:
        writer = csv.DictWriter(
            file,
            fieldnames=[
                "rows",
                "cols",
                "iterations",
                "execution_time_seconds",
            ],
        )

        writer.writeheader()
        writer.writerows(results)

    print(f"\nBenchmark results saved to: {RESULTS_FILE}")


if __name__ == "__main__":
    main()