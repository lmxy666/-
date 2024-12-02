#pragma once
#include "Chess.h"
class player
{
public:
	void init(Chess* chess);
	void go();
	void gowhite();

private:
	Chess* chess;
};

