#include "../include/timer.hpp"

void Timer::start(){
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop(){
    endTime = std::chrono::high_resolution_clock::now();
}

int Timer::getElapsedSeconds() const{
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    return duration.count();
}