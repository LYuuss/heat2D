#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time_;

public:
    void start() {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    double elapsed_seconds() const {
        const auto end_time = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed = end_time - start_time_;
        return elapsed.count();
    }
};