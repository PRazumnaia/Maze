all:
	g++ -c main.cpp -I Maze
	g++ -c time.cpp
	g++ -c test_time.cpp
	g++ -c test.cpp -I Maze
	g++ main.o time.o -o maze -lsfml-graphics -lsfml-window -lsfml-system -I Maze
	g++ test.o time.o -o test -lsfml-graphics -lsfml-window -lsfml-system -I Maze
