#include<iostream>
#include"Game.h"
#include "advancedai.h"
int X = 0;
int main()
{
	player player;
	Chess chess(13, 44, 43, 67.1);
	AI ai;
	chessai advancedai;
	Game game(&player, &ai, &chess,&advancedai);
	Intro1 intro;
	initgraph(600, 1100);
	intro.Welcome();
	if (X == 1) game.play();
	else if (X == 2) game.playpvp();
	else if (X == 3) game.play1();
	else if (X == 4) chess.Fupan();
	return 0;
}