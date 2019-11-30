#include "Cursor.h"

//콘솔화면 커서 깜빡거림 제거
void RemoveCursor(void) //hr:커서 깜박거림 제거 
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0; //hr:bvisible이 False이면 커서가 표시되지 않는다. 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


//커서의 좌표를 (2,1)로 초기화
void setCursor(int x, int y)
{
	COORD pos = { x,y };  //cjl: 좌표 표시하는 구조체
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//cjl:표준콘솔의 핸들값(ID)와 좌표 받아서 커서위치를 바꿈
}

//콘솔 화면 버퍼에 있는 커서의 좌표
COORD getCursor(void)
{
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo; //cjl:콘솔 화면 버퍼에 대한 정보
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;//cjl:콘솔 화면 버퍼에 있는 커서의 좌표
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
	/*화면 버퍼: 컴퓨터의 표시 화면.
	나타나야 할 내용을 저장하는 기억 장소로
	컴퓨터는 주기적으로 이 버퍼의 내용을 화면 접속기에 보내고
	화면 접속기는 이를 받아서 지정된 장소에 그려줌으로써 화면이 계속 보이게 된다*/
}
