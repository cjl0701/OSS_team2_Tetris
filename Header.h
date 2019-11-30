#pragma once
#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define BOARD_HEIGHT 20 // ������
#define BOARD_WIDTH 10  // ������
#define BOARD_X 4 //���� �� x��ǥ
#define BOARD_Y 2 //���� �� y��ǥ
#define CBLOCK_X 13 //cjl:���� ������..
#define CBLOCK_Y 2
#define DELAY 100//����
#define RAND 4//����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

extern int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2];
//2���� �迭�� ��Ʈ���� ����� ����
extern int block[][4][4];

#endif 
