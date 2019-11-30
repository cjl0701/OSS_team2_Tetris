#include "MoveBlock.h"

int BlockFalling(int blockType, int* speed, int* level, int* score) {
	//딜레이 타임, DELAY와 전역변수 speed의 값을 바꾸면 시간 조절 가능
	Sleep(DELAY + (*speed));

	//한칸 아래로 이동시 블록이 닿는다면
	if (IsCollision(blockType, 0, 1) == 1) //0, 1은 각각 x,y좌표를 얼만큼 이동할 것인가를 의미
	{   //IsBlockFix?
		UpdateBoardArr(blockType);//블록을 보드판에 '정박'시킴. board 배열에 새로 고정된 블록의 정보 입력
		CheckLine(&*speed, &*level, &*score);//한줄이 꽉찬 상태라면 그 줄을 제거 후 위쪽 블록들 한칸씩 전부 내리기
		return 1;
	}
	removeBlock(blockType, 0, 1);//위치 갱신: 블록을 지우고 콘솔 좌표를 한칸 아래로((0,1)만큼) 이동
	Showblock(blockType);//난수로 추출한 blockType은 블록의 종류를 의미(block[blockType][4][4])
	return 0;
}

void updateBlock(int kb, int* pblocktype)//gw :  kb: 키보드값, pblocktype = 블록타입의 주소
{
	int prove; // 충돌검사
	int updateblock = 0; //블록 초기타입 저장
	int blocktype = *pblocktype;

	/*방향키*/
	switch (kb)    //gw: switch-case구문을 이용하여 (왼쪽,오른쪽,위,아래,스페이스) 행동지시
	{
	case LEFT:        //gw: 키보드 값이 왼쪽방향키 일때
		removeBlock(blocktype, -2, 0); //gw: 블록(잔상)을 지우고 커서를 x축 -2칸 움직임(왼쪽으로 2칸(="■"한칸)움직임)
		Showblock(blocktype);//gw: 블록을 화면에 출력
		break;

	case RIGHT:      //gw: 키보드 값이 오른쪽방향키 일때
		removeBlock(blocktype, 2, 0); //gw: 블록(잔상)을 지우고 커서를 x축 +2칸 움직임(오른쪽으로 2칸(="■"한칸)움직임)
		Showblock(blocktype);//gw: 블록을 화면에 출력
		break;

	case UP:       //gw: 키보드 값이 위쪽 방향키 일때

	   // 첫수를구한다.
	   //gw: nextblock에 현재 블록타입의 기본타입을 저장한다. 예를 들어 ㄴ블록의 타입은 ㄴ,┘,ㄱ,┌  총 4가지가 있고 k는 ㄴ을 저장하게 된다.(다른 블록도 마찬가지)
		updateblock = blocktype / 4;
		updateblock *= 4;

		// 다음수가 끝수이하인가? 
		if ((blocktype + 1) <= (updateblock + 3)) //gw: 예를들어 ㄴ블록타입(ㄴ,┘,ㄱ,┌ )중에 k가 ┌(마지막타입)일경우 증가하면 다른 블록이 되므로 억제시킨다.
			updateblock = blocktype + 1;         //gw: 마지막 타입이 아닐경우 현재 타입의 다음 타입을 k에 저장한다.

		prove = IsCollision(updateblock, 0, 0); //gw: 다음타입 블록이 다른 블록이나 벽에 충돌하는지 검사

		if (prove == 0)          //gw: 다음타입 블록이 다른 블록이나 벽에 충동하지 않는다면
		{
			removeBlock(blocktype, 0, 0); //gw: 블록(잔상)을 지우고 커서는 고정         
			Showblock(updateblock);  //gw: 블록을 화면에 출력
			*pblocktype = updateblock; //gw: 블록타입을 다음블럭으로 교체
			break;
		}
		break;

	case DOWN:      //gw: 키보드 값이 아래쪽 방향키 일때
		removeBlock(blocktype, 0, 1);  //gw: 블록(잔상)을 지우고 커서를 y축 +2칸 움직임(아래쪽으로 2칸(="■"한칸)움직임)
		Showblock(blocktype);
		break;

	case SPACE:     //gw: 키보드 값이 스페이스키 일때
		while (1)   //gw: 블록이 충돌이 발생할때까지 반복
		{
			removeBlock(blocktype, 0, 1);     //gw: 블록(잔상)을 지우고 커서를 y축 +1칸 움직임(아래쪽으로 1칸(="■"한칸)움직임)
			if (IsCollision(blocktype, 0, 1) == 1) //gw: 블럭이 다른 블록이나 벽에 충돌한다면
			{
				Showblock(blocktype);         //gw: 블록을 화면에 출력
				UpdateBoardArr(blocktype); //gw: 블록을 고정시킴
				break;
			}
		}
	}
}
void moveBlock(int* speed, int* level, int* score)
{
	int blockType = 0; //블록 모양
	int kb;// 키보드 입력값
	srand((unsigned int)time(NULL));
	int c = 2;
	/*게임 시작~끝*/
	while (!(GameWin(&*level) || GameOver(blockType)))
	{
		setCursor(CBLOCK_X, CBLOCK_Y); //블록 생성 위치 설정
		blockType = rand() % 7;//블록 모양을 임의로 결정하기 위해 추출하는 수 
		blockType = blockType * 4; //cjl:blockType은 0~6 사이의 7개의 난수, 도형이 7개/ *4는 왜해??

		Showblock(blockType);//난수로 추출한 blockType은 블록의 종류를 의미(block[blockType][4][4])
		/*블록 한개 위~밑 이동*/
		while (1)
		{
			int isBlockFixed = 0;//블록 충돌 발생 여부 알리는 flag(닿으면 1)
			int k = 0;

			/*블록 하나가 아래로 떨어지는 과정*/
			while (!_kbhit() && isBlockFixed == 0)//kbhit():키보드가 눌렸는지 확인. 안눌리면 0반환
				isBlockFixed = BlockFalling(blockType, &*speed, &*level, &*score);

			//블록이 자리잡았다면 한 블록의 여정이 끝난다. while문 탈출해서 다시 블록 생성부터
			if (isBlockFixed == 1)
				break;

			kb = _getch();//키보드 입력값 받아와 kb에 저장
			
						  /*방향키*/
			updateBlock(kb, &blockType);
		}
	}
	setCursor(35, 20);
	printf("GAME OVER");
}
