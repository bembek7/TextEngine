#include "Game.h"
#include <fstream>
#include <iostream>

void Game::AddRoom(const Room& room) noexcept
{
	rooms.push_back(std::make_unique<Room>(room));
}

bool Game::TryAdvanceRoom(const std::string& message) noexcept
{
	int nextRoomIndex = rooms[currentRoomIndex]->FindRoomUnderMessage(message);
	if (nextRoomIndex >= 0)
	{
		currentRoomIndex = nextRoomIndex;
		rooms[currentRoomIndex]->Enter();
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::TryAction(const std::string& message) noexcept
{
	return rooms[currentRoomIndex]->TryAction(message);
}

void Game::Start() noexcept
{
	started = true;
	rooms[currentRoomIndex]->Enter();
}

void Game::SaveGame() const noexcept
{
	std::ofstream file("Save", std::ios::binary);
	player.SavePlayer(file);
	auto roomsSize = rooms.size();
	file.write(reinterpret_cast<const char*>(&roomsSize), sizeof(roomsSize));
	for (const auto& room : rooms)
	{
		room->SaveRoom(file);
	}
	file.write(reinterpret_cast<const char*>(&currentRoomIndex), sizeof(currentRoomIndex));
	file.close();
}

bool Game::IsStarted() const noexcept
{
	return started;
}

void Game::LoadLast()
{
	LoadGame("Save");
}

void Game::LoadNew()
{
	LoadGame("DefaultStart");
}

void Game::PrintInventory() const noexcept
{
	player.PrintInventory();
}

void Game::FindItem(Item&& item) noexcept
{
	std::cout << "You found " << item.GetName() << "!" << std::endl;
	player.AddItem(std::move(item));
}

void Game::LoadGame(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't find the save file.");
	}
	player = Player();
	player.LoadPlayer(file);
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
