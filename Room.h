#pragma once
#include<string>
#include <unordered_map>

class Game;

class Room
{
public:
	Room() = default;
	Room(const std::string& entryDescription)noexcept;
	void Enter() const noexcept;
	void AddRoomLink(const std::string& messageThatLinks, unsigned int roomIndex) noexcept;
	int FindRoomUnderMessage(const std::string& message) noexcept;
	void SaveRoom(std::ofstream& file) const noexcept;
	void LoadRoom(std::ifstream& file) noexcept;

public:

private:
	std::unordered_map<std::string, unsigned int> links;
	std::string description;
};

