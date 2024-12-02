#pragma once
#include "Chess.h"
#include<utility>
using namespace std;
#define C_NONE 0//���ӣ�����,����,����
#define C_BLACK 1
#define C_WHITE 2

//���ʹ��� �±� Ȩ��
#define OTHER 0//0,�������Ͳ�����
#define WIN 1//100000,��Ӯ
#define LOSE 2//-10000000
#define FLEX4 3//50000,�׻�4
#define flex4 4//-80000
#define BLOCK4 5//400
#define block4 6//-80000
#define FLEX3 7//400
#define flex3 8//-8000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2
enum gameResult { R_BLACK, R_WHITE, R_DRAW };//����Ӯ������Ӯ������
struct EVALUATION {

	int score;
	gameResult result;
	int STAT[8];//���沿�����εĸ���(ɱ������),�±�WIN=1Ϊ����5,LOSE=2Ϊ����5,FLEX4=3Ϊ�׻�4,BLOCK4=5Ϊ�׳�4,FLEX3=7Ϊ�׻�3
};
class chessai
{
public:
	void init(Chess* chess);
	int minimax(int depth, int alpha, int beta, bool isMaximizingPlayer);
	void init_tuple6type();
	EVALUATION evaluate(int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE]);
	void copyBoard(vector<vector<int>> A, int B[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE]);
	ChessPos* get_best_move(int depth);
	void advancedgo();

	vector<vector<int>> scoreMap;
private:
	Chess* chess;
	int tuple6type[4][4][4][4][4][4];//���ͱ�ʶ����,0����,1����,2����,3�߽�

};

