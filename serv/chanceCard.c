/*********************************
* 파일 이름 : chanceCard.c
* 기능 : chance card 선언
* last modified : 2019/02/22
* 수정자 : 박희완
**********************************/

#include "chanceCard.h"
#include "common.h"


/*
* 함수 이름 : makeCC
* return : ChanceCard *
* 인자 : char *name
* 기능 : ChanceCard를 하나 생성해서 주소를 반환
* last modified : 2019/02/22
* 수정자 : 박희완
*/

ChanceCard * makeCC(char *name, char * explain, int card_num, int(*action)()) {
	ChanceCard * c = (ChanceCard *)malloc(sizeof(ChanceCard));
	CCInit(c, name, explain, card_num, action);
	return c;
}

/*
* 함수 이름 : CCInitialization
* return : void
* 인자 : ChanceCard *c, char * name, char * explain, int card_num, int (*action)()
* 기능 : Chance Card initialization
* last modified : 2019/02/22
* 수정자 : 박희완
*/

void CCInit(ChanceCard *c, char * name, char * explain, int card_num, int (*action)()) {
	// 수정 필요
	setCCName(c, name);
	setCCExplain(c, explain);
	setCCCardNum(c, card_num);
	setCCAction(c, action);
}

/*
* 함수 이름 : getCCName
* return : char *
* 인자 : ChanceCard *c
* 기능 : chance card의 name을 반환
* last modified : 2019/02/21
* 수정자 : 박희완
*/

char * getCCName(ChanceCard *c) {
	return c->name;
}

/*
* 함수 이름 : setCCName
* return : int 성공시 1, 실패시 0
* 인자 : ChanceCard *c, char *name
* 기능 : chance card의 name을 설정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int setCCName(ChanceCard *c, char *name) {
	if (strlen(name) > CHANCE_CARD_NAME_SIZE - 1) {
		return FALSE;
	}
	strcpy(c->name, name);
	return TRUE;
}

/*
* 함수 이름 : getCCExplain
* return : char *
* 인자 : ChanceCard *c
* 기능 : chance card의 explain을 반환
* last modified : 2019/02/22
* 수정자 : 박희완
*/

char * getCCExplain(ChanceCard *c) {
	return c->explain;
}

/*
* 함수 이름 : setCCExplain
* return : int 성공시 1, 실패시 0
* 인자 : ChanceCard *c, char *explain
* 기능 : chance card의 explain을 설정
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int setCCExplain(ChanceCard *c, char *explain) {
	if (strlen(explain) > CHANCE_CARD_NAME_SIZE - 1) {
		return FALSE;
	}
	strcpy(c->explain, explain);
	return TRUE;
}

/*
* 함수 이름 : getCCCardNum
* return : int
* 인자 : ChanceCard *c
* 기능 : chance card의 card_num을 반환
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int getCCCardNum(ChanceCard *c) {
	return c->card_num;
}

/*
* 함수 이름 : setCCCardNum
* return : int 성공시 1, 실패시 0
* 인자 : ChanceCard *c, int card_num
* 기능 : chance card의 card_num을 설정
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int setCCCardNum(ChanceCard *c, int card_num) {
	if (card_num < 0) {
		return FALSE;
	}
	c->card_num = card_num;
	return TRUE;
}

/*
* 함수 이름 : getCCAction
* return : int (*)()
* 인자 : ChanceCard *c
* 기능 : chance card의 action 함수를 반환
* last modified : 2019/02/22
* 수정자 : 박희완
*/

extern int(*getCCAction(ChanceCard *c))() {
	return c->action;
}

/*
* 함수 이름 : setCCAction
* return : int 성공시 1, 실패시 0
* 인자 : ChanceCard *c, int(*action) ()
* 기능 : chance card의 action 함수를 설정
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int setCCAction(ChanceCard *c, int(*action) ()) {
	c->action = action;
	return TRUE;
}


/*
* 함수 이름 : do_action
* return : int 성공시 1, 실패시 0
* 인자 : ChanceCard *c, int action_num, void *p1(함수에 필요한 parameter), void *p2(함수에 필요한 parameter)
* 기능 : chance card의 해당 action number에 해당하는 action 함수 실행
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int do_action(ChanceCard *c, void *p1, void *p2) {
	return c->action(p1, p2);
}