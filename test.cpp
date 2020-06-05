#include "score.h"
#include "maps.h"
#include "time.h"
#include <iostream>

int Correct = 0;
int Fail = 0;

void IntTest(int result, int expected) {
  if (result == expected) {
    Correct++;
    std::cout << "test ended [CORRECT]\n";
  } else {
    Fail++;
    std::cout << "test ended [FAIL]\n";
  }
}


void Score(){
    int result = score(10);
    int expected = 10;
    std::cout << "Score ";
    IntTest(result, expected);
}

void Timer(){

    int result = timer(50, 2);
    int expected = 48;
    std::cout << "Timer ";
    IntTest(result, expected);
}

void RandomGenerationTest() {
  int count = 0;
  RandomGeneration(11);
  for (int i = 1; i < H; i++) {
    for (int j = 1; j < W; j++) {
      if ((TileMap[i][j] == 'Z') || (TileMap[i][j] == 'X') ||
          (TileMap[i][j] == 'C'))
        count++;
    }
  }
  std::cout << "Random generation ";
  IntTest(count, 11);
}

void MapInitTest() {
  RandomGeneration(10);
  MapInit();
  int count = 0;
  for (int i = 1; i < H; i++) {
    for (int j = 1; j < W; j++) {
      if ((TileMap[i][j] == 'Z') || (TileMap[i][j] == 'X') ||
          (TileMap[i][j] == 'C'))
        count++;
    }
  }
  std::cout << "Map initialization ";
  IntTest(count, 0);
}

int main() {
  Score();
  Timer();
  RandomGenerationTest();
  MapInitTest();
  std::cout << "Results: \n CORRECT: " << Correct << "\n FAIL: " << Fail << "\n";
  return 0;
}
