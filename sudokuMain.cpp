/*
	sudokuMain.cpp
	The driver program for a sudoku puzzle
	Author: Andrew Litteken
	Date: 2017-02-23
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Cell.h"
#include "SudBoard.h"
using namespace std;

int main(int argc, char *argv[]){
	
	if(argc==1){
		SudBoard boardToSolve; // create board using standard input
		boardToSolve.solve(); // solve it
		boardToSolve.showBoard(); // show the result
	}
	else{
		string filename;
		filename = argv[1]; // get the filename
		ifstream ifs; // open a file stream
		ifs.open(filename); // open file
		while(!ifs){ // if invalid
			cout<<"Invalid file, enter a different file please"<<endl;
		}
		char c = ifs.peek(); // check next character
		vector< vector<int> > puzzle; // create vector of vector for puzzle
		int n = -1; // index
		while (c != EOF){ // while not at end of file
			n++; // increase index
			vector<int> row; // create row vector
			puzzle.push_back(row);
			string nextList; // get string for list
			getline(ifs, nextList);
			for(int j=0;j<nextList.length();j=j+2){ // go through list
				char nextNum[1]; // create char
				nextNum[0] = nextList[j]; // set number to character in string
				puzzle[n].push_back(atoi(nextNum)); // convert to integer
			}
			c = ifs.peek(); // check next character
		}
		SudBoard boardToSolve(puzzle); // pass into board class
		boardToSolve.solve(); // solve it
		boardToSolve.showBoard(); // show the result
	}
}