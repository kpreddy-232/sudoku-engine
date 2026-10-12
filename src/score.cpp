#include "../include/score.hpp"
#include <iostream>
#include <fstream> // For reading and writing the leaderboard.txt file

ScoreManager::ScoreManager() {
    score = 0;
    moves = 0;
    hintsUsed = 0;
    wrongMoves = 0;
    time = 0;
}

void ScoreManager::setDifficultyScore(int points) {
    score = points;
}

void ScoreManager::setTime(int seconds){
    time = seconds;
}

void ScoreManager::addMove() {
    moves++;
    score += 10; //+10 on a correct answer
}

void ScoreManager::addHint() {
    hintsUsed++;
    score -= 100; //-100 points on using hints
}

void ScoreManager::addWrongMove() {
    wrongMoves++;
    score -= 50; // Penalty  for wrong move
}

void ScoreManager::applySolvePenalty() {
    score -= 500; // penalty for early quit
}

int ScoreManager::getScore() const {
    return score;
}

void ScoreManager::displayScore() const {

    std::cout << "\n====================\n";
    std::cout << "  PUZZLE COMPLETED\n";
    std::cout << "====================\n";

    std::cout << "\nMoves: " << moves << "\n";
    std::cout << "Hints Used: " << hintsUsed << "\n";
    std::cout << "Wrong Moves: " << wrongMoves << "\n";
    std::cout << "Final Score: " << score << "\n";
    std::cout << "Time: " << time << " seconds\n";
}



void ScoreManager::saveScore(std::string difficulty) {
    std::ofstream file("leaderboard.txt", std::ios::app);
    if(file) {
        file << difficulty << " "
             << score << " "
             << time
             << "\n";

    }

}

void ScoreManager::displayLeaderboard() {
    std::ifstream file("leaderboard.txt");
    if(!file) {
        std::cout << "\nNo scores available.\n";
        return;
    }

    std::cout << "\n====================\n";
    std::cout << "    LEADERBOARD\n";
    std::cout << "====================\n\n";

    std::string difficulty;
    int score;
    int time;

    while(file >> difficulty >> score >> time)
    {
        std::cout
        << difficulty
        << " | Score: "
        << score
        << " | Time: "
        << time
        << " seconds\n";

    }


}