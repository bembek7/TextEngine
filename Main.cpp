// TextEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Room.h"
#include <iostream>
#include "CommandsController.h"
#include "openai.hpp"
#include "Game.h"

int main()
{
    Game game;
    CommandsController cc(game);
    
    /*Room room("You've entered the left room.");
    Room room2("You've entered the right room.");
    room.AddRoomLink("go right", 1);
    room.AddAdditionalDescription("I inspect", "You inspected.");
    room2.AddRoomLink("go left", 0);
    game.AddRoom(room);
    game.AddRoom(room2);
    game.FindItem(Item("Key", "an old, rusty key"));
    game.FindItem(Item("Journal", "journal of J. Smith"));
    game.SaveGame();*/
    std::cout << "Program started. Ready for input." << std::endl;
	while (true)
	{
		std::string com;
        std::getline(std::cin, com);
		if (cc.ProcessInput(com) != 0) break;
	}
	return 0;
}
