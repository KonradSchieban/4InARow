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
            heights[x] = -1;
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
		heights[x] = y;

	}

    //copy game board to calculate points for each move
    gameBoard* GCopy = gameBoard(G);

	//weight points:
	double* array = new double[sizeX];
	for(int x = 0; x < sizeX; x++){
	
		array[x] = weight(x,heights[x],sizeX,sizeY);
	
	}

	int bestCol = getMaxIndex(array, sizeX);
	int height = heights[bestCol];

	G->board[height][bestCol] = this->number;
    cout<<valueFunction(G,1)<<endl;
    cout<<valueFunction(G,2)<<endl;

    //paint stone on scene
    scene->addEllipse(bestCol*graphicsWidth/sizeX,graphicsHeight-(height+1)*graphicsHeight/sizeY,graphicsWidth/sizeX,graphicsHeight/sizeY,*blackPen,*brush);

	if(this->checkWon(bestCol, height, G))
		return 2;
	else
		return 1;

}


int computerPlayer::valueFunction(gameBoard* G, int playerNumber){

    /***************************************
     * count number of segments
     *
     *
     *
     ***************************************/

    //initialize return value
    int S = 0;

    int sizeX = G->getSizeX();
    int sizeY = G->getSizeY();

    //get all segments in horizontal direction
    for(int y = 0; y < sizeY; y++){
        for(int x = 0; x < sizeX-1; x++){

            //check for segment of size 4
            if(x < sizeX-3){
                if(G->board[y][x] == playerNumber && G->board[y][x+1] == playerNumber && G->board[y][x+2] == playerNumber && G->board[y][x+3] == playerNumber){
                    return 9999999;
                }
            }

            //check for segment of size 3
            if(x < sizeX-2){
                if(G->board[y][x] == playerNumber && G->board[y][x+1] == playerNumber && G->board[y][x+2] == playerNumber){
                    if(x > 0 && G->board[y][x-1] == 0 || x < sizeX-3 && G->board[y][x+3] == 0){
                        S += 10;
                        x +=2;
                    }
                }
            }

            //check for segment of size 2
            if(G->board[y][x] == playerNumber && G->board[y][x+1] == playerNumber){
                if((x > 1 && G->board[y][x-1] == 0 && G->board[y][x-2] == 0) ||
                   (x < sizeX-3 && G->board[y][x+2] == 0 && G->board[y][x+3] == 0) ||
                   (x > 0 && x < sizeX-2 && G->board[y][x-1] == 0 && G->board[y][x+2] == 0) ){
                    S++;
                    x += 1;
                }
            }

        }
    }


    //get all segments in vertical direction
    for(int x = 0; x < sizeX; x++){
        for(int y = 0; y < sizeY-1; y++){

            //check for segment of size 4
            if(y < sizeY-3){
                if(G->board[y][x] == playerNumber && G->board[y+1][x] == playerNumber && G->board[y+2][x] == playerNumber && G->board[y+3][x] == playerNumber){
                    return 9999999;
                }
            }

            //check for segment of size 3
            if(y < sizeY-3){
                if(G->board[y][x] == playerNumber && G->board[y+1][x] == playerNumber && G->board[y+2][x] == playerNumber){
                    if(G->board[y+3][x] == 0){
                        S += 10;
                        break;
                    }
                }
            }

            //check for segment of size 2
            if(y < sizeY-3){
                if(G->board[y][x] == playerNumber && G->board[y+1][x] == playerNumber && G->board[y+2][x] == 0 && G->board[y+3][x] == 0){
                        S++;
                        break;
                }
            }
        }
    }


    return S;


}


double computerPlayer::weight(int x, int y, int sizeX, int sizeY){

	return -sqrt( ((sizeX-1)/2 - x)*((sizeX-1)/2 - x) + ((sizeY-1)/2 - y)*((sizeY-1)/2 - y) );

}




