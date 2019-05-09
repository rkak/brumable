/*********************************
* 파일 이름 : action_controller.h
* 기능 : action_controller library
* last modified : 2019/02/23
* 수정자 : 박희완
**********************************/


#pragma once
#ifndef __ACTION_CONTROLLER_H__
#define __ACTION_CONTROLLER_H__

#include "controller.h"



extern void action();
extern int doGiveFund(Player * p);
extern int doCity(Player *p, Nation * t);
extern int giveFine(Player * p, Player * target, int fine);
extern int doChanceCard(Player *p);
extern int doDesertIsland(Player *p);
extern int doTravel(Player *p);
extern int doReceiveFund(Player *p);
extern int sellPossess(Player *p);

#endif