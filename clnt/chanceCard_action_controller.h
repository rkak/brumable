/*********************************
* 파일 이름 : chanceCard_action_controller.h
* 기능 : chanceCard action controller library
* last modified : 2019/02/21
* 수정자 : 박희완
**********************************/


#pragma once
#ifndef __CHANCECARD_ACTION_CONTROLLER_H__
#define __CHANCECARD_ACTION_CONTROLLER_H__

#include "controller.h"


// 일단 세개
// 하나는 무인도로
// 하나는 기차여행으로
// 하나는 start 지점으로

extern int moveToIsland(void * p);
extern int moveToTrain(void * p);
extern int moveToStart(void * p);

#endif		