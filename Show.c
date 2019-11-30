#include "Show.h"

//콘솔화면에 테트리스 게임판 생성
void ShowBoard(void)
{
	int x, y;
	//중앙 보드 라인
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board 배열 중앙 1인식
		setCursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //콘솔좌표
		printf("━");
	}/*x를 1부터 보드의 크기만큼 for문을 돌려주고 board배열에  1로 바꿔주고
 setCursor를 통해서 x에다가 2를 곱해주는데 이유는 곱하지 않으면 반만 출력 되므로 2를 곱해줬다.
 그리고 좌표에다가 경계선을 그려준다*/


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

	/*y를 0부터 높이만큼 for문을 돌려주고 board배열에서 왼쪽 라인을 1로 바꿔주고 y가 보드의 높이랑 같으면
  ’┗’을 출력하고 아니면 ‘┃’을 출력한다.*/

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
	
	puts(" ");
}
//벽돌생성, 배열에 저장된 1을 ■으로 변경
void Showblock(int rotation)
{
	int x, y;
	COORD cursor = getCursor();
	int prove;
	prove = IsCollision(rotation, 0, 0);
	if (prove == 0) {
		//콘솔창위치 설정, 배열값에서 1은 ■출력,0은 출력없음
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);//cjl:x는 좁아서 2칸
				if (block[rotation][y][x] == 1)
					printf("■");
			}
		}
		setCursor(cursor.X, cursor.Y);
	}
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
//콘솔화면에 점수판 생성
void ScoreLevel(int* level, int* score)
{
	setCursor(40, 3);
	printf("★레벨10 게임 클리어★");
	setCursor(40, 5);
	printf("레벨:%d\n", *level);
	setCursor(40, 7);
	printf("점수:%d\n", *score);
}