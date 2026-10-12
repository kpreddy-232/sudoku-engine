#pragma once

#include "../include/board.hpp"
#include "../include/solver.hpp"


class Hint{
private:
    Solver solver;
public:
    bool getHint(Board& board, int& row, int& col, int& value);
};