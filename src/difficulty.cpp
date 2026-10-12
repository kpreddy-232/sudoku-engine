#include "../include/difficulty.hpp"

std::string DifficultyRating::calculate(Board board){
    int emptyCells = 0;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board.isEmpty(i,j)) emptyCells++;

    Solver solver;
    solver.solveSudoku(board);

    SolverStats stats = solver.getStats();
    //We get number of nodes visited and number of backtracks
    //This is directly used in determining how difficult the board is
    //More backtracks typically indicates more difficult puzzles

    /*
        Difficulty based on solving complexity:
        Easy:
        - Few empty cells
        - Low search effort (Low backtracking)

        Medium:
        - Moderate search effort (Relatively higher node visits, moderate backtracking)

        Hard:
        - Large search tree (High backtracking)
    */

    if(stats.nodesVisited < 500 && stats.backtracks < 100 && emptyCells <= 40) return "Easy";
    else if(stats.nodesVisited < 5000 && stats.backtracks < 1000) return "Medium";
    
    else return "Hard";
}