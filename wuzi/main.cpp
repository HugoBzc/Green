#include<iostream>
#include<graphics.h>//easyx库
#include <windows.h>//windows库
#include <mmstream.h>// 包含Windows多媒体流头文件
#pragma comment(lib, "winmm.lib")// 链接Windows多媒体库
using namespace std;
void InitGame();//初始化游戏
void PlayGame();//玩游戏
int judge(int MapX, int MapY);//胜负判定
int flag = 0;//标志位
int ChessMap[20][20] = { 0 };//记录棋盘数组
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
	outtextxy(510, 5, "玩家1：执黑");
	outtextxy(510, 30, "玩家2：执白");
}//初始化
int judge(int MapX, int MapY)
{
	int temp = 2 - flag % 2;

	// 检查纵向五连
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

	// 检查横向五连
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

	// 检查左上到右下五连
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

	// 检查右上到左下五连
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
	int MapX = 0, MapY = 0;//记录棋盘地图下标
	MOUSEMSG msg;

	HWND hwnd = GetHWnd();//获取窗口句柄
	while (1)
	{
		msg = GetMouseMsg();//获取鼠标定位
		// 计算最近的格子索引（四舍五入）
		int nearestJ = static_cast<int>(round(static_cast<float>(msg.x) / 25));
		int nearestI = static_cast<int>(round(static_cast<float>(msg.y) / 25));
		// 限制索引在有效范围内（假设棋盘是20x20格子，索引0~19）
		nearestJ = max(0, min(nearestJ, 20));
		nearestI = max(0, min(nearestI, 20));
		// 计算最终的棋子坐标
		ChessX = nearestJ * 25;
		ChessY = nearestI * 25;
		MapX = nearestI;
		MapY = nearestJ;

		if (msg.uMsg == WM_LBUTTONDOWN)//黑白交替
		{
			if (ChessMap[MapX][MapY] != 0)
			{
				MessageBox(hwnd, "落子重复", "五子棋", MB_OK);
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
				MessageBox(hwnd, "玩家一胜利", "Game Over", MB_OK);
				return;
			}
			else
			{
				MessageBox(hwnd, "玩家二胜利", "Game Over", MB_OK);
				return;
			}
		}
	}
}