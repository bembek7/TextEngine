#include "SaveSystem.h"

void SaveSystem::SaveString(std::ofstream& file, const std::string& str) noexcept
{
	auto stringSize = str.size() + 1; // incrementing because of null termination sign
	file.write(reinterpret_cast<const char*>(&stringSize), sizeof(stringSize));
	file.write(str.c_str(), stringSize);
}

std::string SaveSystem::LoadString(std::ifstream& file) 
{
	size_t stringSize;
	file.read(reinterpret_cast<char*>(&stringSize), sizeof(stringSize));
	char* stringBuffer = new char[stringSize];
	file.read(stringBuffer, stringSize);
	return stringBuffer;
}