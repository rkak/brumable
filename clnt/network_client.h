#pragma once
#ifndef __NETWORK_CLNT_H__
#define __NETWORK_CLNT_H__

#include <Windows.h>
#include "player.h"

#define TYPE_INS	0
#define TYPE_PLAYER	1
#define TYPE_BANK	2
#define TYPE_CC		3

SOCKET initClntNet(void);
void doServ(void);
void quitNet(void);
int receiveFromServ(int data_type, void * data, int size);
int sendToServ(int data_type, void * data, int size);
void ErrorHandling(char *msg);

#endif