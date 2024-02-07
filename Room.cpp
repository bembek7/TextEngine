#include "Room.h"
#include <iostream>
#include "Game.h"
#include <fstream>

Room::Room(const std::string& entryDescription) noexcept :
	description(entryDescription)
{
	;
}

void Room::Enter() const noexcept
{
	std::cout << description << std::endl;
}

void Room::AddRoomLink(const std::string& messageThatLinks, unsigned int roomIndex) noexcept
{
	links.emplace(messageThatLinks, roomIndex);
}

void Room::AddAdditionalDescription(const std::string& messageThatLinks, const std::string& description) noexcept
{
	additionalDescriptions.emplace(messageThatLinks, description);
}

int Room::FindRoomUnderMessage(const std::string& message) noexcept
{
	const auto it = links.find(message);
	if (it != links.end())
	{
		return it->second;
	}
	else
	{
		return -1;
	}
}

bool Room::TryAction(const std::string& message) noexcept
{
	const auto it = additionalDescriptions.find(message);
	if (it != additionalDescriptions.end())
	{
		std::cout << it->second << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Room::SaveRoom(std::ofstream& file) const noexcept
{
	auto linksSize = links.size();
	file.write(reinterpret_cast<const char*>(&linksSize), sizeof(linksSize));
	for (const auto& item : links)
	{
		auto linkingMessageSize = item.first.size() + 1; // incrementing because of null termination sign
		file.write(reinterpret_cast<const char*>(&linkingMessageSize), sizeof(linkingMessageSize));
		file.write(item.first.c_str(), linkingMessageSize);
		file.write(reinterpret_cast<const char*>(&item.second), sizeof(item.second));
	}
	auto descriptionSize = description.size() + 1; // incrementing because of null termination sign
	file.write(reinterpret_cast<const char*>(&descriptionSize), sizeof(descriptionSize));
	file.write(description.c_str(), descriptionSize);
}

void Room::LoadRoom(std::ifstream& file)
{
	size_t linksNr;
	file.read(reinterpret_cast<char*>(&linksNr), sizeof(linksNr));
	for (size_t i = 0; i < linksNr; i++)
	{
		size_t linkingMessageSize;
		std::string linkingMessage;
		unsigned int linkedRoomIndex;
		file.read(reinterpret_cast<char*>(&linkingMessageSize), sizeof(linkingMessageSize));
		char* messageBuffer = new char[linkingMessageSize];
		file.read(messageBuffer, linkingMessageSize);
		file.read(reinterpret_cast<char*>(&linkedRoomIndex), sizeof(linkedRoomIndex));
		links.emplace(messageBuffer, linkedRoomIndex);
	}
	size_t descriptionSize;
	file.read(reinterpret_cast<char*>(&descriptionSize), sizeof(descriptionSize));
	char* descriptionBuffer = new char[descriptionSize];
	file.read(descriptionBuffer, descriptionSize);
	description = descriptionBuffer;
}
