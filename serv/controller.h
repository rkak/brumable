/*********************************
* 파일 이름 : controller.h
* 기능 : controller library
* last modified : 2019/02/23
* 수정자 : 박희완
**********************************/

#pragma once
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "player.h"
#include "nation.h"
#include "building.h"
#include "bank.h"
#include "chanceCard.h"

#define DICE_COUNT 6
#define DICE_NUM 2

#define SetInfoCursor() setCursor(info_print_cursor_x, info_print_cursor_y++)

void mableInitForNet(void);
void makePlayerForNet(void);
extern void bitmable(void);
extern void mableInit(void);
extern int setPlayerNum(void);
extern void makePlayers(void);
extern void makeCCs(void);
extern void makeNations(void);
extern void makeBanks(void);
extern int turnInit(void);
extern int chooseTurn(void);
extern int checkPlayer(void);
extern int throwDice(int twice);
extern int movePlayer(int move_location);
extern int movePlayerByName(char * name);

#endif