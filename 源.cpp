#include<iostream>
#include"Game.h"
int X = 0;
int main()
{
	player player;
	Chess chess(13, 44, 43, 67.1);
	AI ai;
	Game game(&player, &ai, &chess);
	Intro1 intro;
	initgraph(600, 1100);
	intro.Welcome();
	if (X == 1) game.play();
	else if (X == 2) game.playpvp();
	return 0;
}