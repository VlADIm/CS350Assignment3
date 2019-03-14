CC = g++
CC_FLAGS = -Wall -pedantic -g -Wextra
SRC = replacementpolicy.cpp
OBJ = $(SRC:.cpp = .o)
HDR = $(SRC:.cpp = .h)
EXC = prog3


all: data
	gnuplot -e "title='RandomData'" -e "input_filename='randData.csv'" plot_hit_rates.plt > RandomPlot.png
	gnuplot -e "title='8020Data'" -e "input_filename='leaning8020Data.csv'" plot_hit_rates.plt > Leaning8020Plot.png
	gnuplot -e "title='LoopingData'" -e "input_filename='loopingData.csv'" plot_hit_rates.plt > LoopingPlot.png

data: replacementpolicy.o
	$(CC) $(CC_FLAGS) -o $(EXC) $(OBJ)
	./$(EXC)

replacementpolicy.o: $(SRC) $(HDR)
	$(CC) $(CC_FLAGS) -c $(SRC)

generator.o: generator..cpp


clean:
	rm -f $(EXC) *.o *.png *.csv

checkmem:
	valgrind $(EXEC)
