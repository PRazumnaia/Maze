all:
	g++ -c main.cpp -I Maze
	g++ -c time.cpp
	g++ -c test_time.cpp
	g++ main.o time.o -o maze -lsfml-graphics -lsfml-window -lsfml-system -I Maze
	g++ test_time.o time.o -o test_move
