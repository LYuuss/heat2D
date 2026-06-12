#include "Grid.hpp"

#include <algorithm>
#include <stdexcept>

Grid::Grid(std::size_t rows, std::size_t cols, double initial_value)
    : rows_(rows), cols_(cols), data_(rows * cols, initial_value) {
    if (rows == 0 || cols == 0) {
        throw std::invalid_argument("Grid dimensions must be positive");
    }
}

double& Grid::operator()(std::size_t i, std::size_t j) {
    return data_[i * cols_ + j];
}

double Grid::operator()(std::size_t i, std::size_t j) const {
    return data_[i * cols_ + j];
}

std::size_t Grid::rows() const {
    return rows_;
}

std::size_t Grid::cols() const {
    return cols_;
}

void Grid::fill(double value) {
    std::fill(data_.begin(), data_.end(), value);
}