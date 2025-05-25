// ===== File: Player.h =====
#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Room.h"
#include "Item.h"
#include <vector>
#include <memory>

class Player {
public:
    static Player* instance();
    void setCurrentRoom(Room* room);
    Room* getCurrentRoom() const;

    bool addToInventory(std::shared_ptr<Item> item);
    std::shared_ptr<Item> removeFromInventory(const std::string& name);
    std::shared_ptr<Item> getItemFromInventory(const std::string& name) const;
    const std::vector<std::shared_ptr<Item>>& getInventory() const;

private:
    Player();
    static Player* playerInstance;
    Room* currentRoom{nullptr};
    std::vector<std::shared_ptr<Item>> inventory;
};

#endif // ZOORK_PLAYER_H
