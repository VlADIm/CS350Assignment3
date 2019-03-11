CC = g++
CC_FLAGS = -Wall -pedantic -g -Wextra
SRC = replacementpolicy.cpp 
OBJ = $(SRC:.cpp = .o)
HDR = $(SRC:.cpp = .h)
EXC = prog3

all: replacementpolicy.o
	$(CC) $(CC_FLAGS) -o $(EXC) $(OBJ)

replacementpolicy.o: $(SRC) $(HDR)
	$(CC) $(CC_FLAGS) -c $(SRC)

generator.o: generator..cpp

clean:
	rm -f replacementpolicy.o $(EXC)
