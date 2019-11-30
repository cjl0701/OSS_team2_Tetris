#include "GameStatus.h"

//생성된 블록이 생성되자마자 다른 블록과 부딫히는가?
int GameOver(int rotation)
{
	setCursor(CBLOCK_X, CBLOCK_Y);
	if (IsCollision(rotation, 0, 0))
		return 5; //게임 끝
	else
		return 0;
}

//레벨이 10인가?
int GameWin(int* level)
{
	if (*level == 10)
		return 1; //게임승
	else
		return 0;
}

//레벨 스코어 계산
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