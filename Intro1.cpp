#include "Intro1.h"
#include "Game.h" 

void Intro1::Welcome()
{
	LPCTSTR title = _T("五子棋课设");
	LPCTSTR tpvp = _T("人人对战");
	LPCTSTR tplay = _T("人机对战--普通难度");
	LPCTSTR tplay2 = _T("人机对战--困难难度");
	LPCTSTR texit = _T("退出游戏");

	RECT tplayr, texitr,tpvpr,tplayr2;//定义文字矩形块的范围
	IMAGE img;
	loadimage(&img, L"res/Start.jpg",600,1100);
	putimage(0, 0, &img);
	BeginBatchDraw();//开启批量绘画
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, _T("黑体"));//设置文本类型 
	settextcolor(BLACK);

	outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 3, title);

	settextstyle(40, 0, _T("黑体"));
	tpvpr.left = swidth / 2 - textwidth(tpvp) / 2;
	tpvpr.right = tpvpr.left + textwidth(tpvp);
	tpvpr.top = sheight / 5 * 2.2;
	tpvpr.bottom = tpvpr.top + textheight(tpvp);

	tplayr.left = swidth / 2 - textwidth(tplay) / 2;
	tplayr.right = tplayr.left + textwidth(tplay);
	tplayr.top = sheight / 5 * 2.7;
	tplayr.bottom = tplayr.top + textheight(tplay);

	tplayr2.left = swidth / 2 - textwidth(tplay2) / 2;
	tplayr2.right = tplayr2.left + textwidth(tplay2);
	tplayr2.top = sheight / 5 * 3.2;
	tplayr2.bottom = tplayr2.top + textheight(tplay2);

	texitr.left = swidth / 2 - textwidth(texit) / 2;
	texitr.right = texitr.left + textwidth(texit);
	texitr.top = sheight / 5 * 3.7;
	texitr.bottom = texitr.top + textheight(texit);

	outtextxy(tpvpr.left, tpvpr.top, tpvp);
	outtextxy(tplayr.left, tplayr.top, tplay);
	outtextxy(tplayr2.left, tplayr2.top, tplay2);
	outtextxy(texitr.left, texitr.top, texit);


	EndBatchDraw();//关闭批量绘画，减少频闪

	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE);
		if (mess.lbutton) {
			if (PointInRect(mess.x, mess.y, tplayr)) {
				X = 1;
				return;
			}
			else if (PointInRect(mess.x, mess.y, texitr)) {
				exit(0);
			}
			else if (PointInRect(mess.x, mess.y, tpvpr)) {
				X = 2;
				return;
			}
			else if (PointInRect(mess.x, mess.y, tplayr2)) {
				X = 3;
				return;
			}
		}
	}
	Sleep(100);
}

bool Intro1::PointInRect(int x, int y, RECT& r)
{
	return (x >= r.left && x <= r.right && y >= r.top && y <= r.bottom);
}
