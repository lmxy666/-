#include "Chess.h"
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

void putimagePNG1(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Chess::init()
{
	// ������Ϸ����
	initgraph(897, 895, EW_SHOWCONSOLE);

	// ��ʾ����ͼƬ
	loadimage(0, L"res/����2.jpg");
	// ���ſ�ʼ��ʾ��
	mciSendString(L"play res/start.wav", 0, 0, 0);
	//���غ���Ͱ�������ͼƬ
	loadimage(&chessBlackImg, L"res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, L"res/white.png", chessSize, chessSize, true);
	//��������
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
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize; //�������λ�õ�����
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

	if (kind == white)
	{
		mciSendString(L"play res/down8.WAV", 0, 0, 0);
		putimagePNG1(x, y, &chessWhiteImg);  //���ð�ɫ����ͼƬ
	}
	else {
		mciSendString(L"play res/down8.WAV", 0, 0, 0);
		putimagePNG1(x, y, &chessBlackImg);  //���ú�ɫ����ͼƬ
	}
	update(pos);
}

bool Chess::Click(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row; //�������λ������ķ������Ͻǽڵ��λ��
	int offset = chessSize * 0.2; //�趨һ��ƫ��ֵ

	int len;
	bool ret = false;
	do {

		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY)); //��õ��λ�þ���ڵ�ľ���
		if (len < offset)  //�������С��ƫ��ֵ���Ϳ�������
		{
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) //�ж�ԭ���Ƿ�������
			{
				ret = true;
			}
			break;
		}

		//���Ͻǵ��ж�
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset)  //�������С��ƫ��ֵ���Ϳ�������
		{
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) //�ж�ԭ���Ƿ�������
			{
				ret = true;
			}
			break;
		}

		//���½ǵ��ж�
		int x3 = leftTopPosX;
		int y3 = leftTopPosY + chessSize;
		len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
		if (len < offset)  //�������С��ƫ��ֵ���Ϳ�������
		{
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) //�ж�ԭ���Ƿ�������
			{
				ret = true;
			}
			break;
		}

		//���½ǵ��ж�
		int x4 = leftTopPosX + chessSize;
		int y4 = leftTopPosY + chessSize;
		len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
		if (len < offset)  //�������С��ƫ��ֵ���Ϳ�������
		{
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) //�ж�ԭ���Ƿ�������
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
			mciSendString(L"play res/ʤ������.mp3", 0, 0, 0);
			loadimage(0, L"res/ʤ��.jpg");
		}
		else {
			loadimage(0, L"res/ʧ��.jpg");
			mciSendString(L"play res/����.mp3", 0, 0, 0);
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
	playerFlag = !playerFlag; //�ڰ׷�����
}

bool Chess::checkWin()
{
	// ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	// ˮƽ����
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// ��ֱ����(��������4��)
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

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
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
