// ===== File: Room.cpp =====
#include "Room.h"
#include "NullPassage.h"
#include <iostream>
#include "RoomDefaultEnterCommand.h"
Room::Room(const std::string& n, const std::string& d) : Location(n, d) {
    setEnterCommand(std::make_shared<RoomDefaultEnterCommand>(this));
}

Room::Room(const std::string& n, const std::string& d, std::shared_ptr<Command> c)
    : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string& dir, std::shared_ptr<Passage> p) {
    passageMap[dir] = std::move(p);
}

std::shared_ptr<Passage> Room::getPassage(const std::string& dir) {
    if (passageMap.count(dir)) return passageMap[dir];
    std::cout << "It is impossible to go " << dir << "!" << std::endl;
    return std::make_shared<NullPassage>(this);
}

void Room::addItem(std::shared_ptr<Item> item) {
    if (item) items.push_back(item);
}

std::shared_ptr<Item> Room::removeItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            auto i = *it;
            items.erase(it);
            return i;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Room::getItem(const std::string& name) const {
    for (auto& it : items) if (it->getName() == name) return it;
    return nullptr;
}

std::vector<std::shared_ptr<Item>> Room::getItems() const {
    return items;
}
