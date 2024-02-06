#include "CommandsController.h"
#include <string>
#include <cctype>
#include <algorithm>

CommandsController::CommandsController(Game& Game) :
	game(Game)
{
}

int CommandsController::ProcessInput(const std::string& input) const noexcept
{
	if (input.size() > 0 && input[0] == '/')
	{
		return ProcessCommand(TranslateToCommand(input));
	}
	else
	{
		return ProcessMessage(input);
	}
}

int CommandsController::ProcessCommand(Command translatedCommand) const noexcept
{
	switch (translatedCommand)
	{
	case Quit:
		std::cout << "Quitting the game now." << std::endl;
		return -1;
		break;
	case Save:
		game.SaveGame();
		std::cout << "Saving the game ..." << std::endl;
		break;
	case Help:
		std::cout << "Possible commands are:" << std::endl;
		for (const auto& a : commandMap)
		{
			std::cout << "\t/" << a.first << std::endl;
		}
		break;
	case Unkown:
		std::cout << "Unkown Command. Type \"/help\" to get list of possible commands." << std::endl;
		break;
	default:
		break;
	}
	return 0;
}

int CommandsController::ProcessMessage(const std::string& message) const noexcept
{
	if (game.TryAdvanceRoom(message) == 0)
	{
		;
	}
	else
	{
		std::cout << "No response." << std::endl;
	}
	return 0;
}

Command CommandsController::TranslateToCommand(std::string command) const noexcept
{
	command.erase(command.begin());
	std::transform(command.begin(), command.end(), command.begin(),
		[](char c) { return std::tolower(c); });
	std::erase_if(command, [](char x)
	{
		return x == ' ' or x == '\n' or x == '\t';
	});
	auto it = commandMap.find(command);
	if (it != commandMap.end()) {
		return it->second;
	}
	else {
		return Unkown;
	}
}
