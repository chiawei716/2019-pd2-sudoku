all: generate transform solve clean

generate: generate.o sudoku.o
	g++ -o generate generate.o sudoku.o

generate.o: generate.cpp sudoku.h
	g++ -c generate.cpp

transform: transform.o sudoku.o
	g++ -o transform transform.o sudoku.o

transform.o: transform.cpp sudoku.h
	g++ -c transform.cpp

solve: solve.o sudoku.o
	g++ -o solve solve.o sudoku.o

solve.o: solve.cpp sudoku.h
	g++ -c solve.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

clean:
	rm *.o
