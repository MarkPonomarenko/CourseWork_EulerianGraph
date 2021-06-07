#include "libs.h"
/*������������ �������*/
void rcol(int color);
/*����������� ������� �� ����������*/
void coord(int x, int y);
/*������������ ��������� ����������� ����*/
void console_settings();

void rcol(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void coord(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void console_settings()
{
	HWND hW = GetConsoleWindow();
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��� �������������
	HMENU hm;
	hm = GetSystemMenu(hW, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(hW);
	//���������� ����� ��������
	DWORD highlight_off;
	GetConsoleMode(hIn, &highlight_off);
	SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | (highlight_off & ~ENABLE_QUICK_EDIT_MODE));
	//��������� ������
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &info);
	//���������� ��������
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);
}