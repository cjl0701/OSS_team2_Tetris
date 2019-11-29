#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define BOARD_HEIGHT 20 // ┃개수
#define BOARD_WIDTH 10  // ━개수
#define BOARD_X 4 //보드 열 x좌표
#define BOARD_Y 2 //보드 행 y좌표
#define CBLOCK_X 13
#define CBLOCK_Y 2
#define DELAY 100//지연
#define RAND 4//난수
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
int static score = 0; //게임점수
int static level = 1; //게임레벨
int static speed = 180;
int curX, curY; //콘솔커서
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };
int block[][4][4] = { //cjl:4x4 2차원 배열로 도형표시-> 2차원 배열의 배열->3차원 배열
	/*■
	  ■■■*/
	{
	 { 0,0,0,0 },
	 { 1,0,0,0 },
	 { 1,1,1,0 },
	 { 0,0,0,0 } },

	{
	 { 0,0,1,0 },
	 { 0,0,1,0 },
	 { 0,1,1,0 },
	 { 0,0,0,0 } },

	{
	 { 1,1,1,0 },
	 { 0,0,1,0 },
	 { 0,0,0,0 },
	 { 0,0,0,0 } },

	{
	 { 1,1,0,0 },
	 { 1,0,0,0 },
	 { 1,0,0,0 },
	 { 0,0,0,0 } },

	/* 두 번째 블록
	  ■
	■■■     */
	{
	 { 0, 0, 0, 0 },
	 { 0, 0, 1, 0 },
	 { 1, 1, 1, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 1, 1, 0 },
	 { 0, 0, 1, 0 },
	 { 0, 0, 1, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 1, 1, 1, 0 },
	 { 1, 0, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 1, 0, 0, 0 },
	 { 1, 0, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 } },

	/* 세 번째 블록
	 ■
	■■■    */
	{
	 { 0, 0, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 1, 1, 1, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 1, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 1, 1, 1, 0 },
	 { 0, 1, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 1, 0, 0 } },

	/* 네 번째 블록
	■■■■   */
	{
	 { 0, 1, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 1, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 1, 1, 1, 1 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 1, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 1, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 1, 1, 1, 1 },
	 { 0, 0, 0, 0 } },

	/* 다섯 번째 블록
	■■
	■■      */
	{
	 { 1, 1, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 1, 1, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 1, 1, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 1, 1, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 },
	 { 0, 0, 0, 0 } },

	/* 여섯 번째 블록
	 ■■
	■■      */
	{
	 { 0, 0, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 1, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 0, 1, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 1, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 0, 1, 0 },
	 { 0, 0, 0, 0 } },

	/* 일곱 번째 블록
	■■
	 ■■    */
	{
	 { 0, 0, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 0, 1, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 0, 0, 0 },
	 { 1, 1, 0, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 0, 0, 0 } },

	{
	 { 0, 0, 1, 0 },
	 { 0, 1, 1, 0 },
	 { 0, 1, 0, 0 },
	 { 0, 0, 0, 0 } },
};

void removeCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void setCursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD getCursor(void)
{
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
}
//void showBlock(int rotation);

void showBoard(void)
{
	int x, y;
	//중앙 보드 라인
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		setCursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //콘솔좌표
		printf("━");
	}
	//왼쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board 배열 왼쪽 1인식
		setCursor(BOARD_X, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
			printf("┗");
		else
			printf("┃");
	}
	//오른쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board 배열 오른쪽 1인식
		setCursor(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
			printf("┛");
		else
			printf("┃");
	}
	//모서리값 값 변경
	board[20][0] = 1;
	board[20][11] = 1;
	//보드판 숫자 보기
	//setCursor(6,2);
	//for(y=0; y<=BOARD_HEIGHT; y++){
	// for(x=0; x<=BOARD_WIDTH+1; x++){
	//  setCursor(4+(x*2),2+y);
	//  printf("%d ",board[y][x]);
	// }
	// printf("\n");
	//}
	puts(" ");
}

void initial(int x, int y)
{
	curX = x;
	curY = y;
	setCursor(x, y);
}

//removeBlock함수 작동전 벽인 or 아닌지확인
int detect(int rotation, int move1, int move2)
{
	int x, y;
	int arrX, arrY; //배열좌표저장
	COORD pos = getCursor();
	arrX = pos.X + move1;
	arrY = pos.Y + move2;
	arrX = (arrX / 2) - 2;
	arrY = arrY - BOARD_Y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if ((block[rotation][y][x] == 1) && board[arrY + y][arrX + x] == 1)
				return 1;  //보드와 벽돌 겹침
		}
	}
	return 0;  //겹치지 않음
}

//벽돌생성
void showBlock(int rotation)
{
	int x, y;
	COORD cursor = getCursor();
	int prove;
	//int n=(rotation-1)%4;
	prove = detect(rotation, 0, 0);
	if (prove == 0) {
		//콘솔창위치 설정, 배열값에서 1은 ■출력,0은 출력없음
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);
				if (block[rotation][y][x] == 1)
					printf("■");
			}
		}
		setCursor(cursor.X, cursor.Y);
	}
}

