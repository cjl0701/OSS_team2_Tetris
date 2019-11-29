#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define BOARD_HEIGHT 20 // ������
#define BOARD_WIDTH 10  // ������
#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ
#define CBLOCK_X 13
#define CBLOCK_Y 2
#define DELAY 100//����
#define RAND 4//����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
int static score = 0; //��������
int static level = 1; //���ӷ���
int static speed = 180;
int curX, curY; //�ܼ�Ŀ��
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };
int block[][4][4] = { //cjl:4x4 2���� �迭�� ����ǥ��-> 2���� �迭�� �迭->3���� �迭
	/*��
	  ����*/
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

	/* �� ��° ���
	  ��
	����     */
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

	/* �� ��° ���
	 ��
	����    */
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

	/* �� ��° ���
	�����   */
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

	/* �ټ� ��° ���
	���
	���      */
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

	/* ���� ��° ���
	 ���
	���      */
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

	/* �ϰ� ��° ���
	���
	 ���    */
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
	//�߾� ���� ����
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		setCursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //�ܼ���ǥ
		printf("��");
	}
	//���� ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][0] = 1; //board �迭 ���� 1�ν�
		setCursor(BOARD_X, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}
	//������ ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		board[y][BOARD_WIDTH + 1] = 1; //board �迭 ������ 1�ν�
		setCursor(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
		if (y == BOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}
	//�𼭸��� �� ����
	board[20][0] = 1;
	board[20][11] = 1;
	//������ ���� ����
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

//removeBlock�Լ� �۵��� ���� or �ƴ���Ȯ��
int detect(int rotation, int move1, int move2)
{
	int x, y;
	int arrX, arrY; //�迭��ǥ����
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
				return 1;  //����� ���� ��ħ
		}
	}
	return 0;  //��ġ�� ����
}

//��������
void showBlock(int rotation)
{
	int x, y;
	COORD cursor = getCursor();
	int prove;
	//int n=(rotation-1)%4;
	prove = detect(rotation, 0, 0);
	if (prove == 0) {
		//�ܼ�â��ġ ����, �迭������ 1�� �����,0�� ��¾���
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);
				if (block[rotation][y][x] == 1)
					printf("��");
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

/*�ֿܼ� ���� ������ ����� ��ġ�� BOARD �迭�� �ݿ�*/
void UpdateBoardArr(int blockType) //blockType�� ����� ����� �ǹ��ϴ� ����
{
	COORD pos = getCursor();//���� Ŀ���� ��ǥ�� �����´�

	//�ܼ��� ��ǥ�� BOARD �迭�� ������ ������Ű�� ���� ����
	int boardXpos = (pos.X - BOARD_X) / 2;
	int boardYpos = pos.Y - BOARD_Y;

	//BOARD�� ����� ����� �ݿ�, ����� 4*4 ������ �迭�� �̷�����־ 4���� �ݺ��ϴ� ��.
	int x, y;
	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (block[blockType][y][x] == 1)
				board[boardYpos + y][boardXpos + x] = 1;

}

/*������ ��� ä�� line�� ����� ���� �Ʒ������� board�迭�� ���� ��ĭ�� ����*/
void BoardArrDown(int column) {
	int y, x;//�ݺ����� ���� ����

	for (y = column; y >= 1; y--) //�ϼ��� line���� ù��° ���α��� �ݺ�
		for (x = 1; x <= BOARD_WIDTH; x++)
			board[y][x] = board[y - 1][x];//�� line�� ����� ���� �Ʒ� line�� ����

}

/*����� board �迭�� ���� �������� �ܼ� ��� */
void ShowUpdatedBoard() {
	int y, x;//�ݺ����� ���� ����

	for (y = 1; y <= BOARD_HEIGHT - 1; y++)
	{
		for (x = 1; x <= BOARD_WIDTH; x++)
		{
			setCursor(x * 2 + BOARD_X + 1, y + BOARD_Y);//board �迭�� ���� �ַܼ� ������Ű�� ���� ����,
					//+1�� �ϴ� ����: ����� x��ǥ�� Ȧ�� ������ �����Ǿ������Ƿ�, Ȧ���� �����ֱ� ����.
			if (board[y][x] == 1)
				printf("��");
			else
				printf("  ");//board�迭���� 1�� �ƴ� �κ��� ��ĭ���� ���
		}
	}
}

//���� ���ھ� ���
void scoreLevel(void)
{
	setCursor(40, 3);
	printf("�ڷ���10 ���� Ŭ�����");
	setCursor(40, 5);
	printf("����:%d\n", level);
	setCursor(40, 7);
	printf("����:%d\n", score);
}

//���� ���ھ� ���
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

/*�� line�� �� ���� �ش� ������ ����� */
void ClearLine(int line)//column���� ������ line�� y��ǥ�� ���޵�.
{
	int x;
	for (x = 1; x < BOARD_WIDTH + 1; x++)
	{
		//board �迭�� ���� �ַܼ� ������Ű�� ���� board �迭�� index�� �ܼ� ��ǥ�� ��ȯ
		setCursor(x * 2 + BOARD_X, line + BOARD_Y);
		printf("  ");//����� x��ǥ 2ĭ�� �����ϹǷ� ���� 2ĭ���� ��ü
	}
}

/*clear�� line�� ����� ���� */
void UpdateLine(int line) {
	ClearLine(line);
	BoardArrDown(line);//clear�� line�� �����ϹǷ� �� ���ε��� �Ʒ��� ����.
	ShowUpdatedBoard();
}

/* 1~10���� ���� �� ��ü�� 1�εǸ� ��ϻ����.������� UpdateLine�Լ� ���� */
void CheckLine(void)
{
	int i;
	int x, y;
	int iter = 0;
	//19����� �����ؼ� 1����� �ݺ�
	for (y = BOARD_HEIGHT - 1; y >= 1; y--) //�Ʒ����� ���� ��ĭ�� �˻� y=1�� ������
	{
		//�� ��� 4�� �ݺ�=>������ ������ �˻��ϱ� ����.(�ѹ��� ����� �� �ִ� ���� ���� �ִ� 4�����̹Ƿ�)
		for (iter = 0; iter < 4; iter++)
		{
			i = 0;
			//board[][x]�� ����� �ǹ��ϴ� ���� ����Ǿ��ִ�.
			for (x = 1; x <= BOARD_WIDTH; x++)//x=0�� ������
			{
				//�����
				if (board[y][x] == 1)
				{
					i++;
					//�࿡ ��� 10���� ���� ä�����ִٸ� ���� ��� ����(line clear)
					if (i == BOARD_WIDTH) {
						UpdateLine(y);
						CountScore();//line clear���� ���� �ø�
					}
				}
			}
		}
	}
}

int gameOver(int rotation)
{
	if (detect(rotation, 0, 0))
		return 5; //���� ��
	else
		return 0;
}

int gameWin(void)
{
	if (level == 10)
		return 1; //���ӽ�
	else
		return 0;
}

void moveBlock(void)
{
	int blockType;
	int kb;
	int prove;
	srand((unsigned int)time(NULL)); //srand() ���� ��� ������ �ʱ�ȭ
	int c = 2;
	/*���� ����~��*/
	while (1)
	{
		setCursor(CBLOCK_X, CBLOCK_Y); //��� ���� ��ġ ����
		blockType = rand() % 7;//��� ����� ���Ƿ� �����ϱ� ���� �����ϴ� �� 
		blockType = blockType * 4; //blockType�� 0~6 ������ 7���� ����, ������ 7��
		if (gameWin())//������ 10�̸� �ܼ� ����
		{
			setCursor(35, 20);
			printf("GAME WIN");
			(void)getchar();
			exit(1);
		}
		if (gameOver(blockType))//������ ����� �������ڸ��� �ٸ� ��ϰ� �΋H���°�?
			break;

		showBlock(blockType);//������ ������ blockType�� ����� ������ �ǹ�(block[blockType][4][4])
		/*��� �Ѱ� ��~�� �̵�*/
		while (1)
		{
			int isBlockFixed = 0;//��� �浹 �߻� ���� �˸��� flag(������ 1)
			int k = 0;

			/*��� �ϳ��� �Ʒ��� �������� ����*/

			while (!_kbhit() && isBlockFixed == 0)   //Ű �Է��� ���� ���
				BlockFalling(blockType, &isBlockFixed);    //����� �������� ������ isBlockFixed == 0�� �ȴ�.

			//����� �ڸ���Ҵٸ� �� ����� ������ ������. while�� Ż���ؼ� �ٽ� ��� ��������
			if (isBlockFixed == 1)
				break;

			kb = _getch();//Ű���� �Է°� �޾ƿ� kb�� ����

			/*����Ű*/
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
				// ù�������Ѵ�.
				k = blockType / 4;
				k *= 4;
				// �������� ���������ΰ�?
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
	removeCursor(); //Ŀ�� ������ ����
	setCursor(2, 1); //����ǥ�� ������ġ ����
	showBoard(); //���� ���
	scoreLevel();
	moveBlock(); //���� ��� ������
	(void)getchar();
}