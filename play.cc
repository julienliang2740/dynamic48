#include <iostream>
#include "game.h"

int main() {
    // testing values 
    std::string command;
    game currentGame = game(4);
    bool boardChanged = true;

    while (true) {
        if (boardChanged) currentGame.spawn_block();
        std::cout << currentGame;
        if (currentGame.game_over()) {
            std::cout << "Game over" << std::endl;
            break;
        }

        std::cin >> command;

        if (std::cin.fail() || command == "q" || command == "quit") break;
        
        if (command == "w" || command == "up") {
            if (currentGame.up()) {
                boardChanged = true;
                std::cout << "brug bruga" << std::endl;
            }
            else boardChanged = false;
        }
        else if (command == "a" || command == "left") {
            if (currentGame.left()) boardChanged = true;
            else boardChanged = false;
        }
        else if (command == "s" || command == "down") {
            if (currentGame.down()) boardChanged = true;
            else boardChanged = false;
        }
        else if (command == "d" || command == "right") {
            if (currentGame.right()) boardChanged = true;
            else boardChanged = false;
        }
        else if (command == "p" || command == "print") {
            std::cout << currentGame;
            boardChanged = false;
        }
        else {
            std::cout << "Invalid command" << std::endl;
            boardChanged = false;
        }
    }
}
