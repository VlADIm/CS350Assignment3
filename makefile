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

graphs: randData.csv leaning8020Data.csv loopingData.csv
	gnuplot -e "title='RandomData'" -e "input_filename='randData.csv'" plot_hit_rates.plt > randomPlot.png
	gnuplot -e "title='8020Data'" -e "input_filename='leaning8020Data.csv'" plot_hit_rates.plt > 8020Plot.png
	gnuplot -e "title='LoopingData'" -e "input_filename='loopingData.csv'" plot_hit_rates.plt > LoopingPlot.png

clean:
	rm -f replacementpolicy.o $(EXC)

checkmem:
	valgrind $(EXEC)
