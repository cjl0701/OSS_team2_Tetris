#pragma once
#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define BOARD_HEIGHT 20 // ┃개수
#define BOARD_WIDTH 10  // ━개수
#define BOARD_X 4 //보드 열 x좌표
#define BOARD_Y 2 //보드 행 y좌표
#define CBLOCK_X 13 //cjl:무슨 변수냐..
#define CBLOCK_Y 2
#define DELAY 100//지연
#define RAND 4//난수
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

extern int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2];
//2차원 배열로 테트리스 블록을 구현
extern int block[][4][4];

#endif 
