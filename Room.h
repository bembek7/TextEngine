#pragma once
#include<string>
#include<unordered_map>
 
class Room
{
public:
	Room() = default;
	Room(const std::string& entryDescription)noexcept;
	void Enter() const noexcept;
	void AddRoomLink(const std::string& messageThatLinks, unsigned int roomIndex) noexcept;
	void AddAdditionalDescription(const std::string& messageThatLinks, const std::string& description) noexcept;
	int FindRoomUnderMessage(const std::string& message) noexcept;
	bool TryAction(const std::string& message) noexcept;
	void SaveRoom(std::ofstream& file) const noexcept;
	void LoadRoom(std::ifstream& file);

public:

private:
	std::unordered_map<std::string, unsigned int> links;
	std::unordered_map<std::string, std::string> additionalDescriptions;
	std::string description;
};

