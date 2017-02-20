/*
	sudBoard.h
	The interface for a board class in a sudoku puzzle
	Author: Andrew Litteken
	Date: 2017-02-23
*/

#include <iostream>
#include <vector>
#include "Cell.h"
#include "SudBoard.h"
using namespace std;

SudBoard::SudBoard(){
	int minigrid=0; // set the initial minigrid to 0
	for(int i=0;i<9;i++){ // cycle through rows
		if(i/3==1) minigrid = 3; // if in the middle three rows, start minigrid count at 3
		else if(i/3==2)minigrid = 6; // if in last three, start at 6
		vector<Cell> row; // create vector of cells
		board.push_back(row); // add to vector of vectors
		for (int j=0;j<9;j++){ // go through columns
			int value;
			cin >> value; // read in value
			board[i].push_back(Cell(value,i,j,minigrid+j/3)); // place cell in
			// minigrid calculated by adding to base number plus, 0, 1 or 2
		}
	}
}

SudBoard::SudBoard(vector< vector<int> > puzzle){
	int minigrid=0; // set the initial minigrid to 0
	for(int i=0;i<9;i++){ // cycle through rows
		if(i/3==1) minigrid = 3; // if in the middle three rows, start minigrid count at 3
		else if(i/3==2) minigrid = 6; // if in last three, start at 6
		vector<Cell> row; // create vector of cells
		board.push_back(row); // add to vector of vectors
		for (int j=0;j<9;j++){ // go through columns
			int value;
			value = puzzle[i][j]; // read in value
			board[i].push_back(Cell(value,i,j,minigrid+j/3)); // place cell in
			// minigrid calculated by adding to base number plus, 0, 1 or 2
		}
	}
}

SudBoard::~SudBoard(){}

void SudBoard::solve(){
	initialCutting(); // start by eliminating initial possibilites
	bool solved = true; // set the fact that it has been solved to true
	for(int i=0;i<9;i++){ // look through ros and columns
		for (int j=0;j<9;j++){
			if(board[i][j].getValue()==0) solved = false; // if one is still empty set to false
		}
	}
	int count=0;
	while (!solved){ // if not solved
		singleton(); // perform singleton algorithm
		solved = true;
		for(int i=0;i<9;i++){ // look for blanks
			for (int j=0;j<9;j++){
				if(board[i][j].getValue()==0) solved = false; // if blank set to false
			}
		}
		count++;
		if (count%1000==0) showBoard();
	}
}

void SudBoard::initialCutting(){
	for(int i=0;i<9;i++){
		for (int j=0;j<9;j++){ // look through each cell
			if(board[i][j].getValue()==0){ // if empty
				int numberAdded = 0; // set for if a number has been added to board
				for(int k=0;k<9;k++){ // look through row
					if(board[i][k].getValue()!=0){ // if not equal to 0
						// remove value from the possible values
						numberAdded=board[i][j].removePoss(board[i][k].getValue());
					}
					if(numberAdded) { // if a number was added, remove that possibility from
						// corresponding locations
						removePoss(board[i][j], numberAdded);
						break; // exit for loop
					}
				}
				if(numberAdded) continue; // if number added, move to next blank
				for(int k=0;k<9;k++){ // look through columns
					if(board[k][j].getValue()!=0){ // perform same possibility removal as above
						numberAdded=board[i][j].removePoss(board[k][j].getValue());
					}
					if(numberAdded){
						removePoss(board[i][j], numberAdded);
						break;
					}
				}
				if(numberAdded) continue;
				for(int m=0;m<9;m++){ // look through each cell
					for (int n=0;n<9;n++){
						if (board[m][n].getValue()!=0){ // if value mot equal to 0
							// Check to see if in same minigrid
							if(board[m][n].getMiniGrid()==board[i][j].getMiniGrid()){
								// If it is, remove the possibility from the number
								numberAdded=board[i][j].removePoss(board[m][n].getValue());
							}
						}
						if(numberAdded){
							removePoss(board[i][j], numberAdded);
							break;
						}
					}
					if(numberAdded) break; // exit for loop
				}
				if(numberAdded) continue; // move to next blank
			}
		}
	}
}

void SudBoard::singleton(){ // Using the singleton algorithm to eliminate values
	vector<int> poss; //empty vector 
	for(int i=0;i<9;i++){ // cycle through each cell
		for (int j=0;j<9;j++){
			if(board[i][j].getValue()==0){ // if value is zero
				poss = board[i][j].getPoss(); // get possibilities
				for (int k=0;k<9;k++){ // look through the current row
					if(k==j) continue; // skip current location
					if(board[i][k].getValue()==0){ // if value is 0
						vector<int> newPoss = board[i][k].getPoss(); // get location's possibilites
						for(auto it = newPoss.begin();it<newPoss.end();it++){ // for each possibility of new location
							for(auto kt=poss.begin();kt<poss.end();kt++){ // compare to orignal
								if(*kt==*it){ // if they are the same
									poss.erase(kt); // remove it from the original
									break; // move to next location
								}
							}
						}
					}
				}
				if(poss.size()==1){ // if there is one possibility left
					board[i][j].setValue(poss[0]); // set value
					removePoss(board[i][j], poss[0]); // remove the rest of the possibilites from
					// correspoding locations
					break; // move to next blank
				}
			}	
		}
	}
	for(int i=0;i<9;i++){ // perform the same operations as above, except with columns this time
		for (int j=0;j<9;j++){
			if(board[j][i].getValue()==0){ // If value is 0
				poss = board[j][i].getPoss(); // get possible values
				for (int k=0;k<9;k++){ // look through current column
					if(k==j) continue; // if current location, skip
					if(board[k][i].getValue()==0){ // if value is 0
						vector<int> newPoss = board[k][i].getPoss(); // get new possibilites
						for(auto it = newPoss.begin();it<newPoss.end();it++){ // look through possibilities
							for(auto kt=poss.begin();kt<poss.end();kt++){ // compare to original
								if(*kt==*it){ // If there is a match
									poss.erase(kt); // remove it form the original
									break; // move to next possibility
								}
							}
						}
					}
				}
				if(poss.size()==1){ // if there is one possibility left
					board[j][i].setValue(poss[0]); // set it as the new value
					removePoss(board[j][i],poss[0]); // remove corresponding values
					break;
				}
			}
		}
	}
	for(int i=0;i<9;i++){ // Using blocks this time
		for (int j=0;j<9;j++){ // We look through each location
			if(board[i][j].getValue()==0){ // If value is 0
				poss = board[i][j].getPoss(); // get possibilites
				for (int k=0;k<9;k++){ // look through every value
					for (int n=0;n<9;n++){
						if(board[i][j].getMiniGrid()==board[k][n].getMiniGrid()){ // check for minigrid match
							if(k==i && n==j) continue; // Skip current blank
							if(board[k][n].getValue()==0){ // If value is 0
								vector<int> newPoss = board[k][n].getPoss(); // get possibilities of new spot
								for(auto it=newPoss.begin();it<newPoss.end();it++){ // look through new possibilites
									for(auto kt=poss.begin();kt<poss.end();kt++){ // look through original
										if(*kt==*it){ // if match
											poss.erase(kt); // remove possibility from original
											break;
										}
									}
								}
							}
						}	
					}
				}
				if(poss.size()==1){ // if one possibility left
					board[i][j].setValue(poss[0]); // set value
					removePoss(board[i][j], poss[0]); // remove possibilties as needed
					break;
				}
			}
		}
	}
}

void SudBoard::removePoss(Cell cell, int value){ // remove possibilites after an added number
	int row = cell.getRow(); // for simplicity, set row and column
	int col = cell.getCol();
	int numberAdded = 0; // set the number added to be 0
	for(int k=0;k<9;k++){ // cycle through the row
		if(board[row][k].getValue()==0){ // if is a blank
			numberAdded = 0;
			numberAdded=board[row][k].removePoss(value); // remove the possibility
			if(numberAdded) { // if a number was added
				removePoss(board[row][k], numberAdded); // start process again
			}
		}
	}
	for(int k=0;k<9;k++){ // cycle through column
		if(board[k][col].getValue()==0){ // if is a blank
			numberAdded = 0;
			numberAdded=board[k][col].removePoss(value); // remove possibility
			if(numberAdded){ // if a number was added
				removePoss(board[k][col], numberAdded); // start process again
			}
		}
	}
	for(int m=0;m<9;m++){ // cycle through each location
		for (int n=0;n<9;n++){
			if (board[m][n].getValue()==0){ // If is a blank
				numberAdded = 0;
				if(board[m][n].getMiniGrid()==cell.getMiniGrid()){ // If minigrid matches
					numberAdded=board[m][n].removePoss(value); // remove possibility
				}
				if(numberAdded){ // if number was added
					removePoss(board[m][n], numberAdded); // start process again
				}
			}
		}
	}
}

void SudBoard::showBoard(){ // print the board
	for(int i=0;i<9;i++){ // go thorugh each location
		for (int j=0;j<9;j++){
			cout << board[i][j].getValue()<<" "; // print out the value
		}
		cout<<endl;
	}
	cout<<endl;
}