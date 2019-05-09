
/*********************************
* ���� �̸� : gui.h
* ��� : �η縶���� ��� gui �Լ� library
* last modified : 2019/02/22
* ������ : ������
**********************************/


#pragma once

#ifndef __GUI_H__
#define __GUI_H__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include<conio.h>
#include "nation.h"

#pragma warning(disable:4996)

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute( col,0x000c ) //������ 
#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008) //�Ķ��� 
#define HIGH SetConsoleTextAttribute( col,0x00a) // ����
#define WHITE SetConsoleTextAttribute( col,0x000f) // ���
#define SKY SetConsoleTextAttribute( col, 0x000b) //�ϴû�
#define YELLOW SetConsoleTextAttribute( col, 0x000e) //�����
#define HIG SetConsoleTextAttribute( col, 0x000d) //����
#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c) //����

//�ܼ�ȭ�� ��ǥ�� ���� ����ü
typedef struct put {
	int x;
	int y;
}pointer;

void removeCursor(void);
extern void viewCursor(void);
void setCursor(int x, int y);

//�ε�ȭ��(�ʱ�ó��ȭ��/ controller.c�� bitmable �Լ��� ����)
extern void gui_loading_display();
//�޴� ���� ���� �������� ��������(controller.c�� bitmable �Լ��� ����)
extern int gui_menu_choice();
//��Ʈ���� �� �׸��� �Լ�(controller.c �� mableInit�� ����)
extern void gui_map_Init(Nation **city);
//��Ʈ������ �ֻ��� gui �Լ�
extern void gui_dice(int n1, int n2);
//��Ʈ������ �̴ϰ���(���Һ�) gui �Լ�
extern void gui_bokbulbok(int com, int user);

#endif
