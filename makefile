CC = g++
CFLAGS = -g -Wall -pedantic -Wextra
SRC = replacementpolicy.cpp
OBJ = $(SRC:.cpp = .o)
HDR = $(SRC:.cpp = .h)
EXC = prog3

all: prog3.o
	$(CC) $(CFLAGS) -o $(EXC) $(OBJ)

prog3.o: $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(EXC)
