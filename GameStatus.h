#pragma once
#ifndef __GAMESTATUS_H__
#define __GAMESTATUS_H__

#include "Header.h"

int GameOver(int rotation);
int GameWin(int* level);
void CountScore(int* speed, int* level, int* score);

#endif