#include "Game.h"

void Game::AddRoom(const Room& room) noexcept
{
	rooms.push_back(std::make_unique<Room>(room));
}

int Game::TryAdvanceRoom(const std::string& message) noexcept
{
	Room* nextRoom = currentRoom->FindRoomUnderMessage(message);
	if (nextRoom)
	{
		currentRoom = nextRoom;
		currentRoom->Enter();
	}
	else
	{
		return -1;
	}
	return 0;
}

void Game::Start() noexcept
{
	if (rooms.size() > 0)
	{
		currentRoom = rooms[0].get();
		currentRoom->Enter();
	}
}
