/*********************************
* 파일 이름 : chanceCard_action_controller.c
* 기능 : chanceCard controller 선언. action에 대한 controller
* last modified : 2019/02/22
* 수정자 : 박희완
**********************************/

#include "chanceCard_action_controller.h"
#include "player.h"

/*
* 함수 이름 : moveToIsland
* return : int
* 인자 : void *p
* 기능 : p를 Player로 typecasting 후 무인도로 보낸다
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int moveToIsland(void * p) {
	p = (Player *)p;
	return movePlayerByName("Desert Island");
}

/*
* 함수 이름 : moveToTrain
* return : int
* 인자 : void *p
* 기능 : p를 Player로 typecasting 후 기차 여행으로 보낸다
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int moveToTrain(void * p) {
	p = (Player *)p;

	return movePlayerByName("Desert Island");
}

/*
* 함수 이름 : moveToStart
* return : int
* 인자 : void *p
* 기능 : p를 Player로 typecasting 후 start 지점으로 보낸다
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int moveToStart(void * p) {
	p = (Player *)p;
	return movePlayerByName("Start");
}

