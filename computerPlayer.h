#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "gameBoard.h"
#include "player.h"

class computerPlayer : public player {

	private:
		
		//template <typename T> int getMaxIndex(T* array, int size);
		double weight(int x, int y, int sizeX, int sizeY);

        //returns the "score" for player with number playerNumber. Target function for MinMax algorithm
        int valueFunction(gameBoard* G, int playerNumber);

	public:
		computerPlayer(int playerNumber) : player(playerNumber){}

        //implements virtual function move from base class. parameter col not needed
		int move(gameBoard *G, int col);

};

#endif


