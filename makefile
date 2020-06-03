all:
	g++ -c main.cpp
	g++ -c time.cpp
	g++ -c test_time.cpp
	g++ main.o time.o -o maze -lsfml-graphics -lsfml-window -lsfml-system
	gcc maintest.o timetest.o time.o -o timetest
	g++ test_time.o time.o -o test_move
