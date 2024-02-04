#pragma once
#include "Room.h"
#include <memory>

class Game
{
public:
	void AddRoom(const Room& room) noexcept;
	int TryAdvanceRoom(const std::string& message) noexcept;
	void Start() noexcept;
private:
	std::vector<std::unique_ptr<Room>>rooms;
	Room* currentRoom = nullptr;
};

