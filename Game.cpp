#include "Game.h"

void Game::play()
{
	//初始化棋盘
	chess->init();
	while (true)
	{
		// 先由玩家走棋
		player->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
		// 再由AI走棋
		ai->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
	}
}

void Game::playpvp()
{
	//初始化棋盘
	chess->init();
	while (true)
	{
		//由玩家走棋
		player->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
		player->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
	}
}
