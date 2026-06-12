# Heat2D — C++ Heat Diffusion Solver

Heat2D is a modern C++ project that simulates heat diffusion on a 2D grid.

The goal of this project is to build a clean and extensible C++ codebase while progressively introducing concepts related to high-performance computing, memory layout optimization, benchmarking and parallel programming.

This project starts with a sequential implementation and is designed to evolve toward multithreaded and OpenMP-based versions.

---

## Overview

The simulation represents a 2D metallic plate as a grid of temperature values.

At each iteration, the temperature of each inner cell is updated using the average of its four direct neighbors:

```txt
new[i][j] = 0.25 * (
    old[i-1][j] +
    old[i+1][j] +
    old[i][j-1] +
    old[i][j+1]
)
```

Boundary cells are kept fixed.

---

## Features

* Modern C++ implementation
* Object-oriented project structure
* Cache-friendly 1D memory layout for the 2D grid
* Sequential heat diffusion solver
* Configurable grid size and number of iterations
* CSV export of the final grid
* Basic execution time measurement
* Python visualization script

---

## Project Structure

```txt
heat2d/
├── include/
│   ├── Grid.hpp
│   ├── HeatSolver.hpp
│   └── Timer.hpp
│
├── src/
│   ├── Grid.cpp
│   ├── HeatSolver.cpp
│   └── main.cpp
│
├── tests/
├── plot_heat.py
├── CMakeLists.txt
└── README.md
```

---

## Requirements

* C++20 compatible compiler
* CMake 3.16 or higher
* Python 3
* Python packages for visualization:

  * pandas
  * matplotlib

Install the Python dependencies with:

```bash
pip install pandas matplotlib
```

---

## Build

From the root of the project:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Run

Default execution:

```bash
./heat2d
```

This runs the simulation with default parameters:

```txt
Rows: 500
Columns: 500
Iterations: 500
```

You can also provide custom parameters:

```bash
./heat2d <rows> <cols> <iterations>
```

Example:

```bash
./heat2d 1000 1000 500
```

Example output:

```txt
Heat2D simulation completed
Grid: 1000 x 1000
Iterations: 500
Execution time: 1.83 seconds
Output file: heat_output.csv
```

---

## Visualization

After running the simulation, a CSV file is generated:

```txt
build/heat_output.csv
```

To visualize the final heat distribution:

```bash
python3 plot_heat.py
```

The script loads the generated CSV file and displays the heat map using matplotlib.

---

## Implementation Details

### Grid Representation

Instead of using:

```cpp
std::vector<std::vector<double>>
```

the grid is stored as a single contiguous 1D vector:

```cpp
std::vector<double> data_;
```

A cell `(i, j)` is accessed internally with:

```cpp
data_[i * cols_ + j]
```

This representation improves memory locality and is closer to the layout typically used in numerical and high-performance computing applications.

---

## Current Version

The current version includes:

* `Grid`: a 2D grid abstraction backed by contiguous memory
* `HeatSolver`: a sequential heat diffusion solver
* `Timer`: a small utility for measuring execution time
* CSV export for result visualization
* command-line parameters for grid size and iteration count

---

## Roadmap

Planned improvements:

* Add unit tests
* Add benchmark scripts
* Compare different grid sizes
* Implement a `std::thread` parallel version
* Implement an OpenMP version
* Measure speedup and parallel efficiency
* Add performance plots
* Add MPI-based domain decomposition as an advanced extension

---

## Example Benchmark Plan

Future experiments will compare execution time across different grid sizes:

```txt
500 x 500
1000 x 1000
2000 x 2000
4000 x 4000
```

And across different implementations:

```txt
Sequential
std::thread
OpenMP
MPI
```

Useful metrics:

```txt
Execution time
Speedup
Parallel efficiency
Memory usage
```

---

## Educational Goals

This project is designed to practice:

* Modern C++
* Header/source file separation
* Classes and encapsulation
* Memory layout optimization
* Numerical simulation
* Performance measurement
* Parallel programming fundamentals
* HPC-oriented software design

---

## License

This project is released under the MIT License.
