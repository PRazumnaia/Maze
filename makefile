CC = g++
CFLAGS = -c -Wall -std=c++11
MSOUR = time.cpp score.cpp main.cpp
TSOUR = time.cpp score.cpp test.cpp
TBUILDDIR = build/test/
MBUILDDIR = build/src/
TDIR = test/
MDIR = src/
MOBJ = $(patsubst %.cpp, $(MBUILDDIR)%.o, $(MSOUR))
TOBJ = $(patsubst %.cpp, $(TBUILDDIR)%.o, $(TSOUR))
EXE = bin/maze
TEST = bin/test
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
HEADERS = -I src

all: $(EXE) $(TEST)

$(EXE): $(MOBJ)
	$(CC) $^ -o $@ $(SFML) $(HEADERS)

$(MBUILDDIR)%.o: $(MDIR)%.cpp
	$(CC) $(CFLAGS) -o $@ $^ 

$(TEST): $(TOBJ)
	$(CC) $^ -o $@ $(SFML) $(HEADERS)

$(TBUILDDIR)%.o: $(TDIR)%.cpp
	$(CC) $(CFLAGS) -o $@ $^

$(TBUILDDIR)%.o: $(MDIR)%.cpp
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean: 
	$(RM) $(TOBJ) $(MOBJ) $(EXE) $(TEST) 
