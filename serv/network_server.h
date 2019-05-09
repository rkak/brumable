#pragma once
#ifndef __NETWORK_SERV_H__
#define __NETWORK_SERV_H__

#include <Windows.h>
#include "player.h"
#include "bank.h"

#define TYPE_INS	0
#define TYPE_PLAYER	1
#define TYPE_BANK	2
#define TYPE_CC		3

#define BUF_SIZE	100

void ErrorHandling(char *msg);
SOCKET initClntNet(void);
void connectClnt(void);
void doBrumable(void);

#endif