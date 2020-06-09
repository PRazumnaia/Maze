#ifndef MAPPING_H
#define MAPPING_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

float offsetX = 0;
float offsetY = 0;

const int H = 39;
const int W = 44;

String TileMap[H] = {

    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B       B  B   B    B             B        B",
    "B          B   B  B B  BBB   BBBBBBBBBBB B B",
    "BBBBBBB    B      B B  B                 B B",
    "B       BBBBBBBBBBB    B   BBBBBBBB      B B",
    "B          B      BBBBBB   B      BBBBBBBB B",
    "B   BBBBBBBB               B  B            B",
    "B     B         B     BBBBBBBBBBBBBBBB     B",
    "B     B B   B   B   B      B            BBBB",
    "BBB   BBB  BBBBBB   B  B   B     BB   B    B",
    "B          B        B  B          B  BB    B",
    "BBBBBBBBBBBBBBBBBBBBBBBB   BBBBBBBBBBBBB  BB",
    "B       B    B    B                  B     B",
    "B   B B           B    BB    BB      B     B",
    "B     B      B    BB   BB    BB      B BBBBB",
    "B   B B    BBB                       B     B",
    "BBBBBBB  BBB      BB       B         B  BBBB",
    "B          BBBBBBBB    BBBBBBBBBBBBBBB     B",
    "B   B B    B      B        B      B  B  B  B",
    "B   BBBBBBBBBBB BBB    BBBBB            BBBB",
    "B     B B  B               BBBBBBBB     B  B",
    "B     B    B  B BBBBB      B           BB  B",
    "BBB   BBB  BBBBBB          B      B     B  B",
    "B          B        B B    B      B        B",
    "BBBBBB  BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB BB",
    "B    B  B        B  B                 B    B",
    "B  B B           B BB  BBBBBBBBBBBBB  B BBBB",
    "B  B B     B     B     B     B    B        B",
    "B  B     BBB   BBB B BBB     B   BBBBBBB BBB",
    "BBBBBBB    B       B       B          B    B",
    "B       B  BBBBBBBBBBBB    BBB  BBBBBBB BBBB",
    "B       B  B  B       BBB BB      B        B",
    "B   BBBBBBBB  B  B B  B    B  B            B",
    "B     B       B  BBBBBB  BBBBBBBBBBBBBBBBBBB",
    "B     B  BBB                  B   B   B    B",
    "BBB   B    BBBBBB     B    B  B BBB B   B  B",
    "B        B B    BBBBBBB BBBB    B BBBBBBB BB",
    "B     B  B B BB         B     B            B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

//Случайная генерация предметов
void RandomGeneration(int items) {
  int RandomX = 0;
  int RandomY = 0;
  srand(time(0));
  while (items > 0) {
    RandomX = 1 + rand() % (W - 1);
    RandomY = 1 + rand() % (H - 1);
    if (TileMap[RandomY][RandomX] == ' ') {
      int rarity = rand() % 15 + 1;
      if (rarity <= 7)
        TileMap[RandomY][RandomX] = 'Z';
      if ((rarity <= 13) && (rarity >= 8))
        TileMap[RandomY][RandomX] = 'X';
      if ((rarity == 14) || (rarity == 15))
        TileMap[RandomY][RandomX] = 'C';
      items--;
    }
  }
}

void MapInit() {
  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++) {
      if ((TileMap[i][j] == 'Z') || (TileMap[i][j] == 'X') ||
          (TileMap[i][j] == 'C'))
        TileMap[i][j] = ' ';
    }
}

#endif
