#include "Chess.h"
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

void putimagePNG1(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Chess::init()
{
	// 创建游戏窗口
	initgraph(897, 895, EW_SHOWCONSOLE);

	// 显示棋盘图片
	loadimage(0, L"res/棋盘2.jpg");
	// 播放开始提示音
	mciSendString(L"play res/start.wav", 0, 0, 0);
	//加载黑棋和白棋棋子图片
	loadimage(&chessBlackImg, L"res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, L"res/white.png", chessSize, chessSize, true);
	//棋盘清零
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			chessMap[i][j] = 0;
		}
	}
	playerFlag = true;
}

void Chess::Luozi(ChessPos* pos, chess_kind kind)
{
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize; //获得落子位置的坐标
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

	if (kind == white)
	{
		mciSendString(L"play res/down8.WAV", 0, 0, 0);
		putimagePNG1(x, y, &chessWhiteImg);  //放置白色棋子图片
	}
	else {
		mciSendString(L"play res/down8.WAV", 0, 0, 0);
		putimagePNG1(x, y, &chessBlackImg);  //放置黑色棋子图片
	}
	update(pos);
}

bool Chess::Click(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row; //获得离点击位置最近的方格左上角节点的位置
	int offset = chessSize * 0.2; //设定一个偏离值

	int len;
	bool ret = false;
	do {

		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY)); //获得点击位置距离节点的距离
		if (len < offset)  //如果距离小于偏离值，就可以落子
		{
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) //判断原先是否有棋子
			{
				ret = true;
			}
			break;
		}

		//右上角的判断
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset)  //如果距离小于偏离值，就可以落子
		{
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) //判断原先是否有棋子
			{
				ret = true;
			}
			break;
		}

		//左下角的判断
		int x3 = leftTopPosX;
		int y3 = leftTopPosY + chessSize;
		len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
		if (len < offset)  //如果距离小于偏离值，就可以落子
		{
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) //判断原先是否有棋子
			{
				ret = true;
			}
			break;
		}

		//右下角的判断
		int x4 = leftTopPosX + chessSize;
		int y4 = leftTopPosY + chessSize;
		len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
		if (len < offset)  //如果距离小于偏离值，就可以落子
		{
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) //判断原先是否有棋子
			{
				ret = true;
			}
			break;
		}

	} while (0);
	return ret;

}

int Chess::getSize()
{
	return gradeSize;
}

bool Chess::over()
{
	if (checkWin() ){
		Sleep(1500);
		if (playerFlag == false) {
			mciSendString(L"play res/胜利结算.mp3", 0, 0, 0);
			loadimage(0, L"res/胜利.jpg");
		}
		else {
			loadimage(0, L"res/失败.jpg");
			mciSendString(L"play res/不错.mp3", 0, 0, 0);
		}

		_getch();
		return true;
	}

	return false;
}

int Chess::getchessdata(ChessPos* pos) {
	return chessMap[pos->row][pos->col];
}
int Chess::getchessdata(int row, int col)
{
	if (chessMap[row][col] == 1){
		return 1;
	}
	if (chessMap[row][col] == -1){
		return -1;
	}
	else {
		return 0;
	}
	return false;
}

void Chess::update(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? black : white;
	playerFlag = !playerFlag; //黑白方交换
}

bool Chess::checkWin()
{
	// 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
	// 水平方向
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		// 往左5个，往右匹配4个子，20种情况
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// 竖直方向(上下延伸4个)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
			return true;
	}

	// “/"方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			// 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// “\“ 方向
	for (int i = 0; i < 5; i++)
	{
		// 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}
