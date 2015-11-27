#include"player.h"
#include"computerPlayer.h"
#include<iostream>
#include"math.h"
#include"util/utilities.h"

using namespace std;

int computerPlayer::move(gameBoard* G, int col){ 


	int sizeX = G->getSizeX();
	int sizeY = G->getSizeY();	
	
	//initialize array of points for each column
	int* points = new int[sizeX];
	int* heights = new int[sizeX];

	//iterate over all columns
	for(int x = 0; x < sizeX; x++){
		
		//is column allready full?
		if(G->board[x][sizeY-1] != 0){
			points[x] = -1;
		}

		
		//get y value of possible move:
		int y = -1;
		for(int y0 = sizeY-1; y0 >= 0; y0--){
		
			if(y0 == 0){
				y = 0;
				break;
			}

			if(G->board[y0-1][x] != 0){
				y = y0;
				break;
			}
		}

		//move in this column has coordinate (x,y)
		points[x] = y;
		heights[x] = y;

	}

	//weight points:
	double* array = new double[sizeX];
	for(int x = 0; x < sizeX; x++){
	
		array[x] = weight(x,heights[x],sizeX,sizeY);
	
	}

	int bestCol = getMaxIndex(array, sizeX);
	int height = heights[bestCol];

	G->board[height][bestCol] = this->number;

    //paint stone on scene
    scene->addEllipse(bestCol*43,140-height*35,40,40,*blackPen,*brush);

	if(this->checkWon(bestCol, height, G))
		return 2;
	else
		return 1;

}



double computerPlayer::weight(int x, int y, int sizeX, int sizeY){

	return -sqrt( ((sizeX-1)/2 - x)*((sizeX-1)/2 - x) + ((sizeY-1)/2 - y)*((sizeY-1)/2 - y) );

}




