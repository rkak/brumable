/*********************************
* ���� �̸� : action_controller.c
* ��� : action_controller ����. action�� ���� controller
* last modified : 2019/02/22
* ������ : �����
**********************************/

#include "action_controller.h"
#include "bank.h"
#include "controller.h"
#include <time.h>

extern Player *p_turn;
extern ChanceCard ** cc;
extern Nation ** city;
extern Bank * bank;
extern int info_print_cursor_x;
extern int info_print_cursor_y;

/*
* �Լ� �̸� : action
* return : void
* ���� : void
* ��� : �ش� location�� �ش��ϴ� action ����
* last modified : 2019/02/23
* ������ : �����
*/

void action() {
	int cur_location = getPlayerLocation(p_turn);	// ���� player�� location�� �����´�
	// whichLocation(city, cur_location) ���, findLocationByNum�� ���, nation ���� �������ִ� �ָ� �����
	Nation * t;
	t = findLocationByNum(city, cur_location);

	// test�� ���� �ش� ��ġ ������ print
//	system("cls");

	SetInfoCursor();
	printf("���� ��ġ ����\n");
	SetInfoCursor();
	printf("�̸� : %s\n", t->name);
	SetInfoCursor();
	printf("location ��ȣ : %d\n", t->location_num);
	SetInfoCursor();
	printf("���� : %d\n", t->price);
	SetInfoCursor();
	printf("���� : %d\n", t->status);
	SetInfoCursor();
	printf("�ǹ� ���� : %d\n", t->numOfBuilding);


	switch (getNationStatus(t)) {	// �ش� location�� � ������ nation���� �ľ� �� ����
		case KIND_FUND:
			doGiveFund(p_turn);
			break;
		case KIND_CITY:
			doCity(p_turn, t);
			break;
		case KIND_CHANCECARD:
			doChanceCard(p_turn);
			break;
		case KIND_DESERTISLNAD:
			doDesertIsland(p_turn);
			break;
		case KIND_TRAVEL:
			doTravel(p_turn);
			break;
		case KIND_FUND_RECEIVE:
			doReceiveFund(p_turn);
			break;
		default:
			break;
	}
}

///* // �̰͵���, move player�ʿ��� �ϴ� �� �� ������
//* �Լ� �̸� : doStart
//* return : int ������ 1, ���н� 0
//* ���� : Player * p
//* ��� : �ش� player���� ���� ����
//* last modified : 2019/02/23
//* ������ : �����
//*/
//
//int doStart(Player * p) {
//	int player_money = getPlayerMoney(p);
//	int bank_money = getBankMoney(bank);
//
//	if (bank_money < SALARY) {
//		printf("���࿡�� ������ ������ �ݾ��� �����մϴ�\n");
//		return 0;
//	}
//
//	setPlayerMoney(p, player_money + SALARY);
//	setBankMoney(bank, bank_money - SALARY);
//
//	return 1;
//}


/*
* �Լ� �̸� : doGiveFund
* return : int ������ 1, ���н� 0
* ���� : Player * p
* ��� : �ش� player ���� fund�� ��, bank�� fund �� �ִ´�
* last modified : 2019/02/21
* ������ : �����
*/

int doGiveFund(Player * p) {
	// bank�� fund�� �����ؼ� �ű⿡ �־�θ� �ɵ�
	int fund_money;
	int player_money;
	int bank_fund;

	//���� �ʿ�
	player_money = getPlayerMoney(p);
	bank_fund = getFundMoney(bank);
	fund_money = 50; // �ӽ�

	if (!setPlayerMoney(p, player_money - fund_money) || !setFundMoney(bank, bank_fund + fund_money))
		return 0;

	return 1;
}

/*
* �Լ� �̸� : doCity
* return : int ������ 1, ���н� 0
* ���� : Player * p, Nation * t
* ��� : �ش� city�� �� ������, �� �������� ���� �Լ�
* last modified : 2019/02/22
* ������ : �����
*/

