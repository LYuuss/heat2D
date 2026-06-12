#include "HeatSolver.hpp"
#include "Timer.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        std::size_t rows = 500;
        std::size_t cols = 500;
        std::size_t iterations = 500;

        if (argc == 4) {
            rows = static_cast<std::size_t>(std::stoul(argv[1]));
            cols = static_cast<std::size_t>(std::stoul(argv[2]));
            iterations = static_cast<std::size_t>(std::stoul(argv[3]));
        }

        HeatSolver solver(rows, cols, iterations);

        solver.initialize_hotspot(100.0, 10);

        Timer timer;
        timer.start();

        solver.run();

        const double elapsed = timer.elapsed_seconds();

        solver.save_to_csv("heat_output.csv");

        std::cout << "Heat2D simulation completed\n";
        std::cout << "Grid: " << rows << " x " << cols << "\n";
        std::cout << "Iterations: " << iterations << "\n";
        std::cout << "Execution time: " << elapsed << " seconds\n";
        std::cout << "Output file: heat_output.csv\n";

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return EXIT_FAILURE;
    }
}