#include "Intro1.h"
#include "Game.h" 

void Intro1::Welcome()
{
	LPCTSTR title = _T("���������");
	LPCTSTR tpvp = _T("���˶�ս");
	LPCTSTR tplay = _T("�˻���ս");
	LPCTSTR texit = _T("�˳���Ϸ");

	RECT tplayr, texitr,tpvpr;//�������־��ο�ķ�Χ
	IMAGE img;
	loadimage(&img, L"res/Start.jpg",600,1100);
	putimage(0, 0, &img);
	BeginBatchDraw();//���������滭
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, _T("����"));//�����ı����� 
	settextcolor(BLACK);

	outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 3, title);

	settextstyle(40, 0, _T("����"));
	tpvpr.left = swidth / 2 - textwidth(tpvp) / 2;
	tpvpr.right = tpvpr.left + textwidth(tpvp);
	tpvpr.top = sheight / 5 * 2.5;
	tpvpr.bottom = tpvpr.top + textheight(tpvp);

	tplayr.left = swidth / 2 - textwidth(tplay) / 2;
	tplayr.right = tplayr.left + textwidth(tplay);
	tplayr.top = sheight / 5 * 3;
	tplayr.bottom = tplayr.top + textheight(tplay);

	texitr.left = swidth / 2 - textwidth(texit) / 2;
	texitr.right = texitr.left + textwidth(texit);
	texitr.top = sheight / 5 * 3.5;
	texitr.bottom = texitr.top + textheight(texit);

	outtextxy(tpvpr.left, tpvpr.top, tpvp);
	outtextxy(tplayr.left, tplayr.top, tplay);
	outtextxy(texitr.left, texitr.top, texit);


	EndBatchDraw();//�ر������滭������Ƶ��

	while (true)
	{
		ExMessage mess;
		getmessage(&mess, EM_MOUSE);
		if (mess.lbutton) {
			if (PointInRect(mess.x, mess.y, tplayr)) {
				X=1;
				return;
			}
			else if (PointInRect(mess.x, mess.y, texitr)) {
				exit(0);
			}
			else if (PointInRect(mess.x, mess.y, tpvpr)) {
				X = 2;
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
