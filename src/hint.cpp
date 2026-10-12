#include "../include/hint.hpp"

bool Hint::getHint(Board& board, int& row, int& col, int& value) {
    Board solved = board;
    if(!solver.solveSudoku(solved)) return false;
    //solveSudoku calls findBestCell function
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board.isEmpty(i,j)){
                row = i;
                col = j;
                value = solved.get(i,j);
                return true;
            }
        }
    }
    return false;
}