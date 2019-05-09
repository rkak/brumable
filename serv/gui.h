
/*********************************
* 파일 이름 : gui.h
* 기능 : 부루마블의 모든 gui 함수 library
* last modified : 2019/02/22
* 수정자 : 구종석
**********************************/


#pragma once

#ifndef __GUI_H__
#define __GUI_H__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include<conio.h>
#include "nation.h"

#pragma warning(disable:4996)

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute( col,0x000c ) //빨간색 
#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008) //파란색 
#define HIGH SetConsoleTextAttribute( col,0x00a) // 연두
#define WHITE SetConsoleTextAttribute( col,0x000f) // 흰색
#define SKY SetConsoleTextAttribute( col, 0x000b) //하늘색
#define YELLOW SetConsoleTextAttribute( col, 0x000e) //노란색
#define HIG SetConsoleTextAttribute( col, 0x000d) //형광
#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c) //보라

//콘솔화면 좌표를 위한 구조체
typedef struct put {
	int x;
	int y;
}pointer;

void removeCursor(void);
extern void viewCursor(void);
void setCursor(int x, int y);

//로딩화면(초기처음화면/ controller.c의 bitmable 함수에 넣음)
extern void gui_loading_display();
//메뉴 선택 게임 시작할지 종료할지(controller.c의 bitmable 함수에 넣음)
extern int gui_menu_choice();
//비트마블 맵 그리는 함수(controller.c 의 mableInit에 넣음)
extern void gui_map_Init(Nation **city);
//비트마블의 주사위 gui 함수
extern void gui_dice(int n1, int n2);
//비트마블의 미니게임(복불복) gui 함수
extern void gui_bokbulbok(int com, int user);

#endif
