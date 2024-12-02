#pragma once
#include "player.h"
#include"AI.h"
#include"Chess.h"
#include"Intro1.h"
class Game
{
public:
	Game(player* player, AI* ai, Chess* chess)
		:player(player)
		, ai(ai)
		, chess(chess) {
		player->init(chess);
		ai->init(chess);
	}
	void play(); //¿ªÊ¼ÓÎÏ·
	void playpvp();

private:
	player* player;
	AI* ai;
	Chess* chess;
};

