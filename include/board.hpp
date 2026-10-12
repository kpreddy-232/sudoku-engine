#pragma once

class Board {
private:
    int grid[9][9];

public:
    Board();
    void set(int row,int col,int value);
    int get(int row,int col) const;
    bool isEmpty(int row,int col) const;
    void print() const;
    bool isComplete() const;
};