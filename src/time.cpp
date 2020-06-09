#include "time.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int timer(int gameTime, int clock)
{
    gameTime -= clock;
    return gameTime;
}

