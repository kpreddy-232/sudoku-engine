#include "../include/benchmark.hpp"
#include "../include/generator.hpp"
#include "../include/solver.hpp"
#include "../include/difficulty.hpp"

#include <iostream>
#include <chrono>

void Benchmark::run(int puzzles){

    Generator generator;

    long long totalNodes = 0;
    long long totalBacktracks = 0;

    double totalTime = 0;

    for(int i = 0; i < puzzles; i++){
        Difficulty level;
        if (i < puzzles/6) level = Difficulty::EASY;
        else if (i < puzzles/2) level = Difficulty::MEDIUM;
        else level = Difficulty::HARD;
        // Tests Easy, Medium and Hard Puzzles in a ratio of 1:2:3 for the benchmark
        
        Board board = generator.generate(level);
        Solver solver;

        auto start = std::chrono::high_resolution_clock::now();
        solver.solveSudoku(board);
        auto end = std::chrono::high_resolution_clock::now();

        double time = std::chrono::duration<double, std::milli> (end-start).count();

        SolverStats stats = solver.getStats();

        totalNodes += stats.nodesVisited;
        totalBacktracks += stats.backtracks;
        totalTime += time;

    }

    std::cout << "\nBenchmark Results\n";
    std::cout << "====================\n";
    std::cout << "Total Puzzles tested: " << puzzles << "\n";
    std::cout << "Easy : " << puzzles / 6 << ", Medium : " << puzzles / 3 << ", Hard : " << puzzles / 2 << '\n';
    std::cout << "Average Nodes: " << totalNodes / puzzles << "\n";
    std::cout << "Average Backtracks: " << totalBacktracks / puzzles << "\n";
    std::cout << "Average Time(ms): " << totalTime / puzzles << "\n";
}