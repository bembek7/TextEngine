#pragma once
#include "Room.h"
#include <memory>

class Game
{
public:
	void AddRoom(const Room& room) noexcept;
	void Start() noexcept;
	int TryAdvanceRoom(const std::string& message) noexcept;
	void SaveGame() const noexcept;
	bool IsStarted() const noexcept;
	void LoadLast();
	void LoadNew();

private:
	void LoadGame(const std::string& fileName);

private:
	std::vector<std::unique_ptr<Room>>rooms;
	unsigned int currentRoomIndex = 0;
	bool started = false;
};

