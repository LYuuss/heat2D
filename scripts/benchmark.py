import csv
import re
import subprocess
from pathlib import Path


ROOT_DIR = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT_DIR / "build"
EXECUTABLE = BUILD_DIR / "heat2d"
RESULTS_FILE = ROOT_DIR / "benchmark_results.csv"


GRID_ROWS = 1500
GRID_COLS = 1500
ITERATIONS = 500

THREAD_COUNTS = [1, 2, 4, 8]


def extract_execution_time(output: str) -> float:
    match = re.search(r"Execution time:\s+([0-9.]+)", output)

    if not match:
        raise ValueError("Could not extract execution time from program output.")

    return float(match.group(1))


def run_benchmark(rows: int, cols: int, iterations: int, threads: int) -> float:
    command = [
        str(EXECUTABLE),
        str(rows),
        str(cols),
        str(iterations),
        str(threads),
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

    sequential_time = None

    for threads in THREAD_COUNTS:
        print(
            f"Running benchmark: "
            f"{GRID_ROWS}x{GRID_COLS}, "
            f"iterations={ITERATIONS}, "
            f"threads={threads}"
        )

        elapsed = run_benchmark(GRID_ROWS, GRID_COLS, ITERATIONS, threads)

        if threads == 1:
            sequential_time = elapsed

        speedup = sequential_time / elapsed if sequential_time else 1.0
        efficiency = speedup / threads

        results.append({
            "rows": GRID_ROWS,
            "cols": GRID_COLS,
            "iterations": ITERATIONS,
            "threads": threads,
            "execution_time_seconds": elapsed,
            "speedup": speedup,
            "efficiency": efficiency,
        })

        print(f"  -> time: {elapsed:.6f}s")
        print(f"  -> speedup: {speedup:.3f}")
        print(f"  -> efficiency: {efficiency:.3f}")

    with RESULTS_FILE.open("w", newline="") as file:
        writer = csv.DictWriter(
            file,
            fieldnames=[
                "rows",
                "cols",
                "iterations",
                "threads",
                "execution_time_seconds",
                "speedup",
                "efficiency",
            ],
        )

        writer.writeheader()
        writer.writerows(results)

    print(f"\nBenchmark results saved to: {RESULTS_FILE}")


if __name__ == "__main__":
    main()