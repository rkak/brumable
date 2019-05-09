/*********************************
* 파일 이름 : action_controller.c
* 기능 : action_controller 선언. action에 대한 controller
* last modified : 2019/02/22
* 수정자 : 박희완
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
* 함수 이름 : action
* return : void
* 인자 : void
* 기능 : 해당 location에 해당하는 action 진행
* last modified : 2019/02/23
* 수정자 : 박희완
*/

void action() {
	int cur_location = getPlayerLocation(p_turn);	// 현재 player의 location을 가져온다
	// whichLocation(city, cur_location) 대신, findLocationByNum를 사용, nation 값을 저장해주는 애를 만든다
	Nation * t;
	t = findLocationByNum(city, cur_location);

	// test를 위해 해당 위치 정보를 print
//	system("cls");

	SetInfoCursor();
	printf("도착 위치 정보\n");
	SetInfoCursor();
	printf("이름 : %s\n", t->name);
	SetInfoCursor();
	printf("location 번호 : %d\n", t->location_num);
	SetInfoCursor();
	printf("가격 : %d\n", t->price);
	SetInfoCursor();
	printf("상태 : %d\n", t->status);
	SetInfoCursor();
	printf("건물 개수 : %d\n", t->numOfBuilding);


	switch (getNationStatus(t)) {	// 해당 location이 어떤 종류의 nation인지 파악 후 실행
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

///* // 이것들은, move player쪽에서 하는 게 더 맞을듯
//* 함수 이름 : doStart
//* return : int 성공시 1, 실패시 0
//* 인자 : Player * p
//* 기능 : 해당 player에게 월급 지급
//* last modified : 2019/02/23
//* 수정자 : 박희완
//*/
//
//int doStart(Player * p) {
//	int player_money = getPlayerMoney(p);
//	int bank_money = getBankMoney(bank);
//
//	if (bank_money < SALARY) {
//		printf("은행에서 월급을 지급할 금액이 부족합니다\n");
//		return 0;
//	}
//
//	setPlayerMoney(p, player_money + SALARY);
//	setBankMoney(bank, bank_money - SALARY);
//
//	return 1;
//}


/*
* 함수 이름 : doGiveFund
* return : int 성공시 1, 실패시 0
* 인자 : Player * p
* 기능 : 해당 player 에서 fund를 빼, bank의 fund 에 넣는다
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int doGiveFund(Player * p) {
	// bank에 fund를 선언해서 거기에 넣어두면 될듯
	int fund_money;
	int player_money;
	int bank_fund;

	//수정 필요
	player_money = getPlayerMoney(p);
	bank_fund = getFundMoney(bank);
	fund_money = 50; // 임시

	if (!setPlayerMoney(p, player_money - fund_money) || !setFundMoney(bank, bank_fund + fund_money))
		return 0;

	return 1;
}

/*
* 함수 이름 : doCity
* return : int 성공시 1, 실패시 0
* 인자 : Player * p, Nation * t
* 기능 : 해당 city를 살 것인지, 말 것인지에 대한 함수
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int doCity(Player *p, Nation * t) {
	// 수정 필요
	Player *target;
	char more_building;
	char fail = 0;
	target = getNationOwner(t);

	if (target != NULL) {	// 누군가의 소유인 경우
		if (strcmp(getPlayerName(target), getPlayerName(p)) == 0) { // 나의 소유인 경우
			if (t->numOfBuilding >= BUILDINGCOUNT) {
				SetInfoCursor();
				printf("건물을 3개 모두 지었습니다 턴이 종료됩니다\n");
				return 1;
			}
			SetInfoCursor();
			puts("건물을 더 지으시겠습니까? (Y/N)");
			scanf("%c", &more_building); getchar();
			if (tolower(more_building) == 'y') {
				if (!constructBuilding(p, t)) {
					SetInfoCursor();
					printf("턴을 종료합니다");
					return 0;
				}
				SetInfoCursor();
				puts("건물을 구매하였습니다");
				return 1;
			}
		}
		else {	// 타인의 소유일 경우
			int fine;
			fine = getNationPrice(t);
			while (!giveFine(p, target, fine)) {
				if (!sellPossess(p)) {
					SetInfoCursor();
					puts("파산하시겠습니까? (Y/N)");
					scanf("%c", &fail); getchar();
					if (tolower(fail) == 'y')
						break;
				}
			}
			SetInfoCursor();
			printf("플레이어 %s가 %s에게 %d원의 통행료를 지불했습니다\n", getPlayerName(p), getPlayerName(target), fine);
			return 1;
		}
	}
	else {	// 누구의 소유도 아닌 경우
		// 도시의 정보를 print 해준다
		SetInfoCursor();
		printf("해당 도시의 가격은 %d 원 입니다\n", getNationPrice(t));
		if (!buyPossess(p, t)) {
			return 0;
		}
		SetInfoCursor();
		puts("도시를 구매하였습니다");
		return 1;
	}
}

/*
* 함수 이름 : giveFine
* return : int 성공시 1, 실패시 0(p의 재산이 부족한 경우)
* 인자 : Player * p, Player * target, int fine
* 기능 : player p가 target에게 벌금을 줌
* last modified : 2019/02/23
* 수정자 : 박희완
*/

int giveFine(Player * p, Player * target, int fine) {
	int p_money = getPlayerMoney(p);
	int t_money = getPlayerMoney(target);

	if (!setPlayerMoney(p, p_money - fine))
		return 0;	// p의 재산이 부족한 경우

	setPlayerMoney(target, t_money + fine);
	
	return 1;
}

/*
* 함수 이름 : sellPossess
* return : int 성공시 1, 실패시 0
* 인자 : Player * p, Player * target
* 기능 : p의 possess를 판매
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int sellPossess(Player *p) {
	int num_of_poss = getPlayerNumOfPossession(p);
	char sell[20];	// natino name size = 20;
	char is_sell;
	if (num_of_poss == 0)
		return 0;

	SetInfoCursor();
	puts("당신의 소유 리스트입니다");
	printPlayerPossession(p);

	SetInfoCursor();
	printf("당신의 소유를 파시겠습니까? 파시지 않는다면, 파산하게 됩니다 (Y/N) : ");
	scanf("%c", &is_sell); getchar();
	if (tolower(is_sell) == 'y') {
		SetInfoCursor();
		printf("팔 소유의 이름 입력하세요 : ");
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
* 함수 이름 : buyPossess
* return : int 성공시 1, 실패시 0
* 인자 : Player * p, Nation * n
* 기능 : p가 n을 구매
* last modified : 2019/02/23
* 수정자 : 박희완
*/

int buyPossess(Player *p, Nation * n) {
	char is_buy;
	int player_money;
	int nation_price;
	player_money = getPlayerMoney(p);
	nation_price = getNationPrice(n);
	SetInfoCursor();
	printf("해당 도시를 구매하시겠습니까? (Y/N) : ");
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
* 함수 이름 : constructBuilding
* return : int 성공시 1, 실패시 0
* 인자 : Player * p, Nation * n
* 기능 : nation에 building을 추가
* last modified : 2019/02/23
* 수정자 : 박희완
*/

int constructBuilding(Player *p, Nation * n) {
	// 일단 건물 종류 상관없이.
	//char kind[10];	// 건물의 종류
	//puts("어떤 건물을 추가하시겠습니까? (모텔/콘도/호텔)");
	//scanf("%s", kind); getchar();
	//while ((strcmp(kind, "모텔") || strcmp(kind, "콘도") || strcmp(kind, "호텔"))) {
	//	printf("모텔, 콘도, 호텔 중 하나를 입력하세요\n");
	//	scanf("%s", kind); getchar();
	//}
	int price;
	//if (!strcmp(kind, "모텔"))
	//	price = 100;
	//else if (!strcmp(kind, "콘도"))
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
* 함수 이름 : doChanceCard
* return : int 성공시 1, 실패시 0
* 인자 : Player * p
* 기능 : chaceCard를 한 장 뽑고, 그것을 실행.
* last modified : 2019/02/23
* 수정자 : 박희완
*/

int doChanceCard(Player *p) {
	srand((unsigned int)time(NULL));
	int ccnum = rand() % CHANCE_CARD_NUM;
	ChanceCard * cur_c = cc[ccnum];
	SetInfoCursor();
	printf("%d 번째 카드를 뽑으셨습니다\n", ccnum + 1);
	SetInfoCursor();
	printf("카드 번호 : %d\n", cur_c->card_num);
	SetInfoCursor();
	printf("카드의 이름은 %s 입니다\n", cur_c->name);
	SetInfoCursor();
	printf("카드의 효과는 %s 입니다\n", cur_c->explain);
	SetInfoCursor();
	printf("카드의 효과를 실행합니다\n");
	// 수정 필요. 함수 만든 후 작성
	if(!cur_c->action(p_turn)){
		return 0;
	}
	return 1;
}

/*
* 함수 이름 : doDesertIsland
* return : int. 1이면 계속 남아있고, 0이면 그 턴부터 돔
* 인자 : Player * p
* 기능 : desert island에 있을 경우, throw dice 후 double이면 다음 턴 탈출, 아니면 3번 동안 턴 종료
* last modified : 2019/02/23
* 수정자 : 박희완
*/

int doDesertIsland(Player *p) {
	SetInfoCursor();
	printf("무인도에 걸렸습니다! 3턴동안 움직이실 수 없습니다.\n주사위를 던져 더블이 나오게 한다면 다음 턴에 탈출합니다\n");
	setPlayerBreakTurn(p, 3);
	setPlayerStatus(p, STAT_DESERTISLAND);
	return 1;
}

/*
* 함수 이름 : doTravel
* return : int. 성공시 1, 실패시 0
* 인자 : Player * p
* 기능 : player의 status를 STAT_TRAVEL로 변경, 해당 player는 다음 턴에 원하는 곳으로 이동
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int doTravel(Player *p) {
	SetInfoCursor();
	printf("KTX에 걸렸습니다! 다음 턴에 원하는 지역에 갈 수 있습니다\n");
	setPlayerStatus(p_turn, STAT_TRAVEL);
}

/*
* 함수 이름 : doReceiveFund
* return : int. 성공시 1, 실패시 0
* 인자 : Player * p
* 기능 : bank에 저장된 모든 fund를 player에게 줌
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int doReceiveFund(Player *p) {
	// bank의 모든 Fund를 가져와서 p의 money에 넣어두면 될듯
	int fund_money;
	int player_money;
	
	// 수정 필요
	fund_money = getFundMoney(bank);
	
	player_money = getPlayerMoney(p);
	if (!setPlayerMoney(p, player_money + fund_money))
		return 0;

	setFundMoney(bank, 0);

	return 1;
}