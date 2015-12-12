#include"gameBoard.h"
#include<iostream>

using namespace std;

//Copy Constructor
gameBoard::gameBoard(const gameBoard &G){

    sizeX = G.sizeX;
    sizeY = G.sizeY;

    board = new int*[sizeY];

    for(int y = 0; y < sizeY; y++){

        int* boardRow = new int[sizeX];

        for(int x = 0; x < sizeX; x++){
            boardRow[x] = G.board[y][x];
        }

        board[y] = boardRow;
    }

}

//Print game board with ASCII charcters on console
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

gameBoard::~gameBoard(){

    for(int y = 0; y < sizeY; y++){

        delete board[y];
    }

    delete[] board;

}

void gameBoard::clear(){

    for(int y = 0; y < sizeY; y++){
        for(int x = 0; x < sizeX; x++){
            board[y][x] = 0;
        }
    }

}

vector<int> gameBoard::getAllHeights(){

    //initialize array of points for each column
    vector<int> heights(sizeX);

    //iterate over all columns
    for(int x = 0; x < sizeX; x++){

        //is column allready full?
        if(board[x][sizeY-1] != 0){
            heights[x] = -1;
        }

        //get y value of possible move:
        int y = -1;
        for(int y0 = sizeY-1; y0 >= 0; y0--){

            if(y0 == 0){
                y = 0;
                break;
            }

            if(board[y0-1][x] != 0){
                y = y0;
                break;
            }
        }

        //move in this column has coordinate (x,y)
        heights[x] = y;

    }

    return heights;

}


bool gameBoard::allColumnsFull(){

    //initialize return value
    bool allFull = true;

    for(int i = 0; i<sizeX; i++){
        if(board[sizeY-1][i] == 0)
            allFull = false;
    }

    return allFull;

}
