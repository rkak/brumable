
/*********************************
* 파일 이름 : bank.h
* 기능 : bank library
* last modified : 2019/02/21
* 수정자 : 송승호
**********************************/
#pragma once
#ifndef __BANK_H__
#define __BANK_H__
#include "common.h"
#define FIRST_BANK_MONEY 1  //초기에 은행에 있는 값
#define FIRST_FUND_MONEY 0 // 초기에 기부처에 있는값 
#define SALARY 250

typedef struct _bank {
	int bank_money;
	int fund_money;
}Bank;

extern void  bankInit(Bank * bank, int bank_money, int fund_money);
extern Bank * makeBank(int bank_money, int fund_money);

extern int getBankMoney(Bank * bank);
extern int setBankMoney(Bank * bank, int money);

extern int checkBankMoney(Bank * bank, int money);

//extern int payBankMoney(Bank * bank, int money);
//extern int  giveBankMoney(Bank * bank, int money);

extern int getFundMoney(Bank* bank);
extern int setFundMoney(Bank* bank, int fundmoney);

//extern void fundBank(Bank * bank, int fund_money);
extern int refundBank(Bank * bank);

#endif