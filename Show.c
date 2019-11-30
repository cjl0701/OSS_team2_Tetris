#include "Show.h"

//�ܼ�ȭ�鿡 ��Ʈ���� ������ ����
void ShowBoard(void)
{
	int x, y;
	//�߾� ���� ����
	for (x = 1; x <= BOARD_WIDTH + 1; x++)
	{
		board[BOARD_HEIGHT][x] = 1; //board �迭 �߾� 1�ν�
		setCursor((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT);  //�ܼ���ǥ
		printf("��");
	}/*x�� 1���� ������ ũ�⸸ŭ for���� �����ְ� board�迭��  1�� �ٲ��ְ�
 setCursor�� ���ؼ� x���ٰ� 2�� �����ִµ� ������ ������ ������ �ݸ� ��� �ǹǷ� 2�� �������.
 �׸��� ��ǥ���ٰ� ��輱�� �׷��ش�*/


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

	/*y�� 0���� ���̸�ŭ for���� �����ְ� board�迭���� ���� ������ 1�� �ٲ��ְ� y�� ������ ���̶� ������
  �������� ����ϰ� �ƴϸ� �������� ����Ѵ�.*/

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
	
	puts(" ");
}
//��������, �迭�� ����� 1�� ������ ����
void Showblock(int rotation)
{
	int x, y;
	COORD cursor = getCursor();
	int prove;
	prove = IsCollision(rotation, 0, 0);
	if (prove == 0) {
		//�ܼ�â��ġ ����, �迭������ 1�� �����,0�� ��¾���
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				setCursor(cursor.X + (x * 2), cursor.Y + y);//cjl:x�� ���Ƽ� 2ĭ
				if (block[rotation][y][x] == 1)
					printf("��");
			}
		}
		setCursor(cursor.X, cursor.Y);
	}
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
//�ܼ�ȭ�鿡 ������ ����
void ScoreLevel(int* level, int* score)
{
	setCursor(40, 3);
	printf("�ڷ���10 ���� Ŭ�����");
	setCursor(40, 5);
	printf("����:%d\n", *level);
	setCursor(40, 7);
	printf("����:%d\n", *score);
}