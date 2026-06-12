#pragma once

#include "Grid.hpp"

#include <cstddef>
#include <string>

class HeatSolver {
private:
    Grid current_;
    Grid next_;
    std::size_t iterations_;

public:
    HeatSolver(std::size_t rows, std::size_t cols, std::size_t iterations);

    void initialize_hotspot(double temperature = 100.0, std::size_t radius = 5);
    void step();
    void run();

    const Grid& grid() const;

    void save_to_csv(const std::string& filename) const;
};