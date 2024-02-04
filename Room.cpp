#include "Room.h"
#include<iostream>

Room::Room(const std::string& entryDescription) noexcept :
	description(entryDescription)
{
	;
}

void Room::Enter() const noexcept
{
	std::cout << description << std::endl;
}

void Room::AddRoomLink(const std::string& messageThatLinks, Room* room) noexcept
{
	links.insert({ messageThatLinks, room });
}

Room* Room::FindRoomUnderMessage(const std::string& message) noexcept
{
	const auto it = links.find(message);
	if (it != links.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}


