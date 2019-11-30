#include "MoveBlock.h"

int BlockFalling(int blockType, int* speed, int* level, int* score) {
	//������ Ÿ��, DELAY�� �������� speed�� ���� �ٲٸ� �ð� ���� ����
	Sleep(DELAY + (*speed));

	//��ĭ �Ʒ��� �̵��� ����� ��´ٸ�
	if (IsCollision(blockType, 0, 1) == 1) //0, 1�� ���� x,y��ǥ�� ��ŭ �̵��� ���ΰ��� �ǹ�
	{   //IsBlockFix?
		UpdateBoardArr(blockType);//����� �����ǿ� '����'��Ŵ. board �迭�� ���� ������ ����� ���� �Է�
		CheckLine(&*speed, &*level, &*score);//������ ���� ���¶�� �� ���� ���� �� ���� ��ϵ� ��ĭ�� ���� ������
		return 1;
	}
	removeBlock(blockType, 0, 1);//��ġ ����: ����� ����� �ܼ� ��ǥ�� ��ĭ �Ʒ���((0,1)��ŭ) �̵�
	Showblock(blockType);//������ ������ blockType�� ����� ������ �ǹ�(block[blockType][4][4])
	return 0;
}

void updateBlock(int kb, int* pblocktype)//gw :  kb: Ű���尪, pblocktype = ���Ÿ���� �ּ�
{
	int prove; // �浹�˻�
	int updateblock = 0; //��� �ʱ�Ÿ�� ����
	int blocktype = *pblocktype;

	/*����Ű*/
	switch (kb)    //gw: switch-case������ �̿��Ͽ� (����,������,��,�Ʒ�,�����̽�) �ൿ����
	{
	case LEFT:        //gw: Ű���� ���� ���ʹ���Ű �϶�
		removeBlock(blocktype, -2, 0); //gw: ���(�ܻ�)�� ����� Ŀ���� x�� -2ĭ ������(�������� 2ĭ(="��"��ĭ)������)
		Showblock(blocktype);//gw: ����� ȭ�鿡 ���
		break;

	case RIGHT:      //gw: Ű���� ���� �����ʹ���Ű �϶�
		removeBlock(blocktype, 2, 0); //gw: ���(�ܻ�)�� ����� Ŀ���� x�� +2ĭ ������(���������� 2ĭ(="��"��ĭ)������)
		Showblock(blocktype);//gw: ����� ȭ�鿡 ���
		break;

	case UP:       //gw: Ű���� ���� ���� ����Ű �϶�

	   // ù�������Ѵ�.
	   //gw: nextblock�� ���� ���Ÿ���� �⺻Ÿ���� �����Ѵ�. ���� ��� ������� Ÿ���� ��,��,��,��  �� 4������ �ְ� k�� ���� �����ϰ� �ȴ�.(�ٸ� ��ϵ� ��������)
		updateblock = blocktype / 4;
		updateblock *= 4;

		// �������� ���������ΰ�? 
		if ((blocktype + 1) <= (updateblock + 3)) //gw: ������� �����Ÿ��(��,��,��,�� )�߿� k�� ��(������Ÿ��)�ϰ�� �����ϸ� �ٸ� ����� �ǹǷ� ������Ų��.
			updateblock = blocktype + 1;         //gw: ������ Ÿ���� �ƴҰ�� ���� Ÿ���� ���� Ÿ���� k�� �����Ѵ�.

		prove = IsCollision(updateblock, 0, 0); //gw: ����Ÿ�� ����� �ٸ� ����̳� ���� �浹�ϴ��� �˻�

		if (prove == 0)          //gw: ����Ÿ�� ����� �ٸ� ����̳� ���� �浿���� �ʴ´ٸ�
		{
			removeBlock(blocktype, 0, 0); //gw: ���(�ܻ�)�� ����� Ŀ���� ����         
			Showblock(updateblock);  //gw: ����� ȭ�鿡 ���
			*pblocktype = updateblock; //gw: ���Ÿ���� ���������� ��ü
			break;
		}
		break;

	case DOWN:      //gw: Ű���� ���� �Ʒ��� ����Ű �϶�
		removeBlock(blocktype, 0, 1);  //gw: ���(�ܻ�)�� ����� Ŀ���� y�� +2ĭ ������(�Ʒ������� 2ĭ(="��"��ĭ)������)
		Showblock(blocktype);
		break;

	case SPACE:     //gw: Ű���� ���� �����̽�Ű �϶�
		while (1)   //gw: ����� �浹�� �߻��Ҷ����� �ݺ�
		{
			removeBlock(blocktype, 0, 1);     //gw: ���(�ܻ�)�� ����� Ŀ���� y�� +1ĭ ������(�Ʒ������� 1ĭ(="��"��ĭ)������)
			if (IsCollision(blocktype, 0, 1) == 1) //gw: ���� �ٸ� ����̳� ���� �浹�Ѵٸ�
			{
				Showblock(blocktype);         //gw: ����� ȭ�鿡 ���
				UpdateBoardArr(blocktype); //gw: ����� ������Ŵ
				break;
			}
		}
	}
}
void moveBlock(int* speed, int* level, int* score)
{
	int blockType = 0; //��� ���
	int kb;// Ű���� �Է°�
	srand((unsigned int)time(NULL));
	int c = 2;
	/*���� ����~��*/
	while (!(GameWin(&*level) || GameOver(blockType)))
	{
		setCursor(CBLOCK_X, CBLOCK_Y); //��� ���� ��ġ ����
		blockType = rand() % 7;//��� ����� ���Ƿ� �����ϱ� ���� �����ϴ� �� 
		blockType = blockType * 4; //cjl:blockType�� 0~6 ������ 7���� ����, ������ 7��/ *4�� ����??

		Showblock(blockType);//������ ������ blockType�� ����� ������ �ǹ�(block[blockType][4][4])
		/*��� �Ѱ� ��~�� �̵�*/
		while (1)
		{
			int isBlockFixed = 0;//��� �浹 �߻� ���� �˸��� flag(������ 1)
			int k = 0;

			/*��� �ϳ��� �Ʒ��� �������� ����*/
			while (!_kbhit() && isBlockFixed == 0)//kbhit():Ű���尡 ���ȴ��� Ȯ��. �ȴ����� 0��ȯ
				isBlockFixed = BlockFalling(blockType, &*speed, &*level, &*score);

			//����� �ڸ���Ҵٸ� �� ����� ������ ������. while�� Ż���ؼ� �ٽ� ��� ��������
			if (isBlockFixed == 1)
				break;

			kb = _getch();//Ű���� �Է°� �޾ƿ� kb�� ����
			
						  /*����Ű*/
			updateBlock(kb, &blockType);
		}
	}
	setCursor(35, 20);
	printf("GAME OVER");
}
