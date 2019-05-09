/*********************************
* 파일 이름 : player.c
* 기능 : player 선언
* last modified : 2019/02/25
* 수정자 : 박희완
**********************************/

#include "nation.h"
#include "player.h"
#include "controller.h"

extern int info_print_cursor_x;
extern int info_print_cursor_y;

#define PLAYER_MONEY_INIT 50

/*
* 함수 이름 : makePlayer
* return : Player * 성공시 만들어진 player의 주소 반환, 실패시 NULL
* 인자 : char * name(player의 이름)
* 기능 : memory에 player 공간을 하나 만든다
* last modified : 2019/02/21
* 수정자 : 박희완
*/

Player * makePlayer(char * name) {
	Player * t = (Player *)malloc(sizeof(Player));
	if (t == NULL)
		return NULL;
	playerInit(t, name);
	return t;
}

/*
* 함수 이름 : playerInit
* return : void 
* 인자 : Player *p, char *name
* 기능 : player initialization
* last modified : 2019/02/23
* 수정자 : 박희완
*/

void playerInit(Player * p, char * name) {
	p->location = 0;
	p->money = PLAYER_MONEY_INIT;
	strcpy(p->name, name);
	p->possession;
	p->status = STAT_GAMING;
	p->turn = FALSE;	// TRUE 일 때 본인의 turn.
	p->num_of_possession = 0;
	p->travel = 0;
}

/*
* 함수 이름 : getPlayerName
* return : char *
* 인자 : Player *p
* 기능 : player의 이름을 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

char * getPlayerName(Player *p) {
	return p->name;
}

/*
* 함수 이름 : setPlayerName
* return : int, 성공시 1, 실패시 0
* 인자 : Player *p, char *name
* 기능 : player의 이름을 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int setPlayerName(Player *p, char *name) {
	if (strlen(name) > PLAYER_NAME_SIZE - 1) {
		return FALSE;
	}
	strcpy(p->name, name);
	return TRUE;
}

/*
* 함수 이름 : getPlayerMoney
* return : int
* 인자 : Player *p
* 기능 : player의 money을 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int getPlayerMoney(Player *p) {
	return p->money;
}

/*
* 함수 이름 : setPlayerMoney
* return : int
* 인자 : Player *p, int money
* 기능 : player 의 money를 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int setPlayerMoney(Player *p, int money) {
	if (money > _CRT_INT_MAX || money < 0)
		return FALSE;
	p->money = money;
	return TRUE;
}

/*
* 함수 이름 : getPlayerPossession
* return : Nation *
* 인자 : Player *p, int num
* 기능 : player 의 Nation 배열의 주소를 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/


Nation * getPlayerPossession(Player *p, int num) {		// num : 반환하고자 하는 possession의 index값
	return p->possession[num];
}

/*
* 함수 이름 : addPlayerPossession
* return : int
* 인자 : Player *p. struct _nation *n
* 기능 : player 에 Nation을 추가
* last modified : 2019/02/21
* 수정자 : 박희완
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
* 함수 이름 : deletePlayerPossession
* return : int
* 인자 : Player *p. struct _nation *n
* 기능 : player 에 Nation을 삭제
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int deletePlayerPossession(Player *p, struct _nation *n){
	int num = getPlayerNumOfPossession(p);
	if (num <= 0)
		return FALSE;

	int deleteIndex;
	// 해당하는 n이 삭제
	for (int i = 0; i < num; i++) {
		if (!strcmp(p->possession[i]->name, n->name)) {
			deleteIndex = i;
			break;
		}
	}
	
	// deleteIndex가 맨 끝인 경우를 제외하면
	if (deleteIndex != num) {
		for (int i = deleteIndex; i < num - 1; i++) {
			p->possession[i] = p->possession[i + 1];
		}
	}

	p->num_of_possession = --num;
	return TRUE;
}

/*
* 함수 이름 : getPlayerTurn
* return : int
* 인자 : Player *p
* 기능 : player의 turn을 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int getPlayerTurn(Player *p) {
	return p->turn;
}

/*
* 함수 이름 : givePlayerTurn
* return : int 성공시 1, 실패시 0
* 인자 : Player *p
* 기능 : player의 turn을 1로 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int givePlayerTurn(Player *p) {
	return (p->turn = TRUE);
}

/*
* 함수 이름 : losePlayerTurn
* return : int 성공시 1, 실패시 0
* 인자 : Player *p
* 기능 : player의 turn을 0으로 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int losePlayerTurn(Player *p) {
	return (p->turn = FALSE);
}

/*
* 함수 이름 : getPlayerLocation
* return : int
* 인자 : Player *p
* 기능 : player의 location을 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int getPlayerLocation(Player *p) {
	return p->location;
}

/*
* 함수 이름 : setPlayerLocation
* return : int
* 인자 : Player *p, int l
* 기능 : player의 location을 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int setPlayerLocation(Player *p, int l) {
	p->location = l;
	return TRUE;
}

/*
* 함수 이름 : getPlayerStatus
* return : PLAYER_STATUS
* 인자 : Player *p
* 기능 : player의 status를 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/


PLAYER_STATUS getPlayerStatus(Player *p) {
	return p->status;
}

/*
* 함수 이름 : setPlayerStatus
* return : int 성공시 1, 실패시 0
* 인자 : Player *p, PLAYER_STATUS s
* 기능 : player의 status를 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int setPlayerStatus(Player *p, PLAYER_STATUS s) {
	return (p->status = s);
}

/*
* 함수 이름 : getPlayerNumOfPossession
* return : int
* 인자 : Player *p
* 기능 : player의 possession의 수를 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int getPlayerNumOfPossession(Player *p) {
	return p->num_of_possession;
}

/*
* 함수 이름 : setPlayerNumOfPossession
* return : int
* 인자 : Player *p, int num_of_possession
* 기능 : player의 possession의 수를 set
* last modified : 2019/02/23
* 수정자 : 박희완
*/

int setPlayerNumOfPossession(Player *p, int num_of_possession) {
	return p->num_of_possession = num_of_possession;
}



/*
* 함수 이름 : getPlayerBreakTurn
* return : int
* 인자 : Player *p
* 기능 : player의 break turn을 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int getPlayerBreakTurn(Player *p) {
	return p->break_turn;
}

/*
* 함수 이름 : setPlayerBreakTurn
* return : int 성공시 1, 실패시 0
* 인자 : Player *p, int break_turn
* 기능 : player의 break_turn을 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int setPlayerBreakTurn(Player *p, int break_turn) {
	return (p->break_turn = break_turn);
}

/*
* 함수 이름 : printPlayerPossession
* return : void
* 인자 : Player *p
* 기능 : player의 possession을 모두 출력
* last modified : 2019/02/25
* 수정자 : 박희완
*/

void printPlayerPossession(Player *p) {
	SetInfoCursor();
	printf("이름\t\t가격\n");
	for (int i = 0; i < p->num_of_possession; i++) {
		SetInfoCursor();
		printf("%s\t", getNationName(p->possession[i]));
		// 가격을 print해주어야 한다
		SetInfoCursor();
		printf("%d\n", getNationPrice(p->possession[i]));
		SetInfoCursor();
		printf("%d\n", getNumofBuilding(p->possession[i]));
	}
}