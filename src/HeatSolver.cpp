#include "HeatSolver.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <utility>

HeatSolver::HeatSolver(std::size_t rows, std::size_t cols, std::size_t iterations)
    : current_(rows, cols, 0.0),
      next_(rows, cols, 0.0),
      iterations_(iterations) {
    if (rows < 3 || cols < 3) {
        throw std::invalid_argument("Grid must be at least 3x3");
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
    for (std::size_t i = 1; i < current_.rows() - 1; ++i) {
        for (std::size_t j = 1; j < current_.cols() - 1; ++j) {
            next_(i, j) = 0.25 * (
                current_(i - 1, j) +
                current_(i + 1, j) +
                current_(i, j - 1) +
                current_(i, j + 1)
            );
        }
    }

    std::swap(current_, next_);
}

void HeatSolver::run() {
    for (std::size_t iter = 0; iter < iterations_; ++iter) {
        step();
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