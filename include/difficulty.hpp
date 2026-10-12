#pragma once

#include "../include/board.hpp"
#include "../include/solver.hpp"
#include <string>

enum class Difficulty {EASY, MEDIUM, HARD};
class DifficultyRating {
public:
    static std::string calculate(Board board);
};