
/*********************************
* ���� �̸� : bank.c
* ��� : bank ����
* last modified : 2019/02/21
* ������ : �۽�ȣ
**********************************/
#include "bank.h"

/*
* �Լ� �̸� : bankInit
* return : Bank bank
* ���� : void
* ��� : Bank ��ҵ��� �ʱ�ȭ �Ѵ�.
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
void bankInit(Bank * bank, int bank_money, int fund_money) {  //Bank ����ü�� �ʱ�ȭ 
	setBankMoney(bank, bank_money);
	setFundMoney(bank, fund_money);
}

/*
* �Լ� �̸� : makeBank
* return : Bank* bank
* ���� : Bank * bank
* ��� :bank ����ü�� ������ �ʱ�ȭ
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
Bank* makeBank(int bank_money, int fund_money) {
	Bank * bank = (Bank*)malloc(sizeof(Bank));
	bankInit(bank, bank_money, fund_money);
	return bank;
}
/*
* �Լ� �̸� : getBankMoney
* return : int bank_money
* ���� : void
* ��� : bank_money�� ���� �����´�.
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
int getBankMoney(Bank * bank) {
	return bank->bank_money;
}
/*
* �Լ� �̸� : setBankMoney
* return : void
* ���� : int money
* ��� : bank_money�� set�Ѵ�.
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
int setBankMoney(Bank * bank, int money) {

	bank->bank_money = money;

	return 1;

}

///*
//* �Լ� �̸� : payBankMoney
//* return : int ���ǿ� ��ġ �Ұ�� money ���� ���ǿ� ��ġ ���� ������� FALSE ����
//* ���� : int money
//* ��� : ������ �÷��̾�� ���� �����ؾ��ϴ� ��ŭ �����ܰ� ���� �Լ�
//* last modified : 2019/02/22
//* ������ : �۽�ȣ
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
//* �Լ� �̸� :  giveBankMoney
//* return : money
//* ���� : int money
//* ��� : �÷��̾ ���࿡�� �����ؾ��� ���� ���� �ܰ� ���Ѵ�.
//* last modified : 2019/02/22
//* ������ : �۽�ȣ
//*/
//int  giveBankMoney(Bank * bank,int money) {
//
//	setBankMoney(bank,getBankMoney(bank) + money);
//	return money;
//}

/*
* �Լ� �̸� : checkBankMoney
* return : int  ���� ���ɰ�� 1 ���� �Ұ����ϰ�� 0
* ���� : int money ,
* ��� : �÷��̾�� �����ؾ��� ���� ���� �ܰ� �ִ��� Ȯ���Ѵ�.
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
int checkBankMoney(Bank * bank, int money) {
	if (getBankMoney(bank) >= money) {
		return TRUE;

	}
	else
		return FALSE;
}





/*
* �Լ� �̸� : getFundMoney
* return : int
* ���� : Bank* bank
* ��� : ���ó�� �ִ� ���� ���� ��������.
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
int getFundMoney(Bank* bank) {
	return bank->fund_money;

}


/*
* �Լ� �̸� : setFundMoney
* return : int
* ���� : Bank* bank int money
* ��� : ���ó�� �ִµ��� ���ο� ���� �����Ѵ�.
* last modified : 2019/02/23
* ������ : �۽�ȣ
*/
int setFundMoney(Bank* bank, int fundmoney) {
	bank->fund_money = fundmoney;

}


///*
//* �Լ� �̸� : fundBank
//* return : void 
//* ���� : int money
//* ��� : �÷��̾ ���ó�� �����ؾ��� ���� ����
//* last modified : 2019/02/22
//* ������ : �۽�ȣ
//*/
//void fundBank(Bank * bank, int fundMoney) {
//	setFundMoney(bank, getBankMoney(bank) + fundMoney);
//}

/*
* �Լ� �̸� : refundBank
* return : int temp
* ���� :
* ��� : �÷��̾ �޾ƾ��� ��ݾ��� ���θ� temp�� �����ϰ� bank.fund_money�� 0 ���� �ʱ�ȭ �ϰ� temp ����
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
int refundBank(Bank * bank) {
	int temp = getFundMoney(bank);
	bank->fund_money = FIRST_FUND_MONEY;
	return temp;
}

