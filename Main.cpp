// TextEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Room.h"
#include <iostream>
#include "CommandsController.h"
#include "openai.hpp"
#include "Game.h"

int main()
{
    /*
    openai::start("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");

    auto chat = openai::chat().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[{"role":"user", "content":"blah"}],
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json);
    std::cout << "Response is:\n" << chat.dump(2) << '\n';
	*/
    Game game;

    CommandsController cc(game);
    Room room("You've entered the left room.");
    Room room2("You've entered the right room.");
    room.AddRoomLink("go right", &room2);
    room2.AddRoomLink("go left", &room);
    game.AddRoom(room);
    game.AddRoom(room2);

    game.Start();
	while (true)
	{
		std::string com;
        std::getline(std::cin, com);
		if (cc.ProcessInput(com) != 0) break;
	}

	return 0;
}
