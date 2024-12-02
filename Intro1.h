#pragma once
#include"Game.h"
extern int X;
constexpr auto swidth = 600;
constexpr auto sheight = 1100;
class Intro1
{
public:
	void Welcome();
	bool PointInRect(int x, int y, RECT& r);
};

