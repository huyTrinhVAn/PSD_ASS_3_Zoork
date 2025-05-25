// ===== File: ZOOrkEngine.h =====
#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

class ZOOrkEngine {
public:
    explicit ZOOrkEngine(std::shared_ptr<Room> start);
    void run();

private:
    bool gameOver = false;
    Player* player;

    void handleGoCommand(const std::vector<std::string>& args);
    void handleLookCommand(const std::vector<std::string>& args);
    void handleTakeCommand(const std::vector<std::string>& args);
    void handleDropCommand(const std::vector<std::string>& args);
    void handleInventoryCommand();
    void handleQuitCommand(const std::vector<std::string>& args);

    static std::vector<std::string> tokenizeString(const std::string& input);
    static std::string makeLowercase(std::string s);
};

#endif // ZOORK_ZOORKENGINE_H
