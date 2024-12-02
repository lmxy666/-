#pragma once
#include "player.h"
#include"AI.h"
#include"Chess.h"
#include"Intro1.h"
#include"advancedai.h"
#include<fstream>
class Game
{
public:
	Game(player* player, AI* ai, Chess* chess,chessai* advanced)
		:player(player)
		,ai(ai)
		,chess(chess) 
		,advanced(advanced){
		player->init(chess);
		ai->init(chess);
	}
	void play();
	void playpvp();
	void playl();

private:
	player* player;
	AI* ai;
	Chess* chess;
	chessai* advanced;

















public:
	void play1();
};

