
/*********************************
* 파일 이름 : player.h
* 기능 : player library
* last modified : 2019/02/23
* 수정자 : 박희완
**********************************/


#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "common.h"
#include "nation.h"

#define PLAYER_NAME_SIZE 20
#define PLAYER_POSSESSION_SIZE 30
typedef enum {	// player의 상태를 나타냄
	STAT_GAMING, STAT_FAIL, STAT_WINNER, STAT_DESERTISLAND, STAT_TRAVEL // 게임중(보통 상태), 파산, 이김, 무인도, 기차여행
}PLAYER_STATUS;

typedef struct _Player { // player 구조체
	char name[PLAYER_NAME_SIZE];				// player의 이름
	int money;									// player가 가지고 있는 money
	struct _nation * possession[PLAYER_POSSESSION_SIZE];	// player가 소유하고 있는 nation
	int turn;									// 해당 player의 turn인지 아닌지 판별. 1이면 해당 player의 turn
	int location;								// 보드 판 내 위치해 있는 장소
	PLAYER_STATUS status;						// 현재 player의 상태
	int travel;									// travel에 걸리면, 한턴 쉬고 나서, 다음 턴에 이동. 아직 수정 필요
	int break_turn;									// 이 수만큼 turn을 쉰다

		
	int num_of_possession;						// player가 소유하고 있는 nation의 수
}Player;

extern Player * makePlayer(char * name);
extern void playerInit(Player * p, char * name);
extern char * getPlayerName(Player *p);
extern int setPlayerName(Player *p, char *name);
extern int getPlayerMoney(Player *p);
extern int setPlayerMoney(Player *p, int money);
extern struct _nation * getPlayerPossession(Player *p, int num);
extern int addPlayerPossession(Player *p, struct _nation *n);
extern int deletePlayerPossession(Player *p, struct _nation *n);
extern int getPlayerTurn(Player *p);
extern int givePlayerTurn(Player *p);
extern int losePlayerTurn(Player *p);
extern int getPlayerLocation(Player *p);
extern int setPlayerLocation(Player *p, int l);
extern PLAYER_STATUS getPlayerStatus(Player *p);
extern int setPlayerStatus(Player *p, PLAYER_STATUS s);
extern int getPlayerNumOfPossession(Player *p);
extern int setPlayerNumOfPossession(Player *p, int num_of_possession);
extern int getPlayerBreakTurn(Player *p);
extern int setPlayerBreakTurn(Player *p, int break_turn);
extern void printPlayerPossession(Player *p);

#endif