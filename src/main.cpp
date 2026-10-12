#include "../include/game.hpp"
#include "../include/generator.hpp"
#include "../include/solver.hpp"
#include "../include/benchmark.hpp"
#include "../include/score.hpp"
#include "../include/difficulty.hpp"

#include <iostream>

int main(){
    while(true) {

        std::cout << "\n====================\n";
        std::cout << "     SUDOKU ENGINE   \n";
        std::cout << "====================\n\n";

        std::cout << "1. Play Sudoku\n";
        std::cout << "2. Generate Puzzle\n";
        std::cout << "3. Solve Puzzle\n";
        std::cout << "4. Benchmark\n";
        std::cout << "5. View Leaderboard\n";
        std::cout << "6. Exit\n";

        int choice;
        std::cout << "\nEnter choice: ";
        std::cin >> choice;

        switch(choice) {
            
            case 1: {
                Game game;
                game.start();
                break;
            }

            case 2: {
                Generator generator;
                int choice;

                std::cout << "\nChoose Difficulty:\n";
                std::cout << "1. Easy\n";
                std::cout << "2. Medium\n";
                std::cout << "3. Hard\n";

                std::cout << "Enter choice: ";
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
                        break;
                }

                Board puzzle = generator.generate(level);
                std::cout << "\nGenerated Puzzle:\n\n";
                puzzle.print();
                break;
            }


            case 3: {
                Board board;
                std::cout << "\nEnter Sudoku grid (0 for empty cells):\n";
                for(int i = 0; i < 9; i++){
                    for(int j = 0; j < 9; j++){
                        int value;
                        std::cin >> value;
                        board.set(i,j,value);
                    }
                }

                Solver solver;
                if(solver.solveSudoku(board)){
                    std::cout << "\nSolved Sudoku:\n\n";
                    board.print();
                    SolverStats stats = solver.getStats();
                    std::cout << "\nNodes visited: " << stats.nodesVisited << "\n";
                    std::cout << "Backtracks: " << stats.backtracks << "\n";
                }
                else std::cout << "\nNo solution exists.\n";
                break;
            }



            case 4:{
                int puzzles;
                std::cout << "\nNumber of puzzles to benchmark: ";
                std::cin >> puzzles;
                Benchmark::run(puzzles);
                break;
            }

            case 5:{
                ScoreManager manager;
                manager.displayLeaderboard();
                break;
            }

            case 6:{
                std::cout << "\nExiting Sudoku Engine...\n";
                return 0;
            }

            default:
                std::cout << "\nInvalid choice!\n";

        }

    }
    return 0;
}