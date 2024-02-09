#pragma once
#include <string>
#include <ostream>

class Item
{
public:
	Item() = default;
	Item(const std::string& Name, const std::string& Description);
	void SaveItem(std::ofstream& file) const noexcept;
	void LoadItem(std::ifstream& file);
	std::string GetName() const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Item& item);
private:
	std::string name;
	std::string description;
};
