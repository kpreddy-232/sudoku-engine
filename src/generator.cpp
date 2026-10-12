#include "../include/generator.hpp"
#include "../include/difficulty.hpp"

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Generator::Generator() {

    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    gen = mt19937(seed);
    //Generates pseudo-random numbers
}

bool Generator::fillBoard(Board& board) {

    int row = -1;
    int col = -1;

    bool emptyFound = false;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(board.isEmpty(i,j)) {
                row = i;
                col = j;
                emptyFound = true;
                break;
            }
        }

        if(emptyFound) break;
    }

    if(!emptyFound) return true;

    vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    shuffle(numbers.begin(), numbers.end(), gen);

    for(int num : numbers) {
        bool safe = true;
        for(int j = 0; j < 9; j++) {
            if(board.get(row,j) == num) {
                safe = false;
                break;
            }
        } // Check if safe in row 

        for(int i = 0; i < 9; i++) {
            if(board.get(i,col) == num) {
                safe = false;
                break;
            }
        } // Check if safe in column

        int startRow = row - row % 3; 
        int startCol = col - col % 3;

        //Check if safe in the 3x3 grid.
        for(int i = 0; i < 3 && safe; i++) {
            for(int j = 0; j < 3; j++) {
                if(board.get(startRow+i,startCol+j) == num) {
                    safe = false;
                    break;
                }
            }
        }

        if(safe){
            board.set(row,col,num); // grid[row][col] = num; 
            if(fillBoard(board)) return true; // The table is generated successfully
            board.set(row,col,0); // Deadend
        }
    }
    return false; // Eventually lead to an nsolvable board, reset the grid (grid[row][col] = 0)
}


void Generator::removeNumbers(Board& board, int holes) {

    vector<pair<int,int>> positions;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) positions.push_back({i,j});
    }

    shuffle(positions.begin(), positions.end(), gen);
    for(auto pos : positions) {
        if(holes <= 0) break; // No of holes fulfilled

        int row = pos.first;
        int col = pos.second;

        if(board.get(row,col) == 0) continue;

        int backup = board.get(row,col);

        board.set(row,col,0);

        int solutions = solver.countSolutions(board); 
        //Count the number of Solns. Must be 1 (Unique solution)

        if(solutions == 1) holes--;
        else board.set(row,col,backup);
    }
}


int Generator::getHoleCount(Difficulty level) {
    switch(level) {
        case Difficulty::EASY:
            return 35;
        case Difficulty::MEDIUM:
            return 45;
        case Difficulty::HARD:
            return 55;
    }
    return 40;
}

Board Generator::generateCandidate() {
    Board board;
    fillBoard(board);
    return board;
}


Board Generator::generate(Difficulty level) {
    Board bestBoard; //Create a Board (9x9 grid)
    int targetHoles = getHoleCount(level);

    for(int attempt = 0; attempt < 20; attempt++) {
        Board board = generateCandidate();
        removeNumbers(board,targetHoles); 
        //Removes targetHoles number of numbers in the grid;
        
        string rating = DifficultyRating::calculate(board);

        if(level == Difficulty::EASY && rating == "Easy") return board;
        if(level == Difficulty::MEDIUM && rating == "Medium") return board;
        if(level == Difficulty::HARD && rating == "Hard") return board;

        bestBoard = board;
    }
    return bestBoard;
}