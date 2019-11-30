#include "GameProgress.h"

int IsCollision(int blockType, int moveX, int moveY) //minju blockType ������ ��� ����� �ǹ� moveX, moveY�� �̵����� x,y��ǥ
{
	int x, y; //minju �񱳿� �ӽ� ��ǥ ����
	int arrX = 0, arrY = 0; //�迭��ǥ���� ���� 

	arrX += moveX; //minju �̵����� x��ǥ ���� 
	arrY += moveY; //minju �̵����� y��ǥ ����

	TransPos(&arrX, &arrY); //��ǥ ȯ�� �Լ� ȣ��
	/* minju Ŀ�� x��ǥ�� 2�� 1�̶�� ���(���ũ�Ⱑ 2��)�ϱ� ������ �迭�� ǥ���Ҷ���
	   �ܼ���ǥ�� /2�� �ϰ�, x��ǥ�� y��ǥ�� -2�� �ϴ� ������ ó���� ���� ���(showBoard())�Ҷ�
	   x��ǥ 2ĭ(�ܼ���ǥ ������ 4ĭ) y��ǥ�� 2ĭ �̵� �� ����߱� �����̴�. */

	for (y = 0; y < 4; y++) //minju  4x4�� �� 16�� �ݺ�(���ũ���� 4x4 �׸� ��ĵ)
	{
		for (x = 0; x < 4; x++)
		{
			if ((block[blockType][y][x] == 1) && board[arrY + y][arrX + x] == 1)//minju ���� ��ġ���� blockType��� ����� x�� y������ move�� ������ ��� 
												   // ���� ��ġ���� move������ ��ǥ�� 4x4 �׵θ� �ȿ� blockType��� ����� �������� �׷ȴٰ� �������� ��  
												   // �� 4x4�׵θ� �ȿ� �ִ� ������ ����� 4x4 blockType��� ��ϰ� �Ѱ��� ��ġ�� ���ƴٰ� �Ǻ�  
				return 1;  //minju ���忡 �׿��ִ� ����̳� ������ �׵θ� ��ϰ� ���� ��ģ�ٰ� �Ǻ�
		}
	}
	return 0;  //��ġ�� ����
}

//�ܼ� ��ǥ �� �迭 ��ǥ ȯ�� �Լ�
void TransPos(int* arrX, int* arrY) {

	COORD pos = getCursor(); //minju  ���� ��ǥ�� ����ü �ʱ�ȭ

	*arrX += pos.X; //minju ���� x��ǥ ���ϱ� 
	*arrY += pos.Y; //minju ���� y��ǥ ���ϱ�

	*arrX = (*arrX / 2) - 2; //minju �ܼ���ǥ->�迭 �� ��ȯ�� 
	*arrY = *arrY - BOARD_Y; //minju �ܼ���ǥ->�迭 �� ��ȯ��
}


//��� �̵� �� �ܻ� ���� & ���ڷ� ���޵� move1,move2��ŭ Ŀ�� �̵�
void removeBlock(int rotation, int move1, int move2)
{
	int pr;
	int x, y;
	COORD cursor = getCursor();
	pr = IsCollision(rotation, move1, move2); //rotation��� 4x4 ����� move1, move2��ŭ �̵��� Ŀ�� ��ǥ�� �ִٰ� �����ϰ�
	   //rotation��� 4x4 ����� ������ ����� ���ƴٰ� �Ǻ��� ���
	if (pr == 0)//���� �ƴϸ�
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

/*�� line�� �� ���� �ش� ������ ����� */
void ClearLine(int line)//column���� ������ line�� y��ǥ�� ���޵�.
{
	int x;
	for (x = 1; x < BOARD_WIDTH + 1; x++)
	{
		setCursor(x * 2 + BOARD_X, line + BOARD_Y);//board �迭�� ���� �ַܼ� ������Ű�� ���� board �迭�� index�� �ܼ� ��ǥ�� ��ȯ
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
void CheckLine(int* speed, int* level, int* score)
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
						CountScore(&*speed, &*level, &*score);//line clear���� ���� �ø�
					}
				}
			}
		}
	}
}