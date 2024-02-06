#include "Game.h"
#include <fstream>

void Game::AddRoom(const Room& room) noexcept
{
	rooms.push_back(std::make_unique<Room>(room));
}

int Game::TryAdvanceRoom(const std::string& message) noexcept
{
	int nextRoomIndex = rooms[currentRoomIndex]->FindRoomUnderMessage(message);
	if (nextRoomIndex >= 0)
	{
		currentRoomIndex = nextRoomIndex;
		rooms[currentRoomIndex]->Enter();
	}
	else
	{
		return -1;
	}
	return 0;
}

void Game::Start() noexcept
{
	rooms[currentRoomIndex]->Enter();
}

void Game::SaveGame() const noexcept
{
	std::ofstream file("Save", std::ios::binary);
	auto roomsSize = rooms.size();
	file.write(reinterpret_cast<const char*>(&roomsSize), sizeof(roomsSize));
	for (const auto& room : rooms)
	{
		room->SaveRoom(file);
	}
	file.write(reinterpret_cast<const char*>(&currentRoomIndex), sizeof(currentRoomIndex));
	file.close();
}

void Game::LoadGame() noexcept
{
	std::ifstream file("Save", std::ios::binary);
	size_t roomsNr;
	file.read(reinterpret_cast<char*>(&roomsNr), sizeof(roomsNr));
	for (size_t i = 0; i < roomsNr; i++)
	{
		Room room;
		room.LoadRoom(file);
		rooms.push_back(std::make_unique<Room>(std::move(room)));
	}
	file.read(reinterpret_cast<char*>(&currentRoomIndex), sizeof(currentRoomIndex));
	file.close();
}
