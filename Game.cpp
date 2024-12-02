#include "Game.h"

void Game::play()
{
	//��ʼ������
	chess->init();
	while (true)
	{
		// �����������
		player->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
		// ����AI����
		ai->go();
		if (chess->over()) {
			chess->init();
			continue;
		}
	}
}

void Game::playpvp()
{
	//��ʼ������
	chess->init();
	while (true)
	{
		//���������
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
