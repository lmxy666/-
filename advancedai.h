#pragma once
#include "Chess.h"
#include<utility>
using namespace std;
#define C_NONE 0//棋子：黑子,白子,无子
#define C_BLACK 1
#define C_WHITE 2

//棋型代号 下标 权重
#define OTHER 0//0,其他棋型不考虑
#define WIN 1//100000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//50000,白活4
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
enum gameResult { R_BLACK, R_WHITE, R_DRAW };//黑棋赢，白棋赢，和棋
struct EVALUATION {

	int score;
	gameResult result;
	int STAT[8];//储存部分棋形的个数(杀棋棋型),下标WIN=1为白连5,LOSE=2为黑连5,FLEX4=3为白活4,BLOCK4=5为白冲4,FLEX3=7为白活3
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
	int tuple6type[4][4][4][4][4][4];//棋型辨识数组,0无子,1黑子,2白子,3边界

};

