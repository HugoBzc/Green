#include<iostream>
#include<graphics.h>//easyx��
#include <windows.h>//windows��
#include <mmstream.h>// ����Windows��ý����ͷ�ļ�
#pragma comment(lib, "winmm.lib")// ����Windows��ý���
using namespace std;
void InitGame();//��ʼ����Ϸ
void PlayGame();//����Ϸ
int judge(int MapX, int MapY);//ʤ���ж�
int flag = 0;//��־λ
int ChessMap[20][20] = { 0 };//��¼��������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	mciSendString("play music.mp3", NULL, 0, NULL);
	InitGame();
	PlayGame();
	closegraph();
	return 0;
}
void InitGame()
{
	initgraph(600, 500);
	loadimage(NULL, "bj.png");
	setlinecolor(BLACK);
	for (int i = 0; i < 21; i++)
	{
		line(0, i * 25, 500, i * 25);
	}
	for (int i = 0; i < 21; i++)
	{
		line(i * 25, 0, i * 25, 500);
	}
	setlinestyle(PS_SOLID, 2);
	setbkmode(0);
	settextcolor(BLACK);
	outtextxy(510, 5, "���1��ִ��");
	outtextxy(510, 30, "���2��ִ��");
}//��ʼ��
int judge(int MapX, int MapY)
{
	int temp = 2 - flag % 2;

	// �����������
	for (int i = MapX - 4; i <= MapX; i++)
	{
		if (i >= 1 && i + 4 < 17) {
			if (ChessMap[i][MapY] == temp &&
				ChessMap[i + 1][MapY] == temp &&
				ChessMap[i + 2][MapY] == temp &&
				ChessMap[i + 3][MapY] == temp &&
				ChessMap[i + 4][MapY] == temp)
			{
				return 1;
			}
		}
	}

	// ����������
	for (int j = MapY - 4; j <= MapY; j++)
	{
		if (j >= 1 && j + 4 < 17)
		{
			if (ChessMap[MapX][j] == temp &&
				ChessMap[MapX][j + 1] == temp &&
				ChessMap[MapX][j + 2] == temp &&
				ChessMap[MapX][j + 3] == temp &&
				ChessMap[MapX][j + 4] == temp)
			{
				return 1;
			}
		}
	}

	// ������ϵ���������
	for (int i = MapX - 4, j = MapY - 4; i <= MapX && j <= MapY; i++, j++)
	{
		if (i >= 1 && i + 4 < 17 && j >= 1 && j + 4 < 17)
		{
			if (ChessMap[i][j] == temp &&
				ChessMap[i + 1][j + 1] == temp &&
				ChessMap[i + 2][j + 2] == temp &&
				ChessMap[i + 3][j + 3] == temp &&
				ChessMap[i + 4][j + 4] == temp)
			{
				return 1;
			}
		}
	}

	// ������ϵ���������
	for (int i = MapX - 4, j = MapY + 4; i <= MapX && j >= MapY; i++, j--)
	{
		if (i >= 1 && i + 4 < 17 && j - 4 >= 1 && j < 17)
		{
			if (ChessMap[i][j] == temp &&
				ChessMap[i + 1][j - 1] == temp &&
				ChessMap[i + 2][j - 2] == temp &&
				ChessMap[i + 3][j - 3] == temp &&
				ChessMap[i + 4][j - 4] == temp)
			{
				return 1;
			}
		}
	}

	return 0;
}
void PlayGame()
{
	int ChessX = 0, ChessY = 0;
	int MapX = 0, MapY = 0;//��¼���̵�ͼ�±�
	MOUSEMSG msg;

	HWND hwnd = GetHWnd();//��ȡ���ھ��
	while (1)
	{
		msg = GetMouseMsg();//��ȡ��궨λ
		// ��������ĸ����������������룩
		int nearestJ = static_cast<int>(round(static_cast<float>(msg.x) / 25));
		int nearestI = static_cast<int>(round(static_cast<float>(msg.y) / 25));
		// ������������Ч��Χ�ڣ�����������20x20���ӣ�����0~19��
		nearestJ = max(0, min(nearestJ, 20));
		nearestI = max(0, min(nearestI, 20));
		// �������յ���������
		ChessX = nearestJ * 25;
		ChessY = nearestI * 25;
		MapX = nearestI;
		MapY = nearestJ;

		if (msg.uMsg == WM_LBUTTONDOWN)//�ڰ׽���
		{
			if (ChessMap[MapX][MapY] != 0)
			{
				MessageBox(hwnd, "�����ظ�", "������", MB_OK);
				continue;
			}

			if (flag % 2 == 0)
			{
				setfillcolor(BLACK);
				solidcircle(ChessX, ChessY, 10);
				ChessMap[MapX][MapY] = 1;
			}
			else
			{
				setfillcolor(WHITE);
				solidcircle(ChessX, ChessY, 10);
				ChessMap[MapX][MapY] = 2;
			}
			flag++;
		}

		if (judge(MapX, MapY))
		{
			if (1 == flag % 2)
			{
				MessageBox(hwnd, "���һʤ��", "Game Over", MB_OK);
				return;
			}
			else
			{
				MessageBox(hwnd, "��Ҷ�ʤ��", "Game Over", MB_OK);
				return;
			}
		}
	}
}