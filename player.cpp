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

void player::setScene(QGraphicsScene *sceneInit, int grWidth, int grHeight){

    scene = sceneInit;

    graphicsWidth = grWidth;
    graphicsHeight = grHeight;

}

bool player::checkWon(int x0, int y0, gameBoard* G){
/*
    checks if the token at position x0,y0 wins the game
    Return value:
        true if player won
        false otherwise
*/

    int sizeX = G->getSizeX();
    int sizeY = G->getSizeY();

    //check vertical
    if(y0 > 2){

        int yCount = 1;
        while(y0 - yCount >= 0 && G->board[y0-yCount][x0] == this->number){
            yCount++;
        }

        if(yCount >= 4){
            return true;
        }
    }

    //check horizontal
    int xCount = 0;
    for(int x = 0; x < sizeX; x++){

        if(G->board[y0][x] == this->number){
            xCount++;
            if(xCount >= 4){
                return true;
            }
        }
        else
            xCount = 0;

    }

    /************************************/
    //CHECK NW/SE DIAGONAL
    //check NW
    int inARow = 0;
    int y = y0;
    int x = x0;
    while(x >=0 && y < sizeY){

        if(G->board[y][x] == this-> number){
            inARow++;
        }

        x--;
        y++;

    }

    //check SE
    y = y0-1;
    x = x0+1;
    while(x < sizeX && y >= 0){

        if(G->board[y][x] == this-> number){
            inARow++;
        }

        x++;
        y--;

    }

    if(inARow > 3)
        return true;

    /*************************************/


    /************************************/
    //CHECK NE/SW DIAGONAL
    //check NE
    inARow = 0;
    y = y0;
    x = x0;
    while(x < sizeX && y < sizeY){

        if(G->board[y][x] == this-> number){
            inARow++;
        }

        x++;
        y++;

    }

    //check SW
    y = y0-1;
    x = x0-1;
    while(x >= 0 && y >= 0){

        if(G->board[y][x] == this-> number){
            inARow++;
        }

        x--;
        y--;

    }

    if(inARow > 3)
        return true;

    /*************************************/

    return false;

}






