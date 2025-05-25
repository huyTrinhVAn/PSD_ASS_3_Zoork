// ===== File: Player.cpp =====
#include "Player.h"

Player* Player::playerInstance = nullptr;

Player* Player::instance() {
    if (!playerInstance) playerInstance = new Player();
    return playerInstance;
}

Player::Player() {}

void Player::setCurrentRoom(Room* r) { currentRoom = r; }
Room* Player::getCurrentRoom() const { return currentRoom; }

bool Player::addToInventory(std::shared_ptr<Item> item) {
    if (!item) return false;
    inventory.push_back(item);
    return true;
}

std::shared_ptr<Item> Player::removeFromInventory(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == name) {
            auto i = *it;
            inventory.erase(it);
            return i;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Player::getItemFromInventory(const std::string& name) const {
    for (auto& it : inventory)
        if (it->getName() == name)
            return it;
    return nullptr;
}

const std::vector<std::shared_ptr<Item>>& Player::getInventory() const {
    return inventory;
}
