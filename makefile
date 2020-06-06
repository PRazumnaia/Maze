all:
	g++ -c main.cpp -I Maze
	g++ -c time.cpp
	g++ -c score.cpp
	g++ -c test.cpp -I Maze
	g++ main.o time.o score.o -o maze -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I Maze
	g++ test.o time.o score.o -o test -lsfml-graphics -lsfml-window -lsfml-system -I Maze
