
/*********************************
* 파일 이름 : building.h
* 기능 : building library
* last modified : 2019/02/23
* 수정자 : 박희완
**********************************/


#pragma once
#ifndef __BUILDING_H__
#define __BUILDING_H__
#include "common.h"


typedef struct _building {
	char name[10];
	int price;
} Building;

extern char* getBuildingName(Building* b);
extern void setBuildingName(Building* b);
extern int getBuildingPrice(Building* b);
extern void setBuildingPrice(Building* b, int price);
void makeBuilding(Building *b, int price);
void buildingInit(Building* b, int price);
// void buildingClear(Building *b);	// memory allocation을 하지 않았기에 굳이 만들지 x
#endif