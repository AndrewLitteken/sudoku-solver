/*
	sudBoard.h
	The interface for a board class in a sudoku puzzle
	Author: Andrew Litteken
	Date: 2017-02-23
*/

#include <vector>
#include "Cell.h"
using namespace std;

#ifndef SUDBOARD_H
#define SUDBOARD_H

class SudBoard {
	public:
		SudBoard();
		SudBoard(vector <vector<int> >);
		~SudBoard();
		void solve();
		void initialCutting();
		void singleton();
		void removePoss(Cell, int);
		void showBoard();
	private:
		vector< vector<Cell> > board;
};

#endif