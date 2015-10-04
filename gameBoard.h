#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class gameBoard{

	private:
	
		int sizeX;
		int sizeY;

	public:

		//Attributes:
		int** board;

		//Constructor
		gameBoard();

		//Member Functions:
		int getSizeX(){return sizeX;};
		int getSizeY(){return sizeY;};
		void print();

};


#endif
