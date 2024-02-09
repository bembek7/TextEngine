#include "Player.h"
#include <iostream>
#include <fstream>

void Player::PrintInventory() const noexcept
{
	std::cout << "Inventory:" << std::endl;
	for (const auto& item : inventory)
	{
		std::cout << *item << std::endl;
	}
}

void Player::SavePlayer(std::ofstream& file) const noexcept
{
	auto inventorySize = inventory.size();
	file.write(reinterpret_cast<const char*>(&inventorySize), sizeof(inventorySize));
	for (const auto& item : inventory)
	{
		item->SaveItem(file);
	}
}

void Player::LoadPlayer(std::ifstream& file)
{
	size_t itemsNr;
	file.read(reinterpret_cast<char*>(&itemsNr), sizeof(itemsNr));
	for (size_t i = 0; i < itemsNr; i++)
	{
		Item item;
		item.LoadItem(file);
		inventory.push_back(std::make_unique<Item>(std::move(item)));
	}
}

void Player::AddItem(Item&& item) noexcept
{
	inventory.push_back(std::make_unique<Item>(item));
}
