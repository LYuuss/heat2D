#include "HeatSolver.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

HeatSolver::HeatSolver(std::size_t rows, std::size_t cols, std::size_t iterations)
    : current_(rows, cols, 0.0),
      next_(rows, cols, 0.0),
      iterations_(iterations) {
    if (rows < 3 || cols < 3) {
        throw std::invalid_argument("Grid must be at least 3x3");
    }
}

void HeatSolver::compute_range(std::size_t row_start, std::size_t row_end){
    for (std::size_t  i=row_start; i < row_end; ++i){
        for(std::size_t j=1; j < current_.cols(); ++j ){
            next_(i,j) = 0.25 * (
                current_(i - 1, j) +
                current_(i + 1, j) +
                current_(i, j + 1) + 
                current_(i, j - 1)
            );

        }
    }
}

void HeatSolver::initialize_hotspot(double temperature, std::size_t radius) {
    const std::size_t center_i = current_.rows() / 2;
    const std::size_t center_j = current_.cols() / 2;

    const std::size_t i_start = center_i > radius ? center_i - radius : 1;
    const std::size_t j_start = center_j > radius ? center_j - radius : 1;

    const std::size_t i_end = std::min(center_i + radius, current_.rows() - 2);
    const std::size_t j_end = std::min(center_j + radius, current_.cols() - 2);

    for (std::size_t i = i_start; i <= i_end; ++i) {
        for (std::size_t j = j_start; j <= j_end; ++j) {
            current_(i, j) = temperature;
        }
    }
}

void HeatSolver::step() {
    compute_range(1, current_.rows() - 1);
    std::swap(current_, next_);
}

void HeatSolver::step_parallel(std::size_t num_threads) {
    const std::size_t inner_rows = current_.rows() - 2;

    if (num_threads <= 1 || inner_rows == 0) {
        step();
        return;
    }

    num_threads = std::min(num_threads, inner_rows);

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    const std::size_t rows_per_thread = inner_rows / num_threads;
    const std::size_t remaining_rows = inner_rows % num_threads;

    std::size_t row_start = 1;

    for (std::size_t thread_id = 0; thread_id < num_threads; ++thread_id) {
        const std::size_t extra_row = thread_id < remaining_rows ? 1 : 0;
        const std::size_t row_end = row_start + rows_per_thread + extra_row;

        threads.emplace_back(
            &HeatSolver::compute_range,
            this,
            row_start,
            row_end
        );

        row_start = row_end;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::swap(current_, next_);
}

void HeatSolver::run() {
    for (std::size_t iter = 0; iter < iterations_; ++iter) {
        step();
    }
}

void HeatSolver::run_parallel(std::size_t num_threads) {
    for (std::size_t iter = 0; iter < iterations_; ++iter) {
        step_parallel(num_threads);
    }
}

const Grid& HeatSolver::grid() const {
    return current_;
}

void HeatSolver::save_to_csv(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file) {
        throw std::runtime_error("Could not open output file: " + filename);
    }

    for (std::size_t i = 0; i < current_.rows(); ++i) {
        for (std::size_t j = 0; j < current_.cols(); ++j) {
            file << current_(i, j);

            if (j + 1 < current_.cols()) {
                file << ",";
            }
        }

        file << "\n";
    }
}