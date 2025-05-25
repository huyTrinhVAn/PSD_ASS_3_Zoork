// ===== File: Room.h =====
#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include "Location.h"
#include "Item.h"

class Passage;
class Room : public Location {
public:
    Room(const std::string& name, const std::string& desc);
    Room(const std::string& name, const std::string& desc, std::shared_ptr<Command> cmd);

    void addPassage(const std::string& dir, std::shared_ptr<Passage> p);
    std::shared_ptr<Passage> getPassage(const std::string& dir);
    void removePassage(const std::string &);
    void addItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> removeItem(const std::string& name);
    std::shared_ptr<Item> getItem(const std::string& name) const;
    std::vector<std::shared_ptr<Item>> getItems() const;

protected:
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::vector<std::shared_ptr<Item>> items;
};

#endif // ZOORK_ROOM_H