int doCity(Player *p, Nation * t) {
	// ���� �ʿ�
	Player *target;
	char more_building;
	char fail = 0;
	target = getNationOwner(t);

	if (target != NULL) {	// �������� ������ ���
		if (strcmp(getPlayerName(target), getPlayerName(p)) == 0) { // ���� ������ ���
			if (t->numOfBuilding >= BUILDINGCOUNT) {
				SetInfoCursor();
				printf("�ǹ��� 3�� ��� �������ϴ� ���� ����˴ϴ�\n");
				return 1;
			}
			SetInfoCursor();
			puts("�ǹ��� �� �����ðڽ��ϱ�? (Y/N)");
			scanf("%c", &more_building); getchar();
			if (tolower(more_building) == 'y') {
				if (!constructBuilding(p, t)) {
					SetInfoCursor();
					printf("���� �����մϴ�");
					return 0;
				}
				SetInfoCursor();
				puts("�ǹ��� �����Ͽ����ϴ�");
				return 1;
			}
		}
		else {	// Ÿ���� ������ ���
			int fine;
			fine = getNationPrice(t);
			while (!giveFine(p, target, fine)) {
				if (!sellPossess(p)) {
					SetInfoCursor();
					puts("�Ļ��Ͻðڽ��ϱ�? (Y/N)");
					scanf("%c", &fail); getchar();
					if (tolower(fail) == 'y')
						break;
				}
			}
			SetInfoCursor();
			printf("�÷��̾� %s�� %s���� %d���� ����Ḧ �����߽��ϴ�\n", getPlayerName(p), getPlayerName(target), fine);
			return 1;
		}
	}
	else {	// ������ ������ �ƴ� ���
		// ������ ������ print ���ش�
		SetInfoCursor();
		printf("�ش� ������ ������ %d �� �Դϴ�\n", getNationPrice(t));
		if (!buyPossess(p, t)) {
			return 0;
		}
		SetInfoCursor();
		puts("���ø� �����Ͽ����ϴ�");
		return 1;
	}
}

/*
* �Լ� �̸� : giveFine
* return : int ������ 1, ���н� 0(p�� ����� ������ ���)
* ���� : Player * p, Player * target, int fine
* ��� : player p�� target���� ������ ��
* last modified : 2019/02/23
* ������ : �����
*/

int giveFine(Player * p, Player * target, int fine) {
	int p_money = getPlayerMoney(p);
	int t_money = getPlayerMoney(target);

	if (!setPlayerMoney(p, p_money - fine))
		return 0;	// p�� ����� ������ ���

	setPlayerMoney(target, t_money + fine);
	
	return 1;
}

/*
* �Լ� �̸� : sellPossess
* return : int ������ 1, ���н� 0
* ���� : Player * p, Player * target
* ��� : p�� possess�� �Ǹ�
* last modified : 2019/02/22
* ������ : �����
*/

int sellPossess(Player *p) {
	int num_of_poss = getPlayerNumOfPossession(p);
	char sell[20];	// natino name size = 20;
	char is_sell;
	if (num_of_poss == 0)
		return 0;

	SetInfoCursor();
	puts("����� ���� ����Ʈ�Դϴ�");
	printPlayerPossession(p);

	SetInfoCursor();
	printf("����� ������ �Ľðڽ��ϱ�? �Ľ��� �ʴ´ٸ�, �Ļ��ϰ� �˴ϴ� (Y/N) : ");
	scanf("%c", &is_sell); getchar();
	if (tolower(is_sell) == 'y') {
		SetInfoCursor();
		printf("�� ������ �̸� �Է��ϼ��� : ");
		scanf("%s", sell); getchar();

		Nation * n = findLocation(city, sell);
		if (!deletePlayerPossession(p, n)) {
			return 0;
		}
		setPlayerMoney(p, getPlayerMoney(p) - getNationPrice(n));
		delNationOwner(findLocation(city, sell));
		return 1;
	}
	return 0;
}

/*
* �Լ� �̸� : buyPossess
* return : int ������ 1, ���н� 0
* ���� : Player * p, Nation * n
* ��� : p�� n�� ����
* last modified : 2019/02/23
* ������ : �����
*/

int buyPossess(Player *p, Nation * n) {
	char is_buy;
	int player_money;
	int nation_price;
	player_money = getPlayerMoney(p);
	nation_price = getNationPrice(n);
	SetInfoCursor();
	printf("�ش� ���ø� �����Ͻðڽ��ϱ�? (Y/N) : ");
	scanf("%c", &is_buy); getchar();
	if (tolower(is_buy) == 'y') {
		if (p->num_of_possession > PLAYER_POSSESSION_SIZE)
			return 0;
		if (player_money < nation_price) {
			SetInfoCursor();
			printf("No enough money\n");
		}
		setPlayerMoney(p, player_money - nation_price);
		addPlayerPossession(p, n);
		setNationOwner(n, p);
		return 1;
	}
	return 0;
}

