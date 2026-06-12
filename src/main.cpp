#include "Grid.hpp"

#include <iostream>

int main() {
    Grid grid(5, 5, 0.0);

    grid(2, 2) = 100.0;

    for (std::size_t i = 0; i < grid.rows(); ++i) {
        for (std::size_t j = 0; j < grid.cols(); ++j) {
            std::cout << grid(i, j) << " ";
        }
        std::cout << '\n';
    }

    return 0;
}