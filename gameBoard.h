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

        //Destructor
        ~gameBoard();

		//Member Functions:
        int getSizeX(){return sizeX;}
        int getSizeY(){return sizeY;}

        //Prints the gameBoard in ASCII on the console
		void print();

        //clears gameBoard: deletes all tokens from the board
        void clear();

};


#endif
