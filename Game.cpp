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