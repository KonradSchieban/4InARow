#ifndef PLAYER_H
#define PLAYER_H

#include"gameBoard.h"
#include<QGraphicsScene>

class player{

	private:

		int number;
		bool checkWon(int x, int y, gameBoard* G);

        QGraphicsScene *scene;
        QBrush *brush;
        QPen *blackPen;

	public:

        player(int playerNumber);
        void setScene(QGraphicsScene *sceneInit);
		
		int move(int col, gameBoard* G);
		/* returns
			0 if move was invalid	 
			1 if move was valid
			2 if player won
		*/

};

#endif

