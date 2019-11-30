#include "GameStatus.h"

//������ ����� �������ڸ��� �ٸ� ��ϰ� �΋H���°�?
int GameOver(int rotation)
{
	setCursor(CBLOCK_X, CBLOCK_Y);
	if (IsCollision(rotation, 0, 0))
		return 5; //���� ��
	else
		return 0;
}

//������ 10�ΰ�?
int GameWin(int* level)
{
	if (*level == 10)
		return 1; //���ӽ�
	else
		return 0;
}

//���� ���ھ� ���
void CountScore(int* speed, int* level, int* score)
{
	*score += 10;
	if (*score % 30 == 0)
	{
		*level += 1;
		*speed -= 30;
	}
	ScoreLevel(&*level, &*score);
}