#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

int main() {
    // === Create Rooms ===
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
        "You are standing in an open field west of a white house, with a boarded front door.");

    std::shared_ptr<Room> south = std::make_shared<Room>("south-of-house",
        "You are at the south side of the house. The windows are barred and uninviting.");

    std::shared_ptr<Room> east = std::make_shared<Room>("east-of-house",
        "You are standing in a garden. Overgrown weeds twist between cracked stones.");

    std::shared_ptr<Room> west = std::make_shared<Room>("west-of-house",
        "Thick forest looms behind you. The house wall is covered in moss.");

    std::shared_ptr<Room> behind = std::make_shared<Room>("behind-house",
        "You are behind the house. A path leads deeper into the woods.");

    std::shared_ptr<Room> forest = std::make_shared<Room>("forest",
        "You are in a dense forest. The canopy above blocks most of the light.");

    std::shared_ptr<Room> cave = std::make_shared<Room>("cave",
        "You are in a dark, damp cave. The walls are slick with moisture.");

    std::shared_ptr<Room> tower = std::make_shared<Room>("tower",
        "You stand atop a crumbling stone tower. The wind howls.");

    std::shared_ptr<Room> dungeon = std::make_shared<Room>("dungeon",
        "You are in a cold dungeon beneath the tower. Chains hang from the walls.");

    std::shared_ptr<Room> throne = std::make_shared<Room>("throne-room",
        "You are in a grand hall with a shattered throne at the far end.");

    // === Connect Rooms ===
    Passage::createBasicPassage(start.get(), south.get(), "south", true);
    Passage::createBasicPassage(start.get(), west.get(), "west", true);
    Passage::createBasicPassage(start.get(), east.get(), "east", true);

    Passage::createBasicPassage(south.get(), behind.get(), "east", true);
    Passage::createBasicPassage(behind.get(), forest.get(), "east", true);
    Passage::createBasicPassage(forest.get(), cave.get(), "north", true);
    Passage::createBasicPassage(cave.get(), dungeon.get(), "down", true);
    Passage::createBasicPassage(dungeon.get(), tower.get(), "up", true);
    Passage::createBasicPassage(tower.get(), throne.get(), "north", true);

    // === Launch Game ===
    ZOOrkEngine zoork(start);
    zoork.run();

    return 0;
}
