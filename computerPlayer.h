#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "gameBoard.h"
#include "player.h"

class computerPlayer : public player {

	private:
		
		//template <typename T> int getMaxIndex(T* array, int size);
		double weight(int x, int y, int sizeX, int sizeY);

	public:
		computerPlayer(int playerNumber) : player(playerNumber){}

		int move(gameBoard *G, int col);

};

#endif


