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
		player->gowhite();
		if (chess->over()) {
			chess->init();
			continue;
		}
	}
}

void Game::playl()
{
	chess->init();
	while (true)
	{
		player->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
		advanced->advancedgo();
		if (chess->over()) {
			chess->init();
			continue;
		}
	}
}


























void Game::play1()
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