#include <iostream>
#include <memory>
#include <array>
#include <vector>
using namespace std;

enum class Direction {
    North, 
    South, 
    East, 
    West
};

class MapSite {
public:
    virtual void enter() = 0;
    virtual ~MapSite() = default;
};

class Room: public MapSite {
private:
    int roomNumber;
    array<shared_ptr<MapSite>, 4> sides;   
public:
    Room(): roomNumber{0} {}

    explicit Room(int n): roomNumber{n} {}

    Room& setSide(Direction d, shared_ptr<MapSite> ms) {
        sides[static_cast<size_t>(d)] = std::move(ms);
        cout << "Room::setSide " << static_cast<int>(d) << endl;
        return *this;
    }

    void enter() override {
        cout << "Entering room " << roomNumber << endl;
    }

    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;
};

class Wall: public MapSite {
public:
    Wall() = default;

    void enter() override {
        cout << "You bumped into a wall!" << endl;
    }
};

class Door: public MapSite {
private:
    shared_ptr<Room> room1;
    shared_ptr<Room> room2;
public:
    Door(shared_ptr<Room> r1 = nullptr, shared_ptr<Room> r2 = nullptr): 
        room1{std::move(r1)}, room2{std::move(r2)} {}

    void enter() override {
        cout << "You passed through the door." << endl;
    }

    Door(const Door&) = delete;
    Door& operator=(const Door&) = delete;
};

class Maze {
private:
    vector<shared_ptr<Room>> rooms;
public:
    Maze& addRoom(shared_ptr<Room> r) {
        cout << "Maze::addRoom " << reinterpret_cast<void*>(r.get()) << endl;
        rooms.push_back(std::move(r));
        return *this;
    }
  
    shared_ptr<Room> roomNo(int n) const {
        for (auto& r : rooms) {
            // Example: just return the first room for now
            return r;
        }
        return nullptr;
    }
};

class MazeFactory {
public:
    MazeFactory() = default;
    virtual ~MazeFactory() = default;

    [[nodiscard]]
    unique_ptr<Maze> makeMaze() const {
        return std::make_unique<Maze>();
    }

    [[nodiscard]]
    shared_ptr<Wall> makeWall() const {
        return std::make_shared<Wall>();
    }

    [[nodiscard]]
    shared_ptr<Room> makeRoom(int n) const {
        return std::make_shared<Room>(n);
    }
    
    [[nodiscard]]
    shared_ptr<Door> makeDoor(shared_ptr<Room> r1, shared_ptr<Room> r2) const {
        return std::make_shared<Door>(std::move(r1), std::move(r2));
    }
};

// Example of the Abstract Factory pattern
class MazeGame {
public:
    [[nodiscard]]
    unique_ptr<Maze> createMaze(MazeFactory& factory) {
        unique_ptr<Maze> maze = factory.makeMaze();
        shared_ptr<Room> r1 = factory.makeRoom(1);
        shared_ptr<Room> r2 = factory.makeRoom(2);
        shared_ptr<Door> door = factory.makeDoor(r1, r2);

        maze->addRoom(r1)
            .addRoom(r2);

        r1->setSide(Direction::North, factory.makeWall())
           .setSide(Direction::East, door)
           .setSide(Direction::South, factory.makeWall())
           .setSide(Direction::West, factory.makeWall());

        r2->setSide(Direction::North, factory.makeWall())
           .setSide(Direction::East, factory.makeWall())
           .setSide(Direction::South, factory.makeWall())
           .setSide(Direction::West, door);

        return maze;
    }
};

int main() {
    MazeGame game;
    MazeFactory factory;
    unique_ptr<Maze> maze = game.createMaze(factory);
}
