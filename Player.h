#pragma once
#include <vector>
#include <string>
#include "Item.h"

class Player
{
public:
	void PrintInventory() const noexcept;
	void SavePlayer(std::ofstream& file) const noexcept;
	void LoadPlayer(std::ifstream& file);
	void AddItem(Item&& item) noexcept;
private:
	std::vector<std::unique_ptr<Item>>inventory;
};

