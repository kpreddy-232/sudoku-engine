#pragma once
#include <string>
#include <vector>
#include <algorithm>

struct playerEntry{
    std::string difficulty;
    int score;
    int time;
    std::string playerName;
};

class ScoreManager{
private:
    int score;
    int moves;
    int hintsUsed;
    int wrongMoves;
    int time;

public:
    ScoreManager();
    void setTime(int seconds);
    void addMove();
    void addHint();
    void addWrongMove();
    void applySolvePenalty();
    void setDifficultyScore(int points);
    int getScore() const;
    void displayScore() const;
    void saveScore(std::string difficulty);
    void displayLeaderboard();
};