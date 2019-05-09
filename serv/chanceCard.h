/*********************************
* 파일 이름 : chanceCard.h
* 기능 : chance card library
* last modified : 2019/02/21
* 수정자 : 박희완
**********************************/

#pragma once
#ifndef __CHANCECARD_H__
#define __CHANCECARD_H__

#define CHANCE_CARD_NUM 3
#define CHANCE_CARD_NAME_SIZE 20
#define CHANCE_CARD_EXPLAIN_SIZE 100
//#define CHANCE_CARD_ACTION_SIZE 20

typedef struct _chanceCard {
	char name[CHANCE_CARD_NAME_SIZE];
	int card_num;
	int (*action)(void *);
	char explain[CHANCE_CARD_EXPLAIN_SIZE];
}ChanceCard;

extern ChanceCard * makeCC(char *name, char * explain, int card_num, int(*action)());
extern void CCInit(ChanceCard *c, char * name, char * explain, int card_num, int(*action)());

extern char * getCCName(ChanceCard *c);
extern int setCCName(ChanceCard *c, char *name);
extern char * getCCExplain(ChanceCard *c);
extern int setCCExplain(ChanceCard *c, char *explain);
extern int getCCCardNum(ChanceCard *c);
extern int setCCCardNum(ChanceCard *c, int card_num);
extern int (* getCCAction(ChanceCard *c))();
extern int setCCAction(ChanceCard *c, int(*action) ());

extern int do_action(ChanceCard *c, void *p1, void *p2);

#endif