CC = g++
CFLAGS = -c -Wall
MSOUR = time.cpp score.cpp main.cpp
TSOUR = time.cpp score.cpp test.cpp
MOBJ = $(MSOUR:.cpp=.o)
TOBJ = $(TSOUR:.cpp=.o)
EXE = maze
TEST = test
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
HEADERS = -I Maze

all: $(EXE) $(TEST)

$(EXE): $(MOBJ)
	$(CC) $(MOBJ) -o $(EXE) $(SFML) $(HEADERS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(HEADERS)



$(TEST): $(TOBJ)
	$(CC) $(TOBJ) -o $(TEST) $(SFML) $(HEADERS)
