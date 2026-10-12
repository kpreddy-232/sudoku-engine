#pragma once

#include "../include/board.hpp"
#include "../include/solver.hpp"
#include "../include/difficulty.hpp"
#include <random>

class Generator {

private:
    Solver solver;
    std::mt19937 gen;
    bool fillBoard(Board& board);
    void removeNumbers(Board& board, int holes);
    int getHoleCount(Difficulty level);
    Board generateCandidate();

public:
    Generator();
    Board generate(Difficulty level);
};