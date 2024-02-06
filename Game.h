#pragma once
#include "Room.h"
#include <memory>

class Game
{
public:
	friend class CommandsController;

	void AddRoom(const Room& room) noexcept;
	void Start() noexcept;
	void LoadGame() noexcept;

private:
	int TryAdvanceRoom(const std::string& message) noexcept;
	void SaveGame() const noexcept;

private:
	std::vector<std::unique_ptr<Room>>rooms;
	unsigned int currentRoomIndex = 0;
};

