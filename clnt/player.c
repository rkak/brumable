/*********************************
* ���� �̸� : player.c
* ��� : player ����
* last modified : 2019/02/25
* ������ : �����
**********************************/

#include "nation.h"
#include "player.h"
#include "controller.h"

extern int info_print_cursor_x;
extern int info_print_cursor_y;

#define PLAYER_MONEY_INIT 50

/*
* �Լ� �̸� : makePlayer
* return : Player * ������ ������� player�� �ּ� ��ȯ, ���н� NULL
* ���� : char * name(player�� �̸�)
* ��� : memory�� player ������ �ϳ� �����
* last modified : 2019/02/21
* ������ : �����
*/

Player * makePlayer(char * name) {
	Player * t = (Player *)malloc(sizeof(Player));
	if (t == NULL)
		return NULL;
	playerInit(t, name);
	return t;
}

/*
* �Լ� �̸� : playerInit
* return : void 
* ���� : Player *p, char *name
* ��� : player initialization
* last modified : 2019/02/23
* ������ : �����
*/

void playerInit(Player * p, char * name) {
	p->location = 0;
	p->money = PLAYER_MONEY_INIT;
	strcpy(p->name, name);
	p->possession;
	p->status = STAT_GAMING;
	p->turn = FALSE;	// TRUE �� �� ������ turn.
	p->num_of_possession = 0;
	p->travel = 0;
}

/*
* �Լ� �̸� : getPlayerName
* return : char *
* ���� : Player *p
* ��� : player�� �̸��� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

char * getPlayerName(Player *p) {
	return p->name;
}

/*
* �Լ� �̸� : setPlayerName
* return : int, ������ 1, ���н� 0
* ���� : Player *p, char *name
* ��� : player�� �̸��� ����
* last modified : 2019/02/21
* ������ : �����
*/

int setPlayerName(Player *p, char *name) {
	if (strlen(name) > PLAYER_NAME_SIZE - 1) {
		return FALSE;
	}
	strcpy(p->name, name);
	return TRUE;
}

/*
* �Լ� �̸� : getPlayerMoney
* return : int
* ���� : Player *p
* ��� : player�� money�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

int getPlayerMoney(Player *p) {
	return p->money;
}

/*
* �Լ� �̸� : setPlayerMoney
* return : int
* ���� : Player *p, int money
* ��� : player �� money�� ����
* last modified : 2019/02/21
* ������ : �����
*/

int setPlayerMoney(Player *p, int money) {
	if (money > _CRT_INT_MAX || money < 0)
		return FALSE;
	p->money = money;
	return TRUE;
}

/*
* �Լ� �̸� : getPlayerPossession
* return : Nation *
* ���� : Player *p, int num
* ��� : player �� Nation �迭�� �ּҸ� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/


Nation * getPlayerPossession(Player *p, int num) {		// num : ��ȯ�ϰ��� �ϴ� possession�� index��
	return p->possession[num];
}

/*
* �Լ� �̸� : addPlayerPossession
* return : int
* ���� : Player *p. struct _nation *n
* ��� : player �� Nation�� �߰�
* last modified : 2019/02/21
* ������ : �����
*/

int addPlayerPossession(Player *p, struct _nation *n) {
	int player_num_possession = getPlayerNumOfPossession(p);
	if (p->num_of_possession > PLAYER_POSSESSION_SIZE - 1)
		return FALSE;
	p->possession[player_num_possession++] = n;
	setPlayerNumOfPossession(p, player_num_possession);
	return TRUE;
}

/*
* �Լ� �̸� : deletePlayerPossession
* return : int
* ���� : Player *p. struct _nation *n
* ��� : player �� Nation�� ����
* last modified : 2019/02/22
* ������ : �����
*/

int deletePlayerPossession(Player *p, struct _nation *n){
	int num = getPlayerNumOfPossession(p);
	if (num <= 0)
		return FALSE;

	int deleteIndex;
	// �ش��ϴ� n�� ����
	for (int i = 0; i < num; i++) {
		if (!strcmp(p->possession[i]->name, n->name)) {
			deleteIndex = i;
			break;
		}
	}
	
	// deleteIndex�� �� ���� ��츦 �����ϸ�
	if (deleteIndex != num) {
		for (int i = deleteIndex; i < num - 1; i++) {
			p->possession[i] = p->possession[i + 1];
		}
	}

	p->num_of_possession = --num;
	return TRUE;
}

/*
* �Լ� �̸� : getPlayerTurn
* return : int
* ���� : Player *p
* ��� : player�� turn�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

int getPlayerTurn(Player *p) {
	return p->turn;
}

/*
* �Լ� �̸� : givePlayerTurn
* return : int ������ 1, ���н� 0
* ���� : Player *p
* ��� : player�� turn�� 1�� ����
* last modified : 2019/02/21
* ������ : �����
*/

int givePlayerTurn(Player *p) {
	return (p->turn = TRUE);
}

/*
* �Լ� �̸� : losePlayerTurn
* return : int ������ 1, ���н� 0
* ���� : Player *p
* ��� : player�� turn�� 0���� ����
* last modified : 2019/02/21
* ������ : �����
*/

int losePlayerTurn(Player *p) {
	return (p->turn = FALSE);
}

/*
* �Լ� �̸� : getPlayerLocation
* return : int
* ���� : Player *p
* ��� : player�� location�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

int getPlayerLocation(Player *p) {
	return p->location;
}

/*
* �Լ� �̸� : setPlayerLocation
* return : int
* ���� : Player *p, int l
* ��� : player�� location�� ����
* last modified : 2019/02/21
* ������ : �����
*/

int setPlayerLocation(Player *p, int l) {
	p->location = l;
	return TRUE;
}

/*
* �Լ� �̸� : getPlayerStatus
* return : PLAYER_STATUS
* ���� : Player *p
* ��� : player�� status�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/


PLAYER_STATUS getPlayerStatus(Player *p) {
	return p->status;
}

/*
* �Լ� �̸� : setPlayerStatus
* return : int ������ 1, ���н� 0
* ���� : Player *p, PLAYER_STATUS s
* ��� : player�� status�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

int setPlayerStatus(Player *p, PLAYER_STATUS s) {
	return (p->status = s);
}

/*
* �Լ� �̸� : getPlayerNumOfPossession
* return : int
* ���� : Player *p
* ��� : player�� possession�� ���� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

int getPlayerNumOfPossession(Player *p) {
	return p->num_of_possession;
}

/*
* �Լ� �̸� : setPlayerNumOfPossession
* return : int
* ���� : Player *p, int num_of_possession
* ��� : player�� possession�� ���� set
* last modified : 2019/02/23
* ������ : �����
*/

int setPlayerNumOfPossession(Player *p, int num_of_possession) {
	return p->num_of_possession = num_of_possession;
}



/*
* �Լ� �̸� : getPlayerBreakTurn
* return : int
* ���� : Player *p
* ��� : player�� break turn�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

int getPlayerBreakTurn(Player *p) {
	return p->break_turn;
}

/*
* �Լ� �̸� : setPlayerBreakTurn
* return : int ������ 1, ���н� 0
* ���� : Player *p, int break_turn
* ��� : player�� break_turn�� ����
* last modified : 2019/02/21
* ������ : �����
*/

int setPlayerBreakTurn(Player *p, int break_turn) {
	return (p->break_turn = break_turn);
}

/*
* �Լ� �̸� : printPlayerPossession
* return : void
* ���� : Player *p
* ��� : player�� possession�� ��� ���
* last modified : 2019/02/25
* ������ : �����
*/

void printPlayerPossession(Player *p) {
	SetInfoCursor();
	printf("�̸�\t\t����\n");
	for (int i = 0; i < p->num_of_possession; i++) {
		SetInfoCursor();
		printf("%s\t", getNationName(p->possession[i]));
		// ������ print���־�� �Ѵ�
		SetInfoCursor();
		printf("%d\n", getNationPrice(p->possession[i]));
		SetInfoCursor();
		printf("%d\n", getNumofBuilding(p->possession[i]));
	}
}