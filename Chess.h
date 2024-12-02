#pragma once
#include<iostream>
#include <graphics.h> //easyx
#include <vector>
#include<conio.h>
extern int X;
using std::vector;
const int BOARD_GRAD_SIZE = 13;
struct  ChessData {
	// �洢��ǰ��Ϸ���̺����ӵ����,�հ�Ϊ0������1������-1
	int chessMap[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE];

	// �洢������λ�������������ΪAI��������
	int scoreMap[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE];

	// ��ʾ���巽, true:���巽  false: AI ���巽��AI����
	bool playerFlag;
};
struct ChessPos { //����λ��
	int row;  //��
	int col;  //��

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

	void init(); //��ʼ��
	void Luozi(ChessPos* pos, chess_kind kind);  //ʵ�����ӹ���
	bool Click(int x, int y, ChessPos* pos);  //�жϵ���Ƿ���Ч
	int getSize(); //������̴�С
	bool over();  //�������Ƿ����
	bool playerFlag; //true:�ú��� false:�ð���
	int getchessdata(int row, int col);
	int getchessdata(ChessPos* pos);
	bool is_valid_move(int x, int y) const {
		return (x >= 0 && x < BOARD_GRAD_SIZE && y >= 0 && y < BOARD_GRAD_SIZE && chessMap[x][y] == 0);
	}
	void make_move(int x, int y, int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE], chess_kind kind) {
		A[x][y] = kind;
	}//����������������
	void undo_move(int x, int y, int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE]) {
		A[x][y] = 0;
	}//�����������ϳ�����
	vector<vector<int>> chessMap; //�洢���ӷֲ����� 0���հ� 1������ -1������
	bool PointInRect(int x, int y, RECT& r)
	{
		return (x >= r.left && x <= r.right && y >= r.top && y <= r.bottom);
	}

private:
	IMAGE chessBlackImg; //��������
	IMAGE chessWhiteImg; //��������

	int gradeSize; //���̴�С
	int margin_x; //���̵����߽�
	int margin_y; //���̵Ķ����߽�
	float chessSize; //���Ӵ�С


	void update(ChessPos* pos);
	bool checkWin();//����Ƿ�ʤ��
	ChessPos lastPos; //�������λ��
public:
	void Stock();
	void play();
	void Fupan();
private:
	vector<int> information;
	int num;
};