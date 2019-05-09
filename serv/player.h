
/*********************************
* ���� �̸� : player.h
* ��� : player library
* last modified : 2019/02/23
* ������ : �����
**********************************/


#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "common.h"
#include "nation.h"

#define PLAYER_NAME_SIZE 20
#define PLAYER_POSSESSION_SIZE 30
typedef enum {	// player�� ���¸� ��Ÿ��
	STAT_GAMING, STAT_FAIL, STAT_WINNER, STAT_DESERTISLAND, STAT_TRAVEL // ������(���� ����), �Ļ�, �̱�, ���ε�, ��������
}PLAYER_STATUS;

typedef struct _Player { // player ����ü
	char name[PLAYER_NAME_SIZE];				// player�� �̸�
	int money;									// player�� ������ �ִ� money
	struct _nation * possession[PLAYER_POSSESSION_SIZE];	// player�� �����ϰ� �ִ� nation
	int turn;									// �ش� player�� turn���� �ƴ��� �Ǻ�. 1�̸� �ش� player�� turn
	int location;								// ���� �� �� ��ġ�� �ִ� ���
	PLAYER_STATUS status;						// ���� player�� ����
	int travel;									// travel�� �ɸ���, ���� ���� ����, ���� �Ͽ� �̵�. ���� ���� �ʿ�
	int break_turn;									// �� ����ŭ turn�� ����

		
	int num_of_possession;						// player�� �����ϰ� �ִ� nation�� ��
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