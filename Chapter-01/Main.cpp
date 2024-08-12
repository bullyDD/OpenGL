/**
* @file    : Main.cpp
* @author  : Y.BINYOUM
* @brief   : Program that display a cube to the screen.
* @license : BSD
* @version : 0.1
* @date    : 08.2024
*
*/

#include "Game.h"

int main()
{
	Game game;

	int success = game.Initialize();
	if (success)
	{
		game.Runloop();
	}

	game.Shutdown();

	return 0;
}