/*
	cell.cpp
	The implementation for a cell class in a sudoku puzzle
	Author: Andrew Litteken
	Date: 2017-02-23
*/

#include <vector>
#include <iostream>
#include "Cell.h"
#include "SudBoard.h"
using namespace std;

Cell::Cell(int v, int r, int c, int g){
	value = v;
	row = r;
	col = c;
	miniGrid = g;
	if (!value){
		for(int i=1;i<10;i++){
			poss.push_back(i);
		}
	}
	else poss.push_back(v);
}
Cell::~Cell() {}

int Cell::getValue(){
	return value; // return the value number 0-9
}
int Cell::getRow(){
	return row; // return the row number 0-8
}
int Cell::getCol(){
	return col; // return the column number 0-8
}
int Cell::getMiniGrid(){
	return miniGrid; // return the minigrid number 0-8
}
vector<int> Cell::getPoss(){
	return poss; // return the vector containing the remaining possibilities
}

void Cell::setValue(int v){
	value = v; // set the value number 0-9, 0 means no value
	poss.clear(); // empty possibility array
	poss.push_back(v); // add the new value as the only possibility
}
void Cell::setRow(int r){
	row = r; // set the row number 0-8

}
void Cell::setCol(int c){
	col = c; // set the column number 0-8
}
void Cell::setMiniGrid(int g){
	miniGrid = g; // set the minigrid number 0-8
}

int Cell::removePoss(int p){
	for(auto it = poss.begin();it<poss.end();it++){ // Search through remaining possibilities
		if (*it==p){ // if the possibilities remains
			poss.erase(it); // erase that possibility
			break; // exit the loop
		}
	}
	if(poss.size()==1){ // If the remaining length is equal to 1
		value=poss[0]; // set value of the cell to the last possibility
		return poss[0]; // return number to remove from other cells
	}
	return 0; // return 0, so as to not remove from other cells
}