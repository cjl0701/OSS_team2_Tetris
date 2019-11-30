#pragma once
#ifndef __PROGRESS_H__
#define __PROGRESS_H__

#include "Cursor.h"

int IsCollision(int blockType, int moveX, int moveY);
void TransPos(int* arrX, int* arrY);
void removeBlock(int rotation, int move1, int move2);
void UpdateBoardArr(int blockType);
void BoardArrDown(int column);
void ClearLine(int line);
void UpdateLine(int line);
void CheckLine(int* speed, int* level, int* score);

#endif 
