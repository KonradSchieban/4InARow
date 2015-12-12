#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

class gameBoard{

	private:
	
		int sizeX;
		int sizeY;

	public:

		//Attributes:
		int** board;

		//Constructor
		gameBoard();

        //Copy Contructor
        gameBoard(const gameBoard &G);

        //Destructor
        ~gameBoard();

		//Member Functions:
        int getSizeX(){return sizeX;}
        int getSizeY(){return sizeY;}

        //Prints the gameBoard in ASCII on the console
		void print();

        //clears gameBoard: deletes all tokens from the board
        void clear();

        //returns vector of possible token heights for all possible moves. The value of a full column is -1
        std::vector<int> getAllHeights();

        //returns true if all columns are full, false otherwise
        bool allColumnsFull();

};


#endif
