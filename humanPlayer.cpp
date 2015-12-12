#include"player.h"
#include"humanPlayer.h"
#include<iostream>
using namespace std;

bool allColumnsFull(gameBoard* G);

int humanPlayer::move(gameBoard* G, int col){

	int sizeX = G->getSizeX();
	int sizeY = G->getSizeY();	

	//column out of range
	if(col>=sizeX || col < 0)
		return 0;
	
	//column is full
	if(G->board[sizeY-1][col] != 0)
		return 0;

	int y0 = -1;
	for(int y = sizeY-1; y >= 0; y--){
		
		if(y == 0){
			G->board[0][col] = this->number;
			y0 = 0;
			break;
		}

		if(G->board[y-1][col] != 0){
			G->board[y][col] = this->number;
			y0 = y;
			break;
		}
	}
		

    //paint stone on scene
    scene->addEllipse(col*graphicsWidth/sizeX,graphicsHeight-(y0+1)*graphicsHeight/sizeY,graphicsWidth/sizeX,graphicsHeight/sizeY,*blackPen,*brush);

	if(this->checkWon(col, y0, G))
		return 2;
    else{
        if(G->allColumnsFull())
            return 3;
        else
            return 1;
    }

}
