#include "../include/score.hpp"
#include "../include/difficulty.hpp"
#include <iostream>
#include <fstream> // For reading and writing the leaderboard.txt file
#include <vector>
#include <algorithm>

bool cmp (playerEntry a, playerEntry b){
    return (a.score != b.score) ? a.score > b.score : a.time < b.time;
}

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
    std::ifstream file("leaderboard.txt");
    
    std::vector <playerEntry> currDiffScores;
    std::vector <playerEntry> otherScores;

    std::string d, n;
    int s, t;

    while (file >> d >> s >> t >> n){
        if (d == difficulty) currDiffScores.push_back({d,s,t,n});
        else otherScores.push_back({d,s,t,n});
    }
    file.close();
    
    currDiffScores.push_back({difficulty, score, time, "temp"});

    std::sort(currDiffScores.begin(), currDiffScores.end(), cmp);

    int rank = 0;
    for (int i = 0; i < currDiffScores.size(); i++){
        if (currDiffScores[i].playerName == "temp") {
            rank = i + 1;
            break;
        }
    }
    if (rank > 5) return;
    // if rank > 5, simply output the current player's perf (already happens) and exit

    if (rank <= 5){
        std::string name;
        char confirm = 'n';
        std::string pos = "";
        switch (rank){
            case (1) :{
                break;
            }
            case (2) :{
                pos = "second";
                break;
            }
            case (3) :{
                pos = "third";
                break;
            }
            case (4) :{
                pos = "fourth";
                break;
            }
            case (5): {
                pos = "fifth";
                break;
            }
        }
        std::cout << "\nCongratulations! You got an all time " << pos << " highest score in the " << difficulty << "Mode!\n";
        
        while (confirm != 'y' && confirm != 'Y') {
            std::cout << "Please enter your name here (No spaces): ";
            std::cin >> name;
            std::cout << "Confirm the name : " << name << " ? (y/n): ";
            std::cin >> confirm;
        }   
        currDiffScores[rank - 1].playerName = name;
    }

    if (currDiffScores.size() > 5) currDiffScores.pop_back();

    std::ofstream Outfile("leaderboard.txt", std::ios::trunc);
    
    if (Outfile) { // Check outFile, not file
        for (const auto& entry : otherScores) {
            Outfile << entry.difficulty << " " << entry.score << " " << entry.time << " " << entry.playerName << "\n";
        }
        for (const auto& entry : currDiffScores) {
            Outfile << entry.difficulty << " " << entry.score << " " << entry.time << " " << entry.playerName << "\n";
        }
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

    std::string difficulty, name;
    int score;
    int time;

    while(file >> difficulty >> score >> time >> name)
    {
        std::cout 
        << "[" << difficulty << "] " 
        << name 
        << " | Score: " << score 
        << " | Time: " << time << "s\n";
    }


}