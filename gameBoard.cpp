#include"gameBoard.h"
#include<iostream>

using namespace std;

void gameBoard::print(){

	
	int sizeX = this->getSizeX();
	int sizeY = this->getSizeY();

	for(int y = sizeY-1; y >= 0; y--){
		cout<<"||";
		for(int x = 0; x < sizeX; x++){

			if(this->board[y][x] == 0)
				cout<<" "<<"|";
			else
				cout<<this->board[y][x]<<"|";

		}
		cout<<"|"<<endl;
	}

}

gameBoard::gameBoard(){

	sizeX = 7;
	sizeY = 7;

	board = new int*[sizeY]; 	

	for(int y = 0; y < sizeY; y++){

		int* boardRow = new int[sizeX];
	
		for(int x = 0; x < sizeX; x++){
			boardRow[x] = 0;
		}
	
		board[y] = boardRow;
	}

}
