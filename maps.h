#ifndef MAPPING_H
#define MAPPING_H
#include <SFML/Graphics.hpp>

using namespace sf;

float offsetX = 0, offsetY = 0;

const int H = 12;
const int W = 40;


String TileMap[H] = {

    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    "W          W                      W    W",
    "W          W                           W",
    "WWWWWWW    W                           W",
    "W          WWWWWWWW    WWWW            W",
    "W          W           W  W            W",
    "W   WWWWWWWW           W  W            W",
    "W    MMMM              WWWW            W",
    "W                                      W",
    "W       M  WWWWWW                      W",
    "W          W                           W",
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWwWW",

};


#endif
