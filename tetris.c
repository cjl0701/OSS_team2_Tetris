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

//콘솔 좌표 → 배열 좌표 환산 함수
void TransPos(int* arrX, int* arrY) {

	COORD pos = getCursor(); //  현재 좌표로 구조체 초기화

	*arrX += pos.X; // 현재 x좌표 더하기 
	*arrY += pos.Y; // 현재 y좌표 더하기

	*arrX = (*arrX / 2) - 2; // 콘솔좌표->배열 열 변환값 
	*arrY = *arrY - BOARD_Y; // 콘솔좌표->배열 행 변환값

	/*  커서 x좌표는 2당 1이라고 계산(블록크기가 2라서)하기 때문에 배열로 표현할때는
	   콘솔좌표에 /2를 하고, x좌표와 y좌표에 -2를 하는 이유는 처음에 보드 출력(showBoard())할때
	   x좌표 2칸(콘솔좌표 기준은 4칸) y좌표로 2칸 이동 후 출력했기 때문이다. */
}

int IsCollision(int blockType, int moveX, int moveY) // blockType 변수는 블록 모양을 의미 moveX, moveY는 이동예정 x,y좌표
{
	int x, y; // 비교용 임시 좌표 변수
	int arrX = 0, arrY = 0; //배열좌표저장 변수 

	arrX += moveX; // 이동예정 x좌표 저장 
	arrY += moveY; // 이동예정 y좌표 저장

	TransPos(&arrX, &arrY); //좌표 환산 함수 호출

	for (y = 0; y < 4; y++) //  4x4번 총 16번 반복(블록크기인 4x4 네모 스캔)
	{
		for (x = 0; x < 4; x++)
		{
			if ((block[blockType][y][x] == 1) && board[arrY + y][arrX + x] == 1)// 현재 위치에서 blockType모양 블록이 x나 y축으로 move할 예정인 경우 
												   // 현재 위치에서 move예정인 좌표에 4x4 테두리 안에 blockType모양 블록을 가상으로 그렸다고 생각했을 때  
												   // 그 4x4테두리 안에 있는 보드판 블록이 4x4 blockType모양 블록과 한개라도 겹치면 겹쳤다고 판별  



				return 1;  // 보드에 쌓여있는 블록이나 보드판 테두리 블록과 벽돌 겹친다고 판별
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
	prove = IsCollision(rotation, 0, 0);
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
	pr = IsCollision(rotation, move1, move2);
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

/* 1~10까지 행의 열 전체가 1로되면 행의 ■사라짐.사라지면 UpdateLine함수 실행 */
void CheckLine(void)
{
	int numOfFixedCell; //고정된 ■의 수
	int x, y; //board 배열의 가로,세로 좌표 index 
	int i;
	//19행부터 시작해서 1행까지 반복
	for (y = BOARD_HEIGHT - 1; y >= 1; y--) //아래에서 위로 한칸씩 검사 y=1은 보드판
	{
		//한 행당 4번 반복=>내려온 라인을 검사하기 위해.(한번에 사라질 수 있는 라인 수는 최대 4라인이므로)
		for (iter = 0; iter < 4; iter++)
		{
			numOfFixedCell = 0;
			//board[][x]에 ■을 의미하는 값(1)이 저장되어있다.
			for (x = 1; x <= BOARD_WIDTH; x++)//x=0은 보드판
			{
				//행기준
				if (board[y][x] == 1)
				{
					numOfFixedCell++;
					//행에 ■ 10개가 전부 채워져있다면 행의 ■ 전부 삭제(line clear)
					if (numOfFixedCell == BOARD_WIDTH) {
						UpdateLine(y);
						CountScore();//line clear마다 점수 올림
					}
				}
			}
		}
	}
}

int GameOver(int blcokTpye)
{
	setCursor(CBLOCK_X, CBLOCK_Y); //블록 생성 위치 설정
	if (IsCollision(blcokTpye, 0, 0))
		return 1; //게임 끝
	else
		return 0;
}

int GameWin(void)
{
	if (level == 10)
		return 1; //게임승
	else
		return 0;
}

//키보드 입력에 따라 블록 변화
void UpdateBlock(int kb, int* pblocktype)// kb: 키보드값, pblocktype = 블록타입의 주소

{
	int prove; // 충돌검사
	int updateBlock = 0; //다음 블록 저장
	int blockType = *pblocktype; //현재 블록타입 저장

	//COORD cursor = getCursor();

	switch (kb)    //switch-case구문을 이용하여 (왼쪽,오른쪽,위,아래,스페이스) 행동지시
	{
	case LEFT:        //키보드 값이 왼쪽방향키 일때

		removeBlock(blockType, -2, 0); //블록(잔상)을 지우고 커서를 x축 -2칸 움직임(왼쪽으로 2칸(="■"한칸)움직임)
		showBlock(blockType);//블록을 화면에 출력
		/*
		prove=detect(blocktype, 2, 0);
		if(prove==0){
		   removeBlock(blocktype);
		   setCursor(cursor.X -2, cursor.Y)
		   showBlock(blocktype);
		}
		*/

		break;
	case RIGHT:      //키보드 값이 오른쪽방향키 일때
		removeBlock(blockType, 2, 0); //블록(잔상)을 지우고 커서를 x축 +2칸 움직임(오른쪽으로 2칸(="■"한칸)움직임)
		showBlock(blockType);//블록을 화면에 출력


		/*
		prove=detect(blocktype, 2, 0);
		if(prove==0){
		   removeBlock(blocktype);
		   setCursor(cursor.X +2, cursor.Y)
		   showBlock(blocktype);
		}
		*/

		break;
	case UP:       //키보드 값이 위쪽 방향키 일때

	   // 첫수를구한다.
	   //gw: nextblock에 현재 블록타입의 기본타입을 저장한다. 예를 들어 ㄴ블록의 타입은 ㄴ,┘,ㄱ,┌  총 4가지가 있고 k는 ㄴ을 저장하게 된다.(다른 블록도 마찬가지)

		updateBlock = blockType / 4;
		updateBlock *= 4;

		inintupdateblock(int* updateBlock,int bloackType){
		   *updateBlock = blockType / 4;
		   (*updateBlock) *= 4;
		}


		// 다음수가 끝수이하인가? 
		if ((blockType + 1) <= (updateBlock + 3)) //예를들어 ㄴ블록타입(ㄴ,┘,ㄱ,┌ )중에 k가 ┌(마지막타입)일경우 증가하면 다른 블록이 되므로 억제시킨다.

		{
			updateBlock = blockType + 1;         //마지막 타입이 아닐경우 현재 타입의 다음 타입을 k에 저장한다.
		}

		prove = IsCollision(updateBlock, 0, 0); //=다음타입 블록이 다른 블록이나 벽에 충돌하는지 검사

		if (prove == 0)          //다음타입 블록이 다른 블록이나 벽에 충동하지 않는다면
		{
			removeBlock(blockType, 0, 0); //블록(잔상)을 지우고 커서는 고정         
			showBlock(updateBlock);  //블록을 화면에 출력
			*pblocktype = updateBlock; //블록타입을 다음블럭으로 교체
			break;
		}
		break;
	case DOWN:      //키보드 값이 아래쪽 방향키 일때
		removeBlock(blockType, 0, 1);  //블록(잔상)을 지우고 커서를 y축 +2칸 움직임(아래쪽으로 2칸(="■"한칸)움직임)
		showBlock(blockType);
		break;
	case SPACE:     //키보드 값이 스페이스키 일때
		while (1)   //블록이 충돌이 발생할때까지 반복
		{
			removeBlock(blockType, 0, 1);     //블록(잔상)을 지우고 커서를 y축 +1칸 움직임(아래쪽으로 1칸(="■"한칸)움직임)
			if (IsCollision(blockType, 0, 1) == 1) //블럭이 다른 블록이나 벽에 충돌한다면
			{
				showBlock(blockType);         //블록을 화면에 출력
				UpdateBoardArr(blockType, 0, 0); //블록을 고정시킴
				break;
			}

		}

	}

}

void moveBlock(void)
{
	int blockType = 0;
	int kb;
	int prove;
	srand((unsigned int)time(NULL)); //srand() 인자 기반 난수를 초기화

	/*게임 시작~끝*/
	while (!(GameWin() || GameOver(blockType)))
	{
		blockType = rand() % 7;//블록 모양을 임의로 결정하기 위해 추출하는 수 
		blockType = blockType * 4; //blockType은 0~6 사이의 7개의 난수, 도형이 7개

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
			UpdateBlock(kb,&blocktype);

	
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
