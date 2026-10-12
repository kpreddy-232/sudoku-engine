#include "../include/solver.hpp"

bool Solver::isSafe(Board& board, int row, int col, int num) {
    // Row check
    for(int j = 0; j < 9; j++) 
        if(board.get(row,j) == num) return false;
    
    // Column check
    for(int i = 0; i < 9; i++)
        if(board.get(i,col) == num) return false;
    
    // 3x3 grid check
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            if(board.get(startRow+i,startCol+j) == num) return false;
    }
    return true;
}

bool Solver::findBestCell(Board& board, int& row, int& col){

    int minimumOptions = 10;
    bool found = false;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board.isEmpty(i,j)){
                int options = 0;
                for(int num = 1; num <= 9; num++){
                    if(isSafe(board,i,j,num)) options++;
                }

                if(options < minimumOptions){
                    minimumOptions = options;
                    row = i;
                    col = j;
                    found = true;
                    // Best possible case
                    if(options == 1) return true;
                }
            }
        }
    }
    return found;
}

bool Solver::solve(Board& board, int depth) {
    stats.nodesVisited++;
    if(depth > stats.maxDepth) stats.maxDepth = depth;
    int row = -1;
    int col = -1;

    // MRV selection
    if(!findBestCell(board,row,col)) return true;
    //Decreases the complexity from O(9^81) to O(9*81)

    for(int num = 1; num <= 9; num++) {
        if(isSafe(board,row,col,num)) {
            board.set(row,col,num);
            if(solve(board,depth+1)) return true;
            board.set(row,col,0);
            stats.backtracks++;
        }
    }
    return false;
}

bool Solver::solveSudoku(Board& board) {
    stats = SolverStats();
    return solve(board,0);
}

int Solver::countSolutionsHelper(Board& board){ 
    int row = -1;
    int col = -1;

    if(!findBestCell(board,row,col)) return 1;
    int solutions = 0;
    for(int num = 1; num <= 9; num++){
        if(isSafe(board,row,col,num)){
            board.set(row,col,num);
            solutions += countSolutionsHelper(board);
            board.set(row,col,0);
            // Stop after multiple solutions
            if(solutions > 1) return solutions;
        }
    }
    return solutions;
}

int Solver::countSolutions(Board board) {
    return countSolutionsHelper(board);
}

SolverStats Solver::getStats() const {
    return stats;
}