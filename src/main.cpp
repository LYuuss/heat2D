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
        std::size_t num_threads = 1;

        if (argc == 4 || argc == 5) {
            rows = static_cast<std::size_t>(std::stoul(argv[1]));
            cols = static_cast<std::size_t>(std::stoul(argv[2]));
            iterations = static_cast<std::size_t>(std::stoul(argv[3]));

            if (argc == 5) {
                num_threads = static_cast<std::size_t>(std::stoul(argv[4]));
            }
        }

        HeatSolver solver(rows, cols, iterations);
        solver.initialize_hotspot(100.0, 10);

        Timer timer;
        timer.start();

        if (num_threads <= 1) {
            solver.run();
        } else {
            solver.run_parallel(num_threads);
        }

        const double elapsed = timer.elapsed_seconds();

        solver.save_to_csv("heat_output.csv");

        std::cout << "Heat2D simulation completed\n";
        std::cout << "Grid: " << rows << " x " << cols << "\n";
        std::cout << "Iterations: " << iterations << "\n";
        std::cout << "Threads: " << num_threads << "\n";
        std::cout << "Execution time: " << elapsed << " seconds\n";
        std::cout << "Output file: heat_output.csv\n";

        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return EXIT_FAILURE;
    }
}