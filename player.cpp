#include "player.h"

void player::init(Chess* chess)
{
	this->chess = chess;
}

void player::go()
{
	MOUSEMSG msg; // 获取鼠标点击消息
	ChessPos pos;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->Click(msg.x, msg.y, &pos))//判断落子是否有效
		{
			break;
		}
	}

	// 落子
	chess->Luozi(&pos, black);
}
