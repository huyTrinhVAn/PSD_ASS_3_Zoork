// ===== File: ZOOrkEngine.cpp =====
#include "ZOOrkEngine.h"
#include "NullPassage.h"
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
        auto words = tokenizeString(input);
        if (words.empty()) continue;
        auto cmd = words[0];
        std::vector<std::string> args(words.begin() + 1, words.end());

        if (cmd == "go")         handleGoCommand(args);
        else if (cmd == "look" || cmd == "inspect") handleLookCommand(args);
        else if (cmd == "take" || cmd == "get")    handleTakeCommand(args);
        else if (cmd == "drop")   handleDropCommand(args);
        else if (cmd == "inventory" || cmd == "inv") handleInventoryCommand();
        else if (cmd == "quit")   handleQuitCommand(args);
        else                      std::cout << "I don't understand that command." << std::endl;
    }
}

void ZOOrkEngine::handleGoCommand(const std::vector<std::string>& args) {
    if (args.empty()) return;
    std::string dir = args[0];
    if      (dir == "n" || dir == "north") dir = "north";
    else if (dir == "s" || dir == "south") dir = "south";
    else if (dir == "e" || dir == "east")  dir = "east";
    else if (dir == "w" || dir == "west")  dir = "west";
    else if (dir == "u" || dir == "up")    dir = "up";
    else if (dir == "d" || dir == "down")  dir = "down";

    auto room = player->getCurrentRoom();
    auto passage = room->getPassage(dir);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(const std::vector<std::string>& args) {
    auto room = player->getCurrentRoom();
    if (args.empty()) {
        std::cout << room->getDescription() << std::endl;
        auto items = room->getItems();
        if (!items.empty()) {
            std::cout << "Items here:";
            for (auto& it : items) std::cout << " " << it->getName() << ",";
            std::cout << "\b " << std::endl;
        }
        return;
    }
    std::string target = args[0];
    for (size_t i = 1; i < args.size(); ++i) target += " " + args[i];

    // look in room
    if (auto it = room->getItem(target)) {
        std::cout << it->getDescription() << std::endl;
        return;
    }
    // look in inventory
    if (auto it = player->getItemFromInventory(target)) {
        std::cout << it->getDescription() << std::endl;
        return;
    }
    // look direction
    std::string dir = target;
    if      (dir == "n" || dir == "north") dir = "north";
    else if (dir == "s" || dir == "south") dir = "south";
    else if (dir == "e" || dir == "east")  dir = "east";
    else if (dir == "w" || dir == "west")  dir = "west";
    else if (dir == "u" || dir == "up")    dir = "up";
    else if (dir == "d" || dir == "down")  dir = "down";
    if (!dir.empty()) {
        auto passage = room->getPassage(dir);
        if (dynamic_cast<NullPassage*>(passage.get()) == nullptr) {
            std::cout << passage->getDescription() << std::endl;
            return;
        }
    }
    std::cout << "You don't see " << target << " here." << std::endl;
}

void ZOOrkEngine::handleTakeCommand(const std::vector<std::string>& args) {
    if (args.empty()) { std::cout << "Take what?" << std::endl; return; }
    std::string name = args[0];
    for (size_t i = 1; i < args.size(); ++i) name += " " + args[i];

    auto room = player->getCurrentRoom();
    auto item = room->removeItem(name);
    if (item) {
        player->addToInventory(item);
        std::cout << "You take " << name << "." << std::endl;
    } else {
        std::cout << "You don't see " << name << " here." << std::endl;
    }
}

void ZOOrkEngine::handleDropCommand(const std::vector<std::string>& args) {
    if (args.empty()) { std::cout << "Drop what?" << std::endl; return; }
    std::string name = args[0];
    for (size_t i = 1; i < args.size(); ++i) name += " " + args[i];

    auto item = player->removeFromInventory(name);
    if (item) {
        auto room = player->getCurrentRoom();
        room->addItem(item);
        std::cout << "You drop " << name << "." << std::endl;
    } else {
        std::cout << "You are not carrying " << name << "." << std::endl;
    }
}

void ZOOrkEngine::handleInventoryCommand() {
    auto inv = player->getInventory();
    if (inv.empty()) std::cout << "You are carrying nothing." << std::endl;
    else {
        std::cout << "You are carrying:";
        for (auto& it: inv) std::cout << " " << it->getName() << ",";
        std::cout << "\b " << std::endl;
    }
}

void ZOOrkEngine::handleQuitCommand(const std::vector<std::string>&) {
    std::cout << "Are you sure you want to QUIT?" << std::endl << "> ";
    std::string in; std::getline(std::cin, in);
    if (makeLowercase(in) == "y" || makeLowercase(in) == "yes") gameOver = true;
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string& input) {
    std::vector<std::string> toks;
    std::stringstream ss(input);
    std::string t;
    while (std::getline(ss, t, ' ')) toks.push_back(makeLowercase(t));
    return toks;
}

std::string ZOOrkEngine::makeLowercase(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
