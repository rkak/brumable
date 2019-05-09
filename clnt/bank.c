
/*********************************
* 파일 이름 : bank.c
* 기능 : bank 선언
* last modified : 2019/02/21
* 수정자 : 송승호
**********************************/
#include "bank.h"

/*
* 함수 이름 : bankInit
* return : Bank bank
* 인자 : void
* 기능 : Bank 요소들을 초기화 한다.
* last modified : 2019/02/22
* 수정자 : 송승호
*/
void bankInit(Bank * bank, int bank_money, int fund_money) {  //Bank 구조체를 초기화 
	setBankMoney(bank, bank_money);
	setFundMoney(bank, fund_money);
}

/*
* 함수 이름 : makeBank
* return : Bank* bank
* 인자 : Bank * bank
* 기능 :bank 구조체를 생성및 초기화
* last modified : 2019/02/22
* 수정자 : 송승호
*/
Bank* makeBank(int bank_money, int fund_money) {
	Bank * bank = (Bank*)malloc(sizeof(Bank));
	bankInit(bank, bank_money, fund_money);
	return bank;
}
/*
* 함수 이름 : getBankMoney
* return : int bank_money
* 인자 : void
* 기능 : bank_money의 값을 가져온다.
* last modified : 2019/02/22
* 수정자 : 송승호
*/
int getBankMoney(Bank * bank) {
	return bank->bank_money;
}
/*
* 함수 이름 : setBankMoney
* return : void
* 인자 : int money
* 기능 : bank_money를 set한다.
* last modified : 2019/02/22
* 수정자 : 송승호
*/
int setBankMoney(Bank * bank, int money) {

	bank->bank_money = money;

	return 1;

}

///*
//* 함수 이름 : payBankMoney
//* return : int 조건에 일치 할경우 money 리턴 조건에 일치 하지 않을경우 FALSE 리턴
//* 인자 : int money
//* 기능 : 은행이 플레이어에게 돈을 지급해야하는 만큼 보유잔고에 빼는 함수
//* last modified : 2019/02/22
//* 수정자 : 송승호
//*/
//
//int payBankMoney(Bank* bank,int money) {
//	if (check_bank(money)) {
//		setBankMoney(bank,get_bank() - money);
//		return money;
//	}
//	else
//		return FALSE;
//
//
//}
///*
//* 함수 이름 :  giveBankMoney
//* return : money
//* 인자 : int money
//* 기능 : 플레이어가 은행에게 지급해야할 돈을 보유 잔고에 더한다.
//* last modified : 2019/02/22
//* 수정자 : 송승호
//*/
//int  giveBankMoney(Bank * bank,int money) {
//
//	setBankMoney(bank,getBankMoney(bank) + money);
//	return money;
//}

/*
* 함수 이름 : checkBankMoney
* return : int  지급 가능경우 1 지급 불가능일경우 0
* 인자 : int money ,
* 기능 : 플레이어에게 지급해야할 돈이 은행 잔고에 있는지 확인한다.
* last modified : 2019/02/22
* 수정자 : 송승호
*/
int checkBankMoney(Bank * bank, int money) {
	if (getBankMoney(bank) >= money) {
		return TRUE;

	}
	else
		return FALSE;
}





/*
* 함수 이름 : getFundMoney
* return : int
* 인자 : Bank* bank
* 기능 : 모금처에 있는 돈의 값을 가져간다.
* last modified : 2019/02/22
* 수정자 : 송승호
*/
int getFundMoney(Bank* bank) {
	return bank->fund_money;

}


/*
* 함수 이름 : setFundMoney
* return : int
* 인자 : Bank* bank int money
* 기능 : 모금처에 있는돈을 새로운 값을 저장한다.
* last modified : 2019/02/23
* 수정자 : 송승호
*/
int setFundMoney(Bank* bank, int fundmoney) {
	bank->fund_money = fundmoney;

}


///*
//* 함수 이름 : fundBank
//* return : void 
//* 인자 : int money
//* 기능 : 플레이어가 모금처에 지급해야할 돈을 저장
//* last modified : 2019/02/22
//* 수정자 : 송승호
//*/
//void fundBank(Bank * bank, int fundMoney) {
//	setFundMoney(bank, getBankMoney(bank) + fundMoney);
//}

/*
* 함수 이름 : refundBank
* return : int temp
* 인자 :
* 기능 : 플레이어가 받아야할 모금액을 전부를 temp에 저장하고 bank.fund_money는 0 으로 초기화 하고 temp 리턴
* last modified : 2019/02/22
* 수정자 : 송승호
*/
int refundBank(Bank * bank) {
	int temp = getFundMoney(bank);
	bank->fund_money = FIRST_FUND_MONEY;
	return temp;
}

