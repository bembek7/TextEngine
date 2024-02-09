#pragma once
#include <iostream>
#include <unordered_map>
#include "Game.h"

enum CommandID
{
	Quit,
	Save,
	Load,
	New,
	Inventory,
	Help,
	Unkown
};

struct Command
{
	CommandID ID;
	std::string name;
	std::string description;
};

class CommandsController
{
public:
	CommandsController(Game& game);
	int ProcessInput(const std::string& input) const noexcept;
private:
	int ProcessCommand(CommandID translatedCommand) const noexcept;
	int ProcessMessage(const std::string& message) const noexcept;
	CommandID TranslateToCommand(std::string input) const noexcept;
public:

private:
	Game& game;
	std::vector<Command>commands =
	{
		{Quit, "quit", "quits the game without saving"},
		{Save, "save", "saves the current state of the game"},
		{Load, "load", "loads the last saved game"},
		{New, "new", "starts the new game"},
		{Inventory, "inventory", "shows what you have found so far"},
		{Help, "help", "lists all possible commands"}
	};
};

