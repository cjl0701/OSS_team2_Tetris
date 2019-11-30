#pragma once
#ifndef __MOVEBLOCK_H__ 
#define __MOVEBLOCK_H__
#include "Header.h"
#include "Show.h"
#include "GameStatus.h"
#include "GameProgress.h"

int BlockFalling(int blockType, int* speed, int* level, int* score);
void updateBlock(int kb, int* pblocktype);
void moveBlock(int* speed, int* level, int* score);

#endif 


