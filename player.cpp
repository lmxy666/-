#include "player.h"

void player::init(Chess* chess)
{
	this->chess = chess;
}

void player::go()
{
	MOUSEMSG msg; // ��ȡ�������Ϣ
	ChessPos pos;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->Click(msg.x, msg.y, &pos))//�ж������Ƿ���Ч
		{
			break;
		}
	}

	// ����
	chess->Luozi(&pos, black);
}
