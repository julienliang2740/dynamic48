#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include "game.h"

game::game(int default_dim): dimensions(default_dim), gameBoard(dimensions, std::vector<int>(dimensions)), g(rd()) {
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            gameBoard[i][j];
        }
    }
}

game::~game() {}

int game::get_dimensions() const {
    return this->dimensions;
}

std::vector<std::vector<int>> game::get_board() const {
    return this->gameBoard;
}

bool game::compare_board(std::vector<std::vector<int>> board1, std::vector<std::vector<int>>board2) {
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            if (board1[i][j] != board2[i][j]) return false;
        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void game::spawn_block() {
    std::vector<int> innerSpots;
    std::vector<int> outerSpots;
    innerSpots.reserve(dimensions);
    outerSpots.reserve(dimensions);
    for (int i = 0; i < dimensions; ++i) innerSpots.push_back(i);
    for (int i = 0; i < dimensions; ++i) outerSpots.push_back(i);

    // Shuffle the vectors
    shuffle(innerSpots.begin(), innerSpots.end(), g);
    shuffle(outerSpots.begin(), outerSpots.end(), g);

    std::uniform_int_distribution<> dist(1, 10);
    int random_number = dist(g);
    int block_number;
    if (random_number == 1) block_number = 4;
    else block_number = 2;
    
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            if (gameBoard[outerSpots[i]][innerSpots[j]] == 0) {
                gameBoard[outerSpots[i]][innerSpots[j]] = block_number;
                std::cout << "added block" << std::endl;
                std::cout << outerSpots[i] << std::endl;
                std::cout << innerSpots[j] << std::endl;
                return;
            }
        }
    }
    
    // If there's no free spaces
    return;
}

bool game::game_over() {
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            if (gameBoard[i][j] == 0) return false;
            
            if (i-1 >= 0 && i-1 < dimensions) {
                if (gameBoard[i][j] == gameBoard[i-1][j]) return false;
            }
            else if (i+1 >= 0 && i+1 < dimensions) {
                if (gameBoard[i][j] == gameBoard[i+1][j]) return false;
            }
            else if (j-1 >= 0 && j-1 < dimensions) {
                if (gameBoard[i][j] == gameBoard[i][j-1]) return false;
            }
            else if (j+1 >= 0 && j+1 < dimensions) {
                if (gameBoard[i][j] == gameBoard[i][j+1]) return false;
            }
        }
    }
    return true;
}

std::vector<int> game::merge_single_line(const std::vector<int> & line) {
    // each line has len = this.dimensions
    std::vector<int> nozeroes;
    for (int i = 0; i < dimensions; ++i) if (line[i] != 0) nozeroes.push_back(line[i]);

    std::vector<int> mergedline;
    for (int i = 0; i < nozeroes.size(); ++i) {
        if (i < nozeroes.size() - 1 && nozeroes[i] == nozeroes [i+1]) {
            mergedline.push_back(nozeroes[i]*2);
            ++i;
        }
        else {
            mergedline.push_back(nozeroes[i]);
        }
    }

    while (mergedline.size() < dimensions) mergedline.push_back(0);

    return mergedline;
}

bool game::up() {
    std::vector<std::vector<int>> prevBoard = gameBoard;
    for (int i = 0; i < dimensions; ++i) {
        std::vector<int> line;
        line.reserve(dimensions);
        for (int j = 0; j < dimensions; ++j) line.push_back(gameBoard[j][i]);
        std::vector<int> mergedline = merge_single_line(line);
        for (int j = 0; j < dimensions; ++j) gameBoard[j][i] = mergedline[j];
    }
    return !compare_board(prevBoard, gameBoard);
}

bool game::down() {
    std::vector<std::vector<int>> prevBoard = gameBoard;
    for (int i = 0; i < dimensions; ++i) {
        std::vector<int> line;
        line.reserve(dimensions);
        for (int j = 0; j < dimensions; ++j) line.push_back(gameBoard[dimensions-j-1][i]);
        std::vector<int> mergedline = merge_single_line(line);
        for (int j = 0; j < dimensions; ++j) gameBoard[dimensions-j-1][i] = mergedline[j];
    }
    return !compare_board(prevBoard, gameBoard);
}

bool game::left() {
    std::vector<std::vector<int>> prevBoard = gameBoard;
    for (int i = 0; i < dimensions; ++i) {
        std::vector<int> line;
        line.reserve(dimensions);
        for (int j = 0; j < dimensions; ++j) line.push_back(gameBoard[i][j]);
        std::vector<int> mergedline = merge_single_line(line);
        for (int j = 0; j < dimensions; ++j) gameBoard[i][j] = mergedline[j];
    }
    return !compare_board(prevBoard, gameBoard);
}

bool game::right() {
    std::vector<std::vector<int>> prevBoard = gameBoard;
    for (int i = 0; i < dimensions; ++i) {
        std::vector<int> line;
        line.reserve(dimensions);
        for (int j = 0; j < dimensions; ++j) line.push_back(gameBoard[i][dimensions-j-1]);
        std::vector<int> mergedline = merge_single_line(line);
        for (int j = 0; j < dimensions; ++j) gameBoard[i][dimensions-j-1] = mergedline[j];
    }
    return !compare_board(prevBoard, gameBoard);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & out, const game & game) {
    int dimensions = game.get_dimensions();
    std::vector<std::vector<int>> gameBoard = game.get_board();

    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) out << "o-------"; out << "o" << std::endl;
        for (int j = 0; j < dimensions; ++j) out << "|       "; out << "|" << std::endl;
        for (int j = 0; j < dimensions; ++j) out << "|" << std::left << std::setw(7) << gameBoard[i][j]; out << "|" << std::endl;
        for (int j = 0; j < dimensions; ++j) out << "|       "; out << "|" << std::endl;
    }
    for (int j = 0; j < dimensions; ++j) out << "o-------"; out << "o" << std::endl;

    return out;
}

bool operator !=(const game & game1, const game & game2) {
    // will only be called on two boards with the same dimensions
    int dimensions = game1.get_dimensions();
    std::vector<std::vector<int>> gameBoard1 = game1.get_board();
    std::vector<std::vector<int>> gameBoard2 = game2.get_board();
    for (int i = 0; i < dimensions; ++i) {
        for (int j = 0; j < dimensions; ++j) {
            if (gameBoard1[i][j] != gameBoard2[i][j]) {
                return true;
            }
        }
    }
    return false;
}

