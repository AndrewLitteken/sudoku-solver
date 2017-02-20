/*
	cell.h
	The interface for a cell class in a sudoku puzzle
	Author: Andrew Litteken
	Date: 2017-02-23
*/

#include <vector>
using namespace std;

#ifndef CELL_H
#define CELL_H

class Cell {
	public:
		Cell(int, int, int, int);
		~Cell();

		int getValue();
		int getRow();
		int getCol();
		int getMiniGrid();
		vector<int> getPoss();

		void setValue(int);
		void setRow(int);
		void setCol(int);
		void setMiniGrid(int);
		
		int removePoss(int);

	private:
		int value;
		int row;
		int col;
		int miniGrid;
		vector<int> poss;
};

#endif