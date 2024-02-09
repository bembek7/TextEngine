#pragma once
#include <fstream>

namespace SaveSystem
{
	void SaveString(std::ofstream& file, const std::string& str) noexcept;
	std::string LoadString(std::ifstream& file);
}
