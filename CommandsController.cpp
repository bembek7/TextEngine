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

int CommandsController::ProcessCommand(CommandID translatedCommand) const noexcept
{
	switch (translatedCommand)
	{
	case Quit:
		std::cout << "Quitting the game now." << std::endl;
		return -1;
		break;
	case Save:
		game.SaveGame();
		std::cout << "Saved the game" << std::endl;
		break;
	case Load:
		std::cout << "Loading the game ..." << std::endl;
		try
		{
			game.LoadLast();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			break;
		}
		std::cout << "Successfully loaded the game." << std::endl;
		game.Start();
		break;
	case New:
		std::cout << "Starting new game ..." << std::endl;
		try
		{
			game.LoadNew();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			break;
		}
		std::cout << "Successfully started the game." << std::endl;
		game.Start();
		break;
	case Inventory:
		game.PrintInventory();
		break;
	case Help:
		std::cout << "Possible commands are:" << std::endl;
		for (const auto& com : commands)
		{
			std::cout << "\t/" << com.name << " - " << com.description << std::endl;
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
	if (game.IsStarted())
	{
		if (!game.TryAdvanceRoom(message))
		{
			if (!game.TryAction(message))
			{
				std::cout << "No response." << std::endl;
			}
		}
	}
	else
	{
		std::cout << "There is no game loaded. Use \"/load\" command to load last saved game or \"/new\" to start a new game." << std::endl;
	}
	return 0;
}

CommandID CommandsController::TranslateToCommand(std::string input) const noexcept
{
	input.erase(input.begin());
	std::transform(input.begin(), input.end(), input.begin(),
		[](char c) { return std::tolower(c); });
	std::erase_if(input, [](char x)
	{
		return x == ' ' or x == '\n' or x == '\t';
	});
	for (const auto& com : commands)
	{
		if (input == com.name)
		{
			return com.ID;
		}
	}
	return Unkown;
}
