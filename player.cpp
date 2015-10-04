#include"player.h"
#include"gameBoard.h"
#include<iostream>
using namespace std;


player::player(int playerNumber){

	number = playerNumber;

    if(playerNumber == 1)
        brush = new QBrush(Qt::red);
    else
        brush = new QBrush(Qt::blue);

    blackPen = new QPen(Qt::black);
}

void player::setScene(QGraphicsScene *sceneInit){

    scene = sceneInit;

}

int player::move(int col, gameBoard* G){

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
    scene->addEllipse(col*43,140-y0*35,40,40,*blackPen,*brush);



	if(this->checkWon(col, y0, G))
		return 2;
	else
		return 1;

}

bool player::checkWon(int x0, int y0, gameBoard* G){

	bool res = false;
	int sizeX = G->getSizeX();
	int sizeY = G->getSizeY();
	
	//check vertical
	if(y0 > 2){

		int yCount = 1;
		while(y0 - yCount >= 0 && G->board[y0-yCount][x0] == this->number){
			yCount++;
		}
		
		if(yCount >= 4){
			res = true;
			return res;
		}
	}	

	//check horizontal
	int xCount = 0;
	for(int x = 0; x < sizeX; x++){
	
		if(G->board[y0][x] == this->number){
			xCount++;
			if(xCount >= 4){
				res = true; 
				break;
			}
		}
		else
			xCount = 0;

	}	

	return res;

	//check NE
	//TO BE IMPLEMENTED!

}






