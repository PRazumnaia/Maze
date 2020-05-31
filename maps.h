#ifndef MAPPING_H
#define MAPPING_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

float offsetX = 0, offsetY = 0;

const int H = 12;
const int W = 40;


String TileMap[H] = {

    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B          B                      B    B",
    "B          B                           B",
    "BBBBBBB    B                           B",
    "B          BBBBBBBB    BBBB            B",
    "B          B           B  B            B",
    "B   BBBBBBBB           B  B            B",
    "B                      BBBB            B",
    "B                                      B",
    "B          BBBBBB                      B",
    "B          B                           B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

void RandomGeneration()
{
	int RandomX = 0;
	int RandomY = 0;
	srand(time(0)); 
	int items = 5;
	while (items > 0)
	{
		RandomX = 1 + rand() % (W-1);
		RandomY = 1 + rand() % (H-1);
		if (TileMap[RandomY][RandomX] == ' ') {
			int rarity = rand() % 15 +1;
			if (rarity <= 7)
				TileMap[RandomY][RandomX] = 'Z';
			if ((rarity <= 13) && (rarity >=8))
				TileMap[RandomY][RandomX] = 'X';
			if ((rarity == 14) || (rarity == 15))
				TileMap[RandomY][RandomX] = 'C';
			items--;
		}
	}
}


#endif
