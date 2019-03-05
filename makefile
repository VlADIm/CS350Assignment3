CC = g++
CFLAGS = -g -Wall -pedantic -Wextra
SRC = replacementpolicy.cpp
OBJ = $(SRC:.cpp = .o)
HDR = $(SRC:.cpp = .h)
EXC = prog3

all: replacementpolicy.o
	$(CC) $(CFLAGS) -o $(EXC) $(OBJ)

replacementpolicy.o: $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f replacementpolicy.o $(EXC)
