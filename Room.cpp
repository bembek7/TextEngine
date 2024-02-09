#include "Room.h"
#include <iostream>
#include <fstream>
#include "SaveSystem.h"

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
	for (const auto& links : links)
	{
		SaveSystem::SaveString(file, links.first);
		file.write(reinterpret_cast<const char*>(&links.second), sizeof(links.second));
	}
	auto additionalDescriptionsSize = additionalDescriptions.size();
	file.write(reinterpret_cast<const char*>(&additionalDescriptionsSize), sizeof(additionalDescriptionsSize));
	for (const auto& additionalDescription : additionalDescriptions)
	{
		SaveSystem::SaveString(file, additionalDescription.first);
		SaveSystem::SaveString(file, additionalDescription.second);
	}
	SaveSystem::SaveString(file, description);
}

void Room::LoadRoom(std::ifstream& file)
{
	size_t linksNr;
	file.read(reinterpret_cast<char*>(&linksNr), sizeof(linksNr));
	for (size_t i = 0; i < linksNr; i++)
	{
		std::string linkingMessage = SaveSystem::LoadString(file);
		unsigned int linkedRoomIndex;
		file.read(reinterpret_cast<char*>(&linkedRoomIndex), sizeof(linkedRoomIndex));
		links.emplace(linkingMessage, linkedRoomIndex);
	}
	size_t additionalDescriptionsNr;
	file.read(reinterpret_cast<char*>(&additionalDescriptionsNr), sizeof(additionalDescriptionsNr));
	for (size_t i = 0; i < additionalDescriptionsNr; i++)
	{
		auto keyMessage = SaveSystem::LoadString(file);
		auto messageResponse = SaveSystem::LoadString(file);
		additionalDescriptions.emplace(keyMessage, messageResponse);
	}
	description = SaveSystem::LoadString(file);
}
