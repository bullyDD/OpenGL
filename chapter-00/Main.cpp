/**
* @file: Main.cpp
* @author : Y.BINOUM
* @brief : Program that create a game using openGL/
* @license : BSD
* @version : 0.1
* @date : 08.2024
* 
*/

#include "Game.h"

int main()
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.Runloop();
	}

	game.Shutdown();

	return 0;
}