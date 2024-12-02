#pragma once
#include<iostream>
#include <graphics.h> //easyx
#include <vector>
#include<conio.h>
extern int X;
using std::vector;
const int BOARD_GRAD_SIZE = 13;
struct  ChessData {
	// 存储当前游戏棋盘和棋子的情况,空白为0，黑子1，白子-1
	int chessMap[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE];

	// 存储各个点位的评分情况，作为AI下棋依据
	int scoreMap[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE];

	// 标示下棋方, true:黑棋方  false: AI 白棋方（AI方）
	bool playerFlag;
};
struct ChessPos { //落子位置
	int row;  //行
	int col;  //列

	ChessPos(int r = 0, int c = 0):row(r),col(c){}
};
typedef enum {
	white = -1,
	black = 1
}chess_kind;
class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize)
		:gradeSize(gradeSize)
		, margin_x(marginX)
		, margin_y(marginY)
		, chessSize(chessSize) {
		playerFlag = black;
		for (int i = 0; i < gradeSize; i++)
		{
			vector<int> row;
			for (int j = 0; j < gradeSize; j++)
				row.push_back(0);
			chessMap.push_back(row);
		}
	}

	void init(); //初始化
	void Luozi(ChessPos* pos, chess_kind kind);  //实现落子功能
	bool Click(int x, int y, ChessPos* pos);  //判断点击是否有效
	int getSize(); //获得棋盘大小
	bool over();  //检查棋局是否结束
	bool playerFlag; //true:该黑走 false:该白走
	int getchessdata(int row, int col);
	int getchessdata(ChessPos* pos);
	bool is_valid_move(int x, int y) const {
		return (x >= 0 && x < BOARD_GRAD_SIZE && y >= 0 && y < BOARD_GRAD_SIZE && chessMap[x][y] == 0);
	}
	void make_move(int x, int y, int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE], chess_kind kind) {
		A[x][y] = kind;
	}//在虚拟棋盘上下棋
	void undo_move(int x, int y, int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE]) {
		A[x][y] = 0;
	}//在虚拟棋盘上撤销棋
	vector<vector<int>> chessMap; //存储棋子分布数据 0：空白 1：黑子 -1：白子
	bool PointInRect(int x, int y, RECT& r)
	{
		return (x >= r.left && x <= r.right && y >= r.top && y <= r.bottom);
	}

private:
	IMAGE chessBlackImg; //黑棋棋子
	IMAGE chessWhiteImg; //白棋棋子

	int gradeSize; //棋盘大小
	int margin_x; //棋盘的左侧边界
	int margin_y; //棋盘的顶部边界
	float chessSize; //棋子大小


	void update(ChessPos* pos);
	bool checkWin();//检查是否胜利
	ChessPos lastPos; //最近落子位置
public:
	void Stock();
	void play();
	void Fupan();
private:
	vector<int> information;
	int num;
};