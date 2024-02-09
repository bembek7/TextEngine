#include "Item.h"
#include "SaveSystem.h"

Item::Item(const std::string& Name, const std::string& Description) :
	name(Name),
	description(Description)
{}

void Item::SaveItem(std::ofstream& file) const noexcept
{
	SaveSystem::SaveString(file, name);
	SaveSystem::SaveString(file, description);
}

void Item::LoadItem(std::ifstream& file)
{
	name = SaveSystem::LoadString(file);
	description = SaveSystem::LoadString(file);
}

std::string Item::GetName() const noexcept
{
	return name;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << item.name << " - " << item.description;
	return os;
}