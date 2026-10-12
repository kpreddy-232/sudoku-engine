#pragma once
#include "../include/board.hpp"

struct SolverStats{
    int nodesVisited = 0;
    int backtracks = 0;
    int maxDepth = 0;
};

class Solver{
private:
    SolverStats stats;
    bool isSafe(Board& board, int row, int col, int num);
    bool findBestCell(Board& board, int& row, int& col);
    bool solve(Board& board, int depth);
    int countSolutionsHelper(Board& board);

public:
    bool solveSudoku(Board& board);
    int countSolutions(Board board);
    SolverStats getStats() const;
};