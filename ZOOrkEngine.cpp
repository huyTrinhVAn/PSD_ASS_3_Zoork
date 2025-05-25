#include "ZOOrkEngine.h"
#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include "NullPassage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        if (words.empty()) continue;
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if (command == "look" || command == "inspect") {
            handleLookCommand(arguments);
        } else if (command == "take" || command == "get") {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command." << std::endl;
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) return;
    std::string arg = arguments[0];
    std::string direction;
    if (arg == "n" || arg == "north")      direction = "north";
    else if (arg == "s" || arg == "south") direction = "south";
    else if (arg == "e" || arg == "east")  direction = "east";
    else if (arg == "w" || arg == "west")  direction = "west";
    else if (arg == "u" || arg == "up")    direction = "up";
    else if (arg == "d" || arg == "down")  direction = "down";
    else direction = arg;

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* current = player->getCurrentRoom();
    // Describe current room if no target
    if (arguments.empty()) {
        std::cout << current->getDescription() << std::endl;
        return;
    }
    // Otherwise treat target as direction
    std::string target = arguments[0];
    std::string dir;
    if (target == "n" || target == "north")      dir = "north";
    else if (target == "s" || target == "south") dir = "south";
    else if (target == "e" || target == "east")  dir = "east";
    else if (target == "w" || target == "west")  dir = "west";
    else if (target == "u" || target == "up")    dir = "up";
    else if (target == "d" || target == "down")  dir = "down";
    else dir = target;

    auto passage = current->getPassage(dir);
    if (dynamic_cast<NullPassage*>(passage.get()) == nullptr) {
        std::cout << passage->getDescription() << std::endl;
    } else {
        std::cout << "You don't see " << target << " here." << std::endl;
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    std::cout << "This functionality is not yet enabled." << std::endl;
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    std::cout << "This functionality is not yet enabled." << std::endl;
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::cout << "Are you sure you want to QUIT?" << std::endl << "> ";
    std::string input;
    std::getline(std::cin, input);
    std::string quitStr = makeLowercase(input);
    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }
    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}
