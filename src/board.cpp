#include "../include/board.hpp"
#include <iostream>

Board::Board() {
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++) grid[i][j]=0;
}

void Board::print() const
{
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++) std::cout<<grid[i][j]<<" ";
        std::cout<<"\n";
    }
}

int Board::get(int row,int col) const{
    return grid[row][col];
}

void Board::set(int row,int col,int value){
    grid[row][col]=value;
}

bool Board::isEmpty(int row,int col) const{
    return grid[row][col]==0;
}

bool Board::isComplete() const{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++) if (grid[i][j]== 0) return false;

    return true;
}