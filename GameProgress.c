#include "GameProgress.h"

int IsCollision(int blockType, int moveX, int moveY) //minju blockType 변수는 블록 모양을 의미 moveX, moveY는 이동예정 x,y좌표
{
	int x, y; //minju 비교용 임시 좌표 변수
	int arrX = 0, arrY = 0; //배열좌표저장 변수 

	arrX += moveX; //minju 이동예정 x좌표 저장 
	arrY += moveY; //minju 이동예정 y좌표 저장

	TransPos(&arrX, &arrY); //좌표 환산 함수 호출
	/* minju 커서 x좌표는 2당 1이라고 계산(블록크기가 2라서)하기 때문에 배열로 표현할때는
	   콘솔좌표에 /2를 하고, x좌표와 y좌표에 -2를 하는 이유는 처음에 보드 출력(showBoard())할때
	   x좌표 2칸(콘솔좌표 기준은 4칸) y좌표로 2칸 이동 후 출력했기 때문이다. */

	for (y = 0; y < 4; y++) //minju  4x4번 총 16번 반복(블록크기인 4x4 네모 스캔)
	{
		for (x = 0; x < 4; x++)
		{
			if ((block[blockType][y][x] == 1) && board[arrY + y][arrX + x] == 1)//minju 현재 위치에서 blockType모양 블록이 x나 y축으로 move할 예정인 경우 
												   // 현재 위치에서 move예정인 좌표에 4x4 테두리 안에 blockType모양 블록을 가상으로 그렸다고 생각했을 때  
												   // 그 4x4테두리 안에 있는 보드판 블록이 4x4 blockType모양 블록과 한개라도 겹치면 겹쳤다고 판별  
				return 1;  //minju 보드에 쌓여있는 블록이나 보드판 테두리 블록과 벽돌 겹친다고 판별
		}
	}
	return 0;  //겹치지 않음
}

//콘솔 좌표 → 배열 좌표 환산 함수
void TransPos(int* arrX, int* arrY) {

	COORD pos = getCursor(); //minju  현재 좌표로 구조체 초기화

	*arrX += pos.X; //minju 현재 x좌표 더하기 
	*arrY += pos.Y; //minju 현재 y좌표 더하기

	*arrX = (*arrX / 2) - 2; //minju 콘솔좌표->배열 열 변환값 
	*arrY = *arrY - BOARD_Y; //minju 콘솔좌표->배열 행 변환값
}


//블록 이동 시 잔상 지움 & 인자로 전달된 move1,move2만큼 커서 이동
void removeBlock(int rotation, int move1, int move2)
{
	int pr;
	int x, y;
	COORD cursor = getCursor();
	pr = IsCollision(rotation, move1, move2); //rotation모양 4x4 블록이 move1, move2만큼 이동한 커서 좌표에 있다고 가정하고
	   //rotation모양 4x4 블록이 보드판 블록이 겹쳤다고 판별될 경우
	if (pr == 0)//벽이 아니면
	{
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);
				if (block[rotation][y][x] == 1)
					printf("  ");
			}
		}
		setCursor(cursor.X + move1, cursor.Y + move2);
	}
}

/*콘솔에 새로 고정된 블록의 위치를 BOARD 배열에 반영*/
void UpdateBoardArr(int blockType) //blockType은 블록의 모양을 의미하는 변수
{
	COORD pos = getCursor();//현재 커서의 좌표를 가져온다

	//콘솔의 좌표를 BOARD 배열의 값으로 대응시키기 위한 조작
	int boardXpos = (pos.X - BOARD_X) / 2;
	int boardYpos = pos.Y - BOARD_Y;

	//BOARD에 블록의 모양을 반영, 블록이 4*4 이차원 배열로 이루어져있어서 4번씩 반복하는 것.
	int x, y;
	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (block[blockType][y][x] == 1)
				board[boardYpos + y][boardXpos + x] = 1;

}

/*벽돌을 모두 채운 line을 지우기 위해 아래서부터 board배열의 값을 한칸씩 내림*/
void BoardArrDown(int column) {
	int y, x;//반복문을 위한 변수

	for (y = column; y >= 1; y--) //완성한 line부터 첫번째 라인까지 반복
		for (x = 1; x <= BOARD_WIDTH; x++)
			board[y][x] = board[y - 1][x];//윗 line에 저장된 값을 아래 line에 대입

}

/*한 line이 다 차면 해당 라인을 지운다 */
void ClearLine(int line)//column에는 삭제할 line의 y좌표가 전달됨.
{
	int x;
	for (x = 1; x < BOARD_WIDTH + 1; x++)
	{
		setCursor(x * 2 + BOARD_X, line + BOARD_Y);//board 배열의 값을 콘솔로 대응시키기 위해 board 배열의 index를 콘솔 좌표로 변환
		printf("  ");//블록이 x좌표 2칸을 차지하므로 공백 2칸으로 대체
	}
}

/*clear된 line을 지우고 갱신 */
void UpdateLine(int line) {
	ClearLine(line);
	BoardArrDown(line);//clear된 line을 삭제하므로 윗 라인들을 아래로 내림.
	ShowUpdatedBoard();
}

/* 1~10까지 행의 열 전체가 1로되면 블록사라짐.사라지면 UpdateLine함수 실행 */
void CheckLine(int* speed, int* level, int* score)
{
	int i;
	int x, y;
	int iter = 0;
	//19행부터 시작해서 1행까지 반복
	for (y = BOARD_HEIGHT - 1; y >= 1; y--) //아래에서 위로 한칸씩 검사 y=1은 보드판
	{
		//한 행당 4번 반복=>내려온 라인을 검사하기 위해.(한번에 사라질 수 있는 라인 수는 최대 4라인이므로)
		for (iter = 0; iter < 4; iter++)
		{
			i = 0;
			//board[][x]에 블록을 의미하는 값이 저장되어있다.
			for (x = 1; x <= BOARD_WIDTH; x++)//x=0은 보드판
			{
				//행기준
				if (board[y][x] == 1)
				{
					i++;
					//행에 블록 10개가 전부 채워져있다면 행의 블록 삭제(line clear)
					if (i == BOARD_WIDTH) {
						UpdateLine(y);
						CountScore(&*speed, &*level, &*score);//line clear마다 점수 올림
					}
				}
			}
		}
	}
}