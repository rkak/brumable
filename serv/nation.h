
/*********************************
* ���� �̸� : nation.h
* ��� : nation library
* last modified : 2019/02/23
* ������ : �����
**********************************/


#pragma once
#ifndef __NATION_H__
#define __NATION_H__
#include "common.h"
#include "building.h"
#include "player.h"
#define NATION_NAME 20
#define BUILDINGCOUNT 3
#define CITY_COUNT 28

//�� ������ ���뵵�� ��Ÿ��
typedef enum {
	KIND_CITY, KIND_FUND, // ����, �ݵ�
	KIND_CHANCECARD, KIND_DESERTISLNAD, //����ī�� ,���ε�,
	KIND_TRAVEL, KIND_FUND_RECEIVE,		//��������, ���ȯ��ó
	KIND_START
}Nation_Staus;

typedef struct _nation {
	int x;
	int y;
	char name[NATION_NAME];  //�ش� �����̸�
	int price;				//����
	int location_num;
	struct _player * owner;			// ����
	Building buildings[BUILDINGCOUNT]; //���� 
	int numOfBuilding;		// ���� ����
	Nation_Staus status; //������ �뵵
}Nation;


extern void nationInit(Nation * nation, char* name, int price, Nation_Staus status, int location_num);
extern Nation * makeNation(char* name, int price, Nation_Staus status, int location_num);

extern char* getNationName(Nation* nation);
extern void setNationName(Nation* nation, char* name);

extern int getNationPrice(Nation* nation);
extern void setNationPrice(Nation* nation, int price);
extern void stackNationPrice(Nation* nation, int s_price);

extern int getNationStatus(Nation* nation);
extern void setNationStatus(Nation* nation, Nation_Staus status);

extern struct _player* getNationOwner(Nation* nation);
extern void setNationOwner(Nation* nation, struct _player* player);



extern int getNationLocationNum(Nation *nation);
extern void setNationLocationNum(Nation *nation, int location_num);

extern int getNumofBuilding(Nation* nation);
extern void setNumofBuilding(Nation* nation, int num);
extern int checkNumofBuilding(Nation* nation);

extern Nation* findLocationByNum(Nation ** city, int cur_location);
extern Nation* findLocation(Nation ** city, char * name);

extern int addNationBuilding(Nation * nation, Building building);
extern void nationBuildingClear(Nation* nation);

// ���� ���������� 
extern struct _player* whoPossess(Nation ** city, int cur_location);

extern int delNationOwner(Nation* nation);




#endif