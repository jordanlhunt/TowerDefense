/*
 * main.cpp
 *
 *  Created on: Aug 11, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "Game.h"
int main(int argc, char *argv[])
{
    Game game;
    bool isSuccessful = game.Initialize();
    if (isSuccessful)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
