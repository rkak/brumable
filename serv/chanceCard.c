/*********************************
* ���� �̸� : chanceCard.c
* ��� : chance card ����
* last modified : 2019/02/22
* ������ : �����
**********************************/

#include "chanceCard.h"
#include "common.h"


/*
* �Լ� �̸� : makeCC
* return : ChanceCard *
* ���� : char *name
* ��� : ChanceCard�� �ϳ� �����ؼ� �ּҸ� ��ȯ
* last modified : 2019/02/22
* ������ : �����
*/

ChanceCard * makeCC(char *name, char * explain, int card_num, int(*action)()) {
	ChanceCard * c = (ChanceCard *)malloc(sizeof(ChanceCard));
	CCInit(c, name, explain, card_num, action);
	return c;
}

/*
* �Լ� �̸� : CCInitialization
* return : void
* ���� : ChanceCard *c, char * name, char * explain, int card_num, int (*action)()
* ��� : Chance Card initialization
* last modified : 2019/02/22
* ������ : �����
*/

void CCInit(ChanceCard *c, char * name, char * explain, int card_num, int (*action)()) {
	// ���� �ʿ�
	setCCName(c, name);
	setCCExplain(c, explain);
	setCCCardNum(c, card_num);
	setCCAction(c, action);
}

/*
* �Լ� �̸� : getCCName
* return : char *
* ���� : ChanceCard *c
* ��� : chance card�� name�� ��ȯ
* last modified : 2019/02/21
* ������ : �����
*/

char * getCCName(ChanceCard *c) {
	return c->name;
}

/*
* �Լ� �̸� : setCCName
* return : int ������ 1, ���н� 0
* ���� : ChanceCard *c, char *name
* ��� : chance card�� name�� ����
* last modified : 2019/02/21
* ������ : �����
*/

int setCCName(ChanceCard *c, char *name) {
	if (strlen(name) > CHANCE_CARD_NAME_SIZE - 1) {
		return FALSE;
	}
	strcpy(c->name, name);
	return TRUE;
}

/*
* �Լ� �̸� : getCCExplain
* return : char *
* ���� : ChanceCard *c
* ��� : chance card�� explain�� ��ȯ
* last modified : 2019/02/22
* ������ : �����
*/

char * getCCExplain(ChanceCard *c) {
	return c->explain;
}

/*
* �Լ� �̸� : setCCExplain
* return : int ������ 1, ���н� 0
* ���� : ChanceCard *c, char *explain
* ��� : chance card�� explain�� ����
* last modified : 2019/02/22
* ������ : �����
*/

int setCCExplain(ChanceCard *c, char *explain) {
	if (strlen(explain) > CHANCE_CARD_NAME_SIZE - 1) {
		return FALSE;
	}
	strcpy(c->explain, explain);
	return TRUE;
}

/*
* �Լ� �̸� : getCCCardNum
* return : int
* ���� : ChanceCard *c
* ��� : chance card�� card_num�� ��ȯ
* last modified : 2019/02/22
* ������ : �����
*/

int getCCCardNum(ChanceCard *c) {
	return c->card_num;
}

/*
* �Լ� �̸� : setCCCardNum
* return : int ������ 1, ���н� 0
* ���� : ChanceCard *c, int card_num
* ��� : chance card�� card_num�� ����
* last modified : 2019/02/22
* ������ : �����
*/

int setCCCardNum(ChanceCard *c, int card_num) {
	if (card_num < 0) {
		return FALSE;
	}
	c->card_num = card_num;
	return TRUE;
}

/*
* �Լ� �̸� : getCCAction
* return : int (*)()
* ���� : ChanceCard *c
* ��� : chance card�� action �Լ��� ��ȯ
* last modified : 2019/02/22
* ������ : �����
*/

extern int(*getCCAction(ChanceCard *c))() {
	return c->action;
}

/*
* �Լ� �̸� : setCCAction
* return : int ������ 1, ���н� 0
* ���� : ChanceCard *c, int(*action) ()
* ��� : chance card�� action �Լ��� ����
* last modified : 2019/02/22
* ������ : �����
*/

int setCCAction(ChanceCard *c, int(*action) ()) {
	c->action = action;
	return TRUE;
}


/*
* �Լ� �̸� : do_action
* return : int ������ 1, ���н� 0
* ���� : ChanceCard *c, int action_num, void *p1(�Լ��� �ʿ��� parameter), void *p2(�Լ��� �ʿ��� parameter)
* ��� : chance card�� �ش� action number�� �ش��ϴ� action �Լ� ����
* last modified : 2019/02/21
* ������ : �����
*/

int do_action(ChanceCard *c, void *p1, void *p2) {
	return c->action(p1, p2);
}