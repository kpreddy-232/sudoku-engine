#include "../include/game.hpp"
#include "../include/difficulty.hpp"
#include <iostream>

void Game::start() {

    int choice;

    std::cout << "====================\n";
    std::cout << "      SUDOKU GAME    \n";
    std::cout << "====================\n\n";


    std::cout << "Choose Difficulty:\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";

    std::cout << "\nEnter choice: ";
    std::cin >> choice;

    Difficulty level;

    switch(choice) {
        case 1:
            level = Difficulty::EASY;
            break;

        case 2:
            level = Difficulty::MEDIUM;
            break;

        case 3:
            level = Difficulty::HARD;
            break;

        default:
            std::cout << "Invalid choice\n";
            return;
    }

    board = generator.generate(level);
    
    // Starting score based on difficulty
    switch(level) {
       case Difficulty::EASY:
            currentDifficulty = "Easy";
            scoreManager.setDifficultyScore(1000);
            break;

        case Difficulty::MEDIUM:
            currentDifficulty = "Medium";
            scoreManager.setDifficultyScore(2000);
             break;

        case Difficulty::HARD:
            currentDifficulty = "Hard";
            scoreManager.setDifficultyScore(3000);
            break;
    }

    std::cout << "\nGenerated Sudoku:\n\n";
    board.print();
    std::cout << "\nGame started!\n";

    //Game starts!!
    timer.start();
    while(true) {
        int option;

        std::cout << "\n1. Make Move\n";
        std::cout << "2. Get Hint\n";
        std::cout << "3. Solve Sudoku\n";
        std::cout << "Choose option: ";
        std::cin >> option;

        if(option == 2) {
            int row, col, value;
            if(hint.getHint(board,row,col,value)) {
                std::cout
                << "\nHint: Put "
                << value
                << " at row "
                << row + 1
                << " column "
                << col + 1
                << "\n";

                scoreManager.addHint();
            }
            else std::cout << "No hint available\n";
            continue;
        }

        if(option == 3){
            Board solved = board;
            if(solver.solveSudoku(solved)) {
                std::cout << "\nSolved Sudoku:\n\n";
                solved.print();

                scoreManager.applySolvePenalty();
                timer.stop();

                SolverStats stats = solver.getStats();
                std::cout << "\nSolver Statistics:\n";

                std::cout << "Nodes visited: " << stats.nodesVisited << "\n";
                std::cout << "Backtracks: " << stats.backtracks << "\n";
                std::cout << "Maximum depth: " << stats.maxDepth << "\n";
                std::cout << "\nGame ended. Solution displayed.\n";

                displayScore();
            }
            else std::cout << "Cannot solve puzzle\n";
            break;
        }

        if(option == 1) {

            int row, col, num;

            std::cout << "\nEnter row (1-9): ";
            std::cin >> row;

            std::cout << "Enter column (1-9): ";
            std::cin >> col;

            std::cout << "Enter number (1-9): ";
            std::cin >> num;

            row--; col--;

            if(row < 0 || row >= 9 ||
               col < 0 || col >= 9 ||
               num < 1 || num > 9) {
                std::cout << "Invalid input!\n";
                continue;
            }

            if(!board.isEmpty(row,col)) {
                std::cout << "Cell already filled!\n";
                continue;
            }

            Board temp = board;
            temp.set(row,col,num);
            if(solver.solveSudoku(temp)) {
                board.set(row,col,num);
                scoreManager.addMove();
                std::cout << "\nMove accepted!\n";
                board.print();
                if(board.isComplete()) {
                    timer.stop();
                    displayScore();
                    break;
                }
            }
            else {
                std::cout << "\nWrong move!\n";
                scoreManager.addWrongMove();
            }
        }
    }
}

void Game::displayScore(){
    scoreManager.setTime(timer.getElapsedSeconds());
    scoreManager.displayScore();
    scoreManager.saveScore(currentDifficulty);
}