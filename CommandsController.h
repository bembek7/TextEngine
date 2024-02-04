#pragma once
#include <iostream>
#include <unordered_map>
#include "Game.h"

enum Command
{
	Quit,
	Save,
	Help,
	Unkown
};

class CommandsController
{
public:
	CommandsController(Game& game);
	int ProcessInput(const std::string& input) const noexcept;
private:
	int ProcessCommand(Command translatedCommand) const noexcept;
	int ProcessMessage(const std::string& message) const noexcept;
	Command TranslateToCommand(std::string command) const noexcept;
public:

private:
	Game& game;
	std::unordered_map<std::string, Command> commandMap = {
		{"quit", Quit},
		{"save", Save},
		//{"load", Load},
		//{"new", New},
		{"help", Help}
	};
};

