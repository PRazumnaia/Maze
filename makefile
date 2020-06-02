all:
	    g++ -c main.cpp
	    g++ main.o -o maze -lsfml-graphics -lsfml-window -lsfml-system
