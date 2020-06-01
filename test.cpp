#include "maps.h"
#include <iostream>

int RandomGenerationTest() {
  int count = 0;
  RandomGeneration(11);
  for (int i = 1; i < H; i++) {
    for (int j = 1; j < W; j++) {
      if ((TileMap[i][j] == 'Z') || (TileMap[i][j] == 'X') ||
          (TileMap[i][j] == 'C'))
        count++;
    }
  }
  if (count == 11)
    return 0;
  else
    return -1;
}

int main() {
  int a = RandomGenerationTest();
  if (a == 0)
    std::cout << "Item generation test ended [CORRECT]\n";
  else
    std::cout << "Item generation test ended [FAIL]\n";
  return 0;
}
