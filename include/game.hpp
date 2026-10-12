#pragma once

#include <string>
#include "board.hpp"
#include "solver.hpp"
#include "generator.hpp"
#include "hint.hpp"
#include "timer.hpp"
#include "score.hpp"

class Game{
private:
    Board board;
    Solver solver;
    Generator generator;
    Hint hint;
    Timer timer;
    ScoreManager scoreManager;
    std::string currentDifficulty;

public:
    void start();
    void displayScore();
};