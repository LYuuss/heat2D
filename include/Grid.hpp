#pragma once

#include <cstddef>
#include <vector>

class Grid {
private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<double> data_;

public:
    Grid(std::size_t rows, std::size_t cols, double initial_value = 0.0);

    double& operator()(std::size_t i, std::size_t j);
    double operator()(std::size_t i, std::size_t j) const;

    std::size_t rows() const;
    std::size_t cols() const;

    void fill(double value);
};