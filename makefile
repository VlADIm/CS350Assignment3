CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra
SRC = prog3.c
OBJ = $(SRC:.c = .o)
HDR = $(SRC:.c = .h)
EXC = $(SRC:.c = )

all: prog3.o
	$(CC) $(CFLAGS) -o $(EXC) $(OBJ)

prog3.o: $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(EXC)
