#include"player.h"
#include"computerPlayer.h"
#include<iostream>
#include"math.h"
#include<vector>
#include<algorithm>
#include"util/utilities.h"

using namespace std;

int computerPlayer::move(gameBoard* G, int col){ 


	int sizeX = G->getSizeX();
	int sizeY = G->getSizeY();	

	//initialize array of points for each column
    vector<int> heights = G->getAllHeights();

    //copy game board to calculate points for each move
    gameBoard* GCopy = new gameBoard(*G);

    //initialize vectors for
    // 1. all opponent function values: oppValues
    // 2. maximums of opponent function values for each move: maxOppValues

    vector<int> oppValues(sizeX);
    vector<int> maxOppValues(sizeX);

    vector<int> newHeights(sizeX);

    //MinMax algorithm
    int oppPlayerNumber = (this->number)%2 + 1;
    for(int x = 0; x<sizeX; x++){

        if(heights[x] != -1){

            GCopy->board[heights[x]][x] = this->number;
            newHeights = GCopy->getAllHeights();

            for(int y = 0; y < sizeY; y++){

                if(newHeights[y] != -1){

                    GCopy->board[newHeights[y]][y] = oppPlayerNumber;
                    oppValues[y] = valueFunction(GCopy,oppPlayerNumber) - valueFunction(GCopy,this->number);
                    GCopy->board[newHeights[y]][y] = 0;

                }

            }

            maxOppValues[x] = getMax(oppValues,sizeX);
            GCopy->board[heights[x]][x] = 0;

        }

    }

    delete GCopy;


    int bestCol = getMinIndex(maxOppValues, sizeX);
    int height = heights[bestCol];

	G->board[height][bestCol] = this->number;

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

    //Player number of opponent
    int oppPlayerNumber = playerNumber%2 + 1;

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
                    if((x > 0 && G->board[y][x-1] == 0) || (x < sizeX-3 && G->board[y][x+3] == 0)){
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


    int matchX = -1;
    int matchY = -1;
    //get lower segments in NW/SE direction
    for(int y = 3; y < sizeY; y++){

        int matches = 0;

        for(int x = 0; x <= y; x++){

            if(G->board[y-x][x] == playerNumber){
                if(matches == 0){
                    matchX = x;
                    matchY = y-x;
                }
                matches++;
            }else{
                if(matches >= 4){

                    return 9999999;

                }else if(matches == 3){

                    if((matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY+1][matchX-1] == 0) ||
                       (G->board[y-x][x] == 0) ){
                        S += 10;
                    }

                }else if(matches == 2){

                    if((matchX-2 >= 0 && matchY+2 < sizeY && G->board[matchY+2][matchX-2] != oppPlayerNumber && G->board[matchY+1][matchX-1] != oppPlayerNumber) ||
                       (matchX-1 >= 0 && matchY+1 < sizeY && G->board[matchY+1][matchX-1] != oppPlayerNumber && G->board[y-x][x] == 0) ||
                       (y-x-1 >= 0 &&  x+1 < sizeX && G->board[y-x-1][x+1] != oppPlayerNumber)  ){
                        S += 1;
                    }

                }

                matches = 0;
            }

            //Diagonal reached border
            if(x==y && matches >= 4){

                return 9999999;

            }else if(x==y && matches == 3){

                if((matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY+1][matchX-1] == 0) ||
                   (G->board[y-x][x] == 0) ){
                    S += 10;
                }

            }else if(x==y && matches == 2){

                if((matchX-2 >= 0 && matchY+2 < sizeY && G->board[matchY+2][matchX-2] != oppPlayerNumber && G->board[matchY+1][matchX-1] != oppPlayerNumber) ||
                   (matchX-1 >= 0 && matchY+1 < sizeY && G->board[matchY+1][matchX-1] != oppPlayerNumber && G->board[y-x][x] == 0) ||
                   (y-x-1 >= 0 &&  x+1 < sizeX && G->board[y-x-1][x+1] != oppPlayerNumber)  ){
                    S += 1;
                }

            }

        }

        matches = 0;

    }

    //get upper segments in NW/SE direction
    for(int y = 1; y < sizeY; y++){

        int matches = 0;
        for(int x = sizeX-1; x >= y; x--){

            if(G->board[sizeY-x+y-1][x] == playerNumber){

                if(matches == 0){
                    matchX = x;
                    matchY = sizeY-x+y-1;
                }
                matches++;
            }else{
                if(matches >= 4){

                    return 9999999;

                }else if(matches == 3){

                    if((matchX+1 < sizeX && G->board[matchY-1][matchX+1] == 0) ||
                       (G->board[sizeY-x+y-1][x] == 0) ){
                        S += 10;
                    }

                }else if(matches == 2){

                    if((matchX+2 < sizeX && matchY-2 >= 0 && G->board[matchY-2][matchX+2] != oppPlayerNumber && G->board[matchY-1][matchX+1] != oppPlayerNumber) ||
                       (matchX+1 < sizeX && G->board[matchY-1][matchX+1] != oppPlayerNumber && G->board[sizeY-x+y-1][x] == 0) ||
                       (sizeY-x+y < sizeY &&  x+1 < sizeX && G->board[sizeY-x+1][x+1] != oppPlayerNumber)  ){
                        S += 1;
                    }

                }

                matches = 0;
            }

            //Diagonal reached border
            if(x==y && matches >= 4){

                return 9999999;

            }else if(x==y && matches == 3){

                if((matchX+1 < sizeX && G->board[matchY-1][matchX+1] == 0) ||
                   (G->board[sizeY-x+y-1][x] == 0) ){
                    S += 10;
                }

            }else if(x==y && matches == 2){

                if((matchX+2 < sizeX && matchY-2 >= 0 && G->board[matchY-2][matchX+2] != oppPlayerNumber && G->board[matchY-1][matchX+1] != oppPlayerNumber) ||
                   (matchX+1 < sizeX && G->board[matchY-1][matchX+1] != oppPlayerNumber && G->board[sizeY-x+y-1][x] == 0) ||
                   (sizeY-x+y < sizeY &&  x+1 < sizeX && G->board[sizeY-x+1][x+1] != oppPlayerNumber)  ){
                    S += 1;
                }

            }
        }

    }



    //get upper segments in NE/SW direction
    for(int y = 0; y < sizeY; y++){

        int matches = 0;

        for(int x = 0; x < sizeY-y; x++){

            if(G->board[x+y][x] == playerNumber){
                if(matches == 0){
                    matchX = x;
                    matchY = x+y;
                }
                matches++;
            }else{
                if(matches >= 4){

                    return 9999999;

                }else if(matches == 3){

                    if((matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] == 0) ||
                       (G->board[y+x][x] == 0) ){
                        S += 10;
                    }

                }else if(matches == 2){

                    if((matchX-2 >= 0 && matchY-2 >= 0 && G->board[matchY-2][matchX-2] != oppPlayerNumber && G->board[matchY-1][matchX-1] != oppPlayerNumber) ||
                       (matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] != oppPlayerNumber && G->board[x+y][x] == 0) ||
                       (x+y+1 < sizeY &&  x+1 < sizeX && G->board[x+y+1][x+1] != oppPlayerNumber)  ){
                        S += 1;
                    }

                }

                matches = 0;
            }

            //Diagonal reached border
            if(x+y==sizeY-1 && matches >= 4){

                return 9999999;

            }else if(x+y==sizeY-1 && matches == 3){

                if((matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] == 0) ||
                   (G->board[y+x][x] == 0) ){
                    S += 10;
                }

            }else if(x+y==sizeY-1 && matches == 2){

                if((matchX-2 >= 0 && matchY-2 >= 0 && G->board[matchY-2][matchX-2] != oppPlayerNumber && G->board[matchY-1][matchX-1] != oppPlayerNumber) ||
                   (matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] != oppPlayerNumber && G->board[x+y][x] == 0) ||
                   (x+y+1 < sizeY &&  x+1 < sizeX && G->board[x+y+1][x+1] != oppPlayerNumber)  ){
                    S += 1;
                }

            }

        }

        matches = 0;

    }


    //get lower segments in NE/SW direction
    for(int x = 1; x < sizeX; x++){

        int matches = 0;

        for(int y = 0; y < sizeY-x; y++){

            if(G->board[y][x+y] == playerNumber){
                if(matches == 0){
                    matchX = x+y;
                    matchY = y;
                }
                matches++;
            }else{
                if(matches >= 4){

                    return 9999999;

                }else if(matches == 3){

                    if((matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] == 0) ||
                       (G->board[y][x+y] == 0) ){
                        S += 10;
                    }

                }else if(matches == 2){

                    if((matchX-2 >= 0 && matchY-2 >= 0 && G->board[matchY-2][matchX-2] != oppPlayerNumber && G->board[matchY-1][matchX-1] != oppPlayerNumber) ||
                       (matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] != oppPlayerNumber && G->board[y][x+y] == 0) ||
                       (y+1 < sizeY &&  x+y+1 < sizeX && G->board[y+1][x+y+1] != oppPlayerNumber)  ){
                        S += 1;
                    }

                }

                matches = 0;

            }

            //Diagonal reached border
            if(x+y == sizeY-1 && matches >= 4){

                return 9999999;

            }else if(x+y == sizeY-1 && matches == 3){

                if((matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] == 0) ||
                   (G->board[y][x+y] == 0) ){
                    S += 10;
                }

            }else if(x+y == sizeY-1 && matches == 2){

                if((matchX-2 >= 0 && matchY-2 >= 0 && G->board[matchY-2][matchX-2] != oppPlayerNumber && G->board[matchY-1][matchX-1] != oppPlayerNumber) ||
                   (matchX-1 >= 0 && matchY-1 >= 0 && G->board[matchY-1][matchX-1] != oppPlayerNumber && G->board[y][x+y] == 0) ||
                   (y+1 < sizeY &&  x+y+1 < sizeX && G->board[y+1][x+y+1] != oppPlayerNumber)  ){
                    S += 1;
                }

            }
        }
        matches = 0;
    }

    return S;

}
