/*********************************
* ���� �̸� : chanceCard_action_controller.c
* ��� : chanceCard controller ����. action�� ���� controller
* last modified : 2019/02/22
* ������ : �����
**********************************/

#include "chanceCard_action_controller.h"
#include "player.h"

/*
* �Լ� �̸� : moveToIsland
* return : int
* ���� : void *p
* ��� : p�� Player�� typecasting �� ���ε��� ������
* last modified : 2019/02/22
* ������ : �����
*/

int moveToIsland(void * p) {
	p = (Player *)p;
	return movePlayerByName("Desert Island");
}

/*
* �Լ� �̸� : moveToTrain
* return : int
* ���� : void *p
* ��� : p�� Player�� typecasting �� ���� �������� ������
* last modified : 2019/02/22
* ������ : �����
*/

int moveToTrain(void * p) {
	p = (Player *)p;

	return movePlayerByName("Desert Island");
}

/*
* �Լ� �̸� : moveToStart
* return : int
* ���� : void *p
* ��� : p�� Player�� typecasting �� start �������� ������
* last modified : 2019/02/22
* ������ : �����
*/

int moveToStart(void * p) {
	p = (Player *)p;
	return movePlayerByName("Start");
}

