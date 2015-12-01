#ifndef PLAYER_H
#define PLAYER_H

#include"gameBoard.h"
#include<QGraphicsScene>

class player{

    protected:

		int number;
		bool checkWon(int x, int y, gameBoard* G);


        QGraphicsScene *scene;
        QBrush *brush;
        QPen *blackPen;

        int graphicsWidth;
        int graphicsHeight;

	public:

        //Constructor
        player(int playerNumber);
		
        //Destructor
        ~player();

        //Function to initialize Player for scene on which he draws tokens
        void setScene(QGraphicsScene *sceneInit, int grWidth, int grHeight);

        virtual int move(gameBoard* G, int col) = 0;
		/* returns
			0 if move was invalid	 
			1 if move was valid
			2 if player won
            3 if game is tied
		*/

        QBrush* getQBrush(){return brush;}
        QPen* getQPen(){return blackPen;}

};

#endif