void removeBlock(int rotation, int move1, int move2)
{
	int pr;
	int x, y;
	COORD cursor = getCursor();
	pr = detect(rotation, move1, move2);
	if (pr == 0)
	{
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);
				if (block[rotation][y][x] == 1)
					printf(" ");
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

/*변경된 board 배열의 값을 바탕으로 콘솔 출력 */
void ShowUpdatedBoard() {
	int y, x;//반복문을 위한 변수

	for (y = 1; y <= BOARD_HEIGHT - 1; y++)
	{
		for (x = 1; x <= BOARD_WIDTH; x++)
		{
			setCursor(x * 2 + BOARD_X + 1, y + BOARD_Y);//board 배열의 값을 콘솔로 대응시키기 위한 조작,
					//+1을 하는 이유: 블록의 x좌표가 홀수 단위로 설정되어있으므로, 홀수로 맞춰주기 위해.
			if (board[y][x] == 1)
				printf("■");
			else
				printf("  ");//board배열에서 1이 아닌 부분은 빈칸으로 출력
		}
	}
}

//레벨 스코어 출력
void scoreLevel(void)
{
	setCursor(40, 3);
	printf("★레벨10 게임 클리어★");
	setCursor(40, 5);
	printf("레벨:%d\n", level);
	setCursor(40, 7);
	printf("점수:%d\n", score);
}

//레벨 스코어 계산
void countScore(void)
{
	score += 10;
	if (score % 30 == 0)
	{
		level += 1;
		speed -= 30;
	}
	scoreLevel();
}

/*한 line이 다 차면 해당 라인을 지운다 */
void ClearLine(int line)//column에는 삭제할 line의 y좌표가 전달됨.
{
	int x;
	for (x = 1; x < BOARD_WIDTH + 1; x++)
	{
		//board 배열의 값을 콘솔로 대응시키기 위해 board 배열의 index를 콘솔 좌표로 변환
		setCursor(x * 2 + BOARD_X, line + BOARD_Y);
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
void CheckLine(void)
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
						CountScore();//line clear마다 점수 올림
					}
				}
			}
		}
	}
}

int gameOver(int rotation)
{
	if (detect(rotation, 0, 0))
		return 5; //게임 끝
	else
		return 0;
}

int gameWin(void)
{
	if (level == 10)
		return 1; //게임승
	else
		return 0;
}

void moveBlock(void)
{
	int blockType;
	int kb;
	int prove;
	srand((unsigned int)time(NULL)); //srand() 인자 기반 난수를 초기화
	int c = 2;
	/*게임 시작~끝*/
	while (1)
	{
		setCursor(CBLOCK_X, CBLOCK_Y); //블록 생성 위치 설정
		blockType = rand() % 7;//블록 모양을 임의로 결정하기 위해 추출하는 수 
		blockType = blockType * 4; //blockType은 0~6 사이의 7개의 난수, 도형이 7개
		if (gameWin())//레벨이 10이면 콘솔 종료
		{
			setCursor(35, 20);
			printf("GAME WIN");
			(void)getchar();
			exit(1);
		}
		if (gameOver(blockType))//생성된 블록이 생성되자마자 다른 블록과 부딫히는가?
			break;

		showBlock(blockType);//난수로 추출한 blockType은 블록의 종류를 의미(block[blockType][4][4])
		/*블록 한개 위~밑 이동*/
		while (1)
		{
			int isBlockFixed = 0;//블록 충돌 발생 여부 알리는 flag(닿으면 1)
			int k = 0;

			/*블록 하나가 아래로 떨어지는 과정*/

			while (!_kbhit() && isBlockFixed == 0)   //키 입력이 없는 경우
				BlockFalling(blockType, &isBlockFixed);    //블록이 떨어지다 닿으면 isBlockFixed == 0이 된다.

			//블록이 자리잡았다면 한 블록의 여정이 끝난다. while문 탈출해서 다시 블록 생성부터
			if (isBlockFixed == 1)
				break;

			kb = _getch();//키보드 입력값 받아와 kb에 저장

			/*방향키*/
			switch (kb)
			{
			case LEFT:
				removeBlock(blockType, -2, 0);
				showBlock(blockType);
				break;
			case RIGHT:
				removeBlock(blockType, 2, 0);
				showBlock(blockType);
				break;
			case UP:
				// 첫수를구한다.
				k = blockType / 4;
				k *= 4;
				// 다음수가 끝수이하인가?
				if ((blockType + 1) <= (k + 3))
				{
					k = blockType + 1;
				}
				prove = detect(k, 0, 0);
				if (prove == 0)
				{
					removeBlock(blockType, 0, 0);
					blockType = k;
					showBlock(blockType);
					break;
				}
				break;
			case DOWN:
				removeBlock(blockType, 0, 2);
				//showBlock(blockType);
				break;
			case SPACE:
				while (1)
				{
					removeBlock(blockType, 0, 1);
					if (detect(blockType, 0, 1) == 1)
					{
						showBlock(blockType);
						boardConginition(blockType, 0, 0);
						break;
					}
				}
			}
		}
	}
	setCursor(35, 20);
	printf("GAME OVER");
}
int main()
{
	removeCursor(); //커서 깜박이 제거
	setCursor(2, 1); //보드표시 시작위치 설정
	showBoard(); //보드 출력
	scoreLevel();
	moveBlock(); //보드 출력 움직임
	(void)getchar();
}