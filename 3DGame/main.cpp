// 3DGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main()
{
	Game *game = new Game();

	game->run();

    return 0;
}

