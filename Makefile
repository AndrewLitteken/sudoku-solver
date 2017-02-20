solve: sudokuMain.o SudBoard.o Cell.o
	g++ -std=c++11 sudokuMain.o SudBoard.o Cell.o -o solve

sudokuMain.o: sudokuMain.cpp
	g++ -c -std=c++11 sudokuMain.cpp -o sudokuMain.o

SudBoard.o: SudBoard.cpp SudBoard.h
	g++ -c -std=c++11 SudBoard.cpp -o SudBoard.o

Cell.o: Cell.cpp Cell.h
	g++ -c -std=c++11 Cell.cpp -o Cell.o

clean:
	rm  *.o
