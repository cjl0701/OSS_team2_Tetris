#include "Cursor.h"

//�ܼ�ȭ�� Ŀ�� �����Ÿ� ����
void RemoveCursor(void) //hr:Ŀ�� ���ڰŸ� ���� 
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0; //hr:bvisible�� False�̸� Ŀ���� ǥ�õ��� �ʴ´�. 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


//Ŀ���� ��ǥ�� (2,1)�� �ʱ�ȭ
void setCursor(int x, int y)
{
	COORD pos = { x,y };  //cjl: ��ǥ ǥ���ϴ� ����ü
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//cjl:ǥ���ܼ��� �ڵ鰪(ID)�� ��ǥ �޾Ƽ� Ŀ����ġ�� �ٲ�
}

//�ܼ� ȭ�� ���ۿ� �ִ� Ŀ���� ��ǥ
COORD getCursor(void)
{
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo; //cjl:�ܼ� ȭ�� ���ۿ� ���� ����
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;//cjl:�ܼ� ȭ�� ���ۿ� �ִ� Ŀ���� ��ǥ
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
	/*ȭ�� ����: ��ǻ���� ǥ�� ȭ��.
	��Ÿ���� �� ������ �����ϴ� ��� ��ҷ�
	��ǻ�ʹ� �ֱ������� �� ������ ������ ȭ�� ���ӱ⿡ ������
	ȭ�� ���ӱ�� �̸� �޾Ƽ� ������ ��ҿ� �׷������ν� ȭ���� ��� ���̰� �ȴ�*/
}
