#pragma once
#include<string>
#include <unordered_map>

class Room
{
public:
	Room(const std::string& entryDescription)noexcept;
	void Enter() const noexcept;
	void AddRoomLink(const std::string& messageThatLinks, Room* room) noexcept;
	Room* FindRoomUnderMessage(const std::string& message) noexcept;

private:

public:

private:
	std::unordered_map<std::string, Room*> links;
	std::string description;
};

