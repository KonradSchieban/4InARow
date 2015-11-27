#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include"gameBoard.h"
#include"player.h"

class humanPlayer : public player{

	public:
		humanPlayer(int playerNumber):player(playerNumber)
		{

		}

		int move(gameBoard* G, int col);

};


#endif