/*
* �Լ� �̸� : constructBuilding
* return : int ������ 1, ���н� 0
* ���� : Player * p, Nation * n
* ��� : nation�� building�� �߰�
* last modified : 2019/02/23
* ������ : �����
*/

int constructBuilding(Player *p, Nation * n) {
	// �ϴ� �ǹ� ���� �������.
	//char kind[10];	// �ǹ��� ����
	//puts("� �ǹ��� �߰��Ͻðڽ��ϱ�? (����/�ܵ�/ȣ��)");
	//scanf("%s", kind); getchar();
	//while ((strcmp(kind, "����") || strcmp(kind, "�ܵ�") || strcmp(kind, "ȣ��"))) {
	//	printf("����, �ܵ�, ȣ�� �� �ϳ��� �Է��ϼ���\n");
	//	scanf("%s", kind); getchar();
	//}
	int price;
	//if (!strcmp(kind, "����"))
	//	price = 100;
	//else if (!strcmp(kind, "�ܵ�"))
	//	price = 200;
	//else
	//	price = 300;

	price = 100;
	Building b; // = (Building *)malloc(sizeof(Building));
	makeBuilding(&b, price);
	
	addNationBuilding(n, b);
	return 1;
}

/*
* �Լ� �̸� : doChanceCard
* return : int ������ 1, ���н� 0
* ���� : Player * p
* ��� : chaceCard�� �� �� �̰�, �װ��� ����.
* last modified : 2019/02/23
* ������ : �����
*/

int doChanceCard(Player *p) {
	srand((unsigned int)time(NULL));
	int ccnum = rand() % CHANCE_CARD_NUM;
	ChanceCard * cur_c = cc[ccnum];
	SetInfoCursor();
	printf("%d ��° ī�带 �����̽��ϴ�\n", ccnum + 1);
	SetInfoCursor();
	printf("ī�� ��ȣ : %d\n", cur_c->card_num);
	SetInfoCursor();
	printf("ī���� �̸��� %s �Դϴ�\n", cur_c->name);
	SetInfoCursor();
	printf("ī���� ȿ���� %s �Դϴ�\n", cur_c->explain);
	SetInfoCursor();
	printf("ī���� ȿ���� �����մϴ�\n");
	// ���� �ʿ�. �Լ� ���� �� �ۼ�
	if(!cur_c->action(p_turn)){
		return 0;
	}
	return 1;
}

/*
* �Լ� �̸� : doDesertIsland
* return : int. 1�̸� ��� �����ְ�, 0�̸� �� �Ϻ��� ��
* ���� : Player * p
* ��� : desert island�� ���� ���, throw dice �� double�̸� ���� �� Ż��, �ƴϸ� 3�� ���� �� ����
* last modified : 2019/02/23
* ������ : �����
*/

int doDesertIsland(Player *p) {
	SetInfoCursor();
	printf("���ε��� �ɷȽ��ϴ�! 3�ϵ��� �����̽� �� �����ϴ�.\n�ֻ����� ���� ������ ������ �Ѵٸ� ���� �Ͽ� Ż���մϴ�\n");
	setPlayerBreakTurn(p, 3);
	setPlayerStatus(p, STAT_DESERTISLAND);
	return 1;
}

/*
* �Լ� �̸� : doTravel
* return : int. ������ 1, ���н� 0
* ���� : Player * p
* ��� : player�� status�� STAT_TRAVEL�� ����, �ش� player�� ���� �Ͽ� ���ϴ� ������ �̵�
* last modified : 2019/02/21
* ������ : �����
*/

int doTravel(Player *p) {
	SetInfoCursor();
	printf("KTX�� �ɷȽ��ϴ�! ���� �Ͽ� ���ϴ� ������ �� �� �ֽ��ϴ�\n");
	setPlayerStatus(p_turn, STAT_TRAVEL);
}

/*
* �Լ� �̸� : doReceiveFund
* return : int. ������ 1, ���н� 0
* ���� : Player * p
* ��� : bank�� ����� ��� fund�� player���� ��
* last modified : 2019/02/21
* ������ : �����
*/

int doReceiveFund(Player *p) {
	// bank�� ��� Fund�� �����ͼ� p�� money�� �־�θ� �ɵ�
	int fund_money;
	int player_money;
	
	// ���� �ʿ�
	fund_money = getFundMoney(bank);
	
	player_money = getPlayerMoney(p);
	if (!setPlayerMoney(p, player_money + fund_money))
		return 0;

	setFundMoney(bank, 0);

	return 1;
}