/*********************************
* 파일 이름 : controller.c
* 기능 : controller 기능 구현
* last modified : 2019/02/25
* 수정자 : 박희완
**********************************/

#include <time.h>

#include "controller.h"
#include "common.h"
#include "action_controller.h"
#include "chanceCard_action_controller.h"
#include "bank.h"
#include "gui.h"


// information 출력하는 부분에 정확히 출력되도록 하는 함수로 새로 정의
//#define infoPrintf(str) setCursor(info_print_cursor_x, info_print_cursor_y++); printf(str)


static int turn;
int move_location;

int player_num;
int info_print_cursor_x = 23;
int info_print_cursor_y = 9;
 
extern int player_num;

Player **p;
Player * p_turn;	// 현재 turn인 player
Nation ** city;
ChanceCard ** cc;
Bank * bank;
SOCKET hSocket;

// for networking variable
Player *p_net;
Player p_op_net;	// opponent player
Bank bank_net;

/*
* 함수 이름 : bitmable
* return : void
* 인자 : void
* 기능 : 전체적인 game의 flow 진행
* last modified : 2019/02/25
* 수정자 : 박희완
*/

void bitmable(void) {
	int player_status;
/*
	gui_loading_display();	

	int return_n = gui_menu_choice();	
	
	if (return_n != 0) {	
		return 0;
	}
*/
	mableInit();


	//플레이어 만들어지고 게임 시작 할 차례 -> 플레이어가 판안에 표시 되어야함
	system("cls");

	// server에게 player 정보를 넘겨준다
	initClntNet();

	system("cls");


	turnInit();         //턴 주어지고
						//표시 필요 (START지점)

	while (1) {
		removeCursor();
		info_print_cursor_y = 9;
		system("cls");
//		gui_map_Init(city); //맵그려지고

		// system("cls");

		/*
		printf("각 도시의 정보입니다\n");
		for (int i = 0; i < CITY_COUNT; i+=2) {
			printf("%10s : %10s\t", getNationName(city[i]), getNationOwner(city[i]));
			printf("%10s : %10s\n", getNationName(city[i+1]), getNationOwner(city[i+1]));
		}
		*/

		
//		WHITE;
//		
		
		printf("player 정보입니다\n");
		for (int i = 0; i < player_num; i++) {
//			
			printf("%10s : %10d", getPlayerName(p[i]), getPlayerMoney(p[i]));
		}
		puts("");

		printf("bank 정보입니다\n");

		
		printf("%10d : %10d\n", getBankMoney(bank), getFundMoney(bank));

		chooseTurn();

		printf("%s의 턴입니다\n", getPlayerName(p_turn));

		player_status = checkPlayer();
		

		if (player_status == -1) {
			continue;
		}
		else if (player_status == STAT_DESERTISLAND) {
			int player_break_turn = getPlayerBreakTurn(p_turn);
			if (throwDice(0) == 2 || player_break_turn <= 0) {	// 두 주사위 double 시 return 2
				// test 필요
				setPlayerBreakTurn(p_turn, 0);
				setPlayerStatus(p_turn, STAT_GAMING);
			}
			else {
				setPlayerBreakTurn(p_turn, --player_break_turn);
			}
			continue;
		}
		else if (player_status == STAT_TRAVEL) {
			//	char player_want_place[NATION_NAME_SIZE];
			char player_want_place[20]; // 임시
			Nation * target;		// 이동하고자 하는 도시

			
			printf("원하는 장소를 입력하세요 : ");

			scanf("%s", player_want_place); getchar();
			target = findLocation(city, player_want_place);
			if (target == NULL)
				return 0;

			
			printf("%s로 이동합니다", getNationName(target));

			int temp_location = getNationLocationNum(target) - getPlayerLocation(p_turn);

			if (temp_location >= 0) {
				move_location = temp_location;
			}
			else {
				move_location = 28 + temp_location;
			}

			setPlayerStatus(p_turn, STAT_GAMING);
		}
		else {
			if (throwDice(0) == 2) {	// 만약 double이 일어난다면
				while (getchar() != '\n');

				//infoPrintf("double! 한번 더 던지세요\n");
				
				printf("double! 한번 더 던지세요\n");
				throwDice(1);
			}
			while (getchar() != '\n');
		}
		
		// nation에 관한 테스트 시 이곳에서 move_location 변경

		movePlayer(move_location);

		action();

		while (getchar() != '\n');

		if (p_turn->money <= 0) {
			break;
		}
		
		
		/*if (exit())
			break;*/
	}

}


void bitmableForNet(void) {
	int player_status;
/*
	gui_loading_display();

	int return_n = gui_menu_choice();

	if (return_n != 0) {
		return 0;
	}
*/
	mableInitForNet();


	//플레이어 만들어지고 게임 시작 할 차례 -> 플레이어가 판안에 표시 되어야함
	system("cls");

	// server에게 player 정보를 넘겨준다
	doServ();


	int dataLen = recv(hSocket, (char *)&p_op_net, sizeof(Player), 0);
	printf("U are %s\n", p_net->name);
	printf("Op name : %s\n", p_op_net.name);

	dataLen = recv(hSocket, (char *)&bank_net, sizeof(Bank), 0);

	system("cls");


	while (1) {

		recv(hSocket, (char *)&turn, sizeof(int), 0);

		removeCursor();
		info_print_cursor_y = 9;
		system("cls");

		

		if (turn) {
			
			printf("사용자의 턴입니다\n");
			p_turn = p_net;
			gui_map_Init_for_net(city); // map 그리기

			WHITE;
			
			printf("player 정보입니다\n");
			
			printf("%10s : %10d", getPlayerName(p_net), getPlayerMoney(p_net));
			
			printf("%10s : %10d", getPlayerName(&p_op_net), getPlayerMoney(&p_op_net));
			puts("");

			player_status = checkPlayer();

			if (player_status == -1) {
//				continue;
			}
			else if (player_status == STAT_DESERTISLAND) {
				int player_break_turn = getPlayerBreakTurn(p_turn);
				if (throwDice(0) == 2 || player_break_turn <= 0) {	// 두 주사위 double 시 return 2
					// test 필요
					setPlayerBreakTurn(p_turn, 0);
					setPlayerStatus(p_turn, STAT_GAMING);
				}
				else {
					setPlayerBreakTurn(p_turn, --player_break_turn);
				}
//				continue;
			}
			else if (player_status == STAT_TRAVEL) {
				//	char player_want_place[NATION_NAME_SIZE];
				char player_want_place[20]; // 임시
				Nation * target;		// 이동하고자 하는 도시

				
				printf("원하는 장소를 입력하세요 : ");

				scanf("%s", player_want_place); getchar();
				target = findLocation(city, player_want_place);
				if (target == NULL)
					return 0;

				
				printf("%s로 이동합니다", getNationName(target));

				int temp_location = getNationLocationNum(target) - getPlayerLocation(p_turn);

				if (temp_location >= 0) {
					move_location = temp_location;
				}
				else {
					move_location = 28 + temp_location;
				}

				setPlayerStatus(p_turn, STAT_GAMING);
			}
			else {
				if (throwDice(0) == 2) {	// 만약 double이 일어난다면
					while (getchar() != '\n');

					//infoPrintf("double! 한번 더 던지세요\n");
					
					printf("double! 한번 더 던지세요\n");
					throwDice(1);
				}
				while (getchar() != '\n');
			}

			// nation에 관한 테스트 시 이곳에서 move_location 변경

			movePlayer(move_location);

			action();

			send(hSocket, (char *)&move_location, sizeof(int), 0);
			
			
			//send(hSocket, (char *)p_net, sizeof(Player), 0);

			
			printf("Push enter\n");

			while (getchar() != '\n');
		}
		else {
			gui_map_Init_for_net(city); // map 그리기

			
			printf("상대방의 턴입니다\n");
			int ex_pos = p_op_net.location;

			dataLen = recv(hSocket, (char *)&move_location, sizeof(int), 0);
			p_turn = &p_op_net;

			movePlayer(move_location);

			WHITE;
			
			printf("player 정보입니다\n");
			
			printf("%10s : %10d", getPlayerName(p_net), getPlayerMoney(p_net));
			
			printf("%10s : %10d", getPlayerName(&p_op_net), getPlayerMoney(&p_op_net));
			puts("");

			
			printf("Push enter\n");
			while (getchar() != '\n');

		}

		if (p_turn->money <= 0) {
			quitNet();
			if (p_turn == &p_op_net) {
				printf("%s win!\n%s lose T.T\n", p_turn->name, p_op_net.name);
			}
			else {
				printf("%s win!\n%s lose T.T\n", p_op_net.name, p_turn->name);
			}
			
			printf("프로그램을 종료합니다. 엔터키를 눌러주세요\n");
			while (getchar() != '\n');
			exit(0);
		}
	}
}

/*
* 함수 이름 : mableInit
* return : void
* 인자 : void
* 기능 : mable game의 init 진행, 모든 게임의 init이 진행
* last modified : 2019/02/25
* 수정자 : 박희완
*/

void mableInit(void) {
	system("cls");
	
	makeNations();
	makeCCs();
	makeBanks();
	makePlayers();	
}

void mableInitForNet(void) {
	system("cls");

	makeNations();
	makeCCs();
//	makeBanks();
	makePlayerForNet();

}


/*
* 함수 이름 : setPlayerNum
* return : int. 성공시 1, 실패시 0
* 인자 : void
* 기능 : player 수 설정 및 Player ** p의 메모리 할당
* last modified : 2019/02/25
* 수정자 : 박희완
*/


int setPlayerNum(void) {
	YELLOW;
	//setCursor(22, 12);
	puts("Player 수를 입력하시오");
	//setCursor(22, 13);
	puts("-----------------------");
	setCursor(3, 3);
	//setCursor(25, 15);
	printf("명");
	setCursor(1, 3);
	//setCursor(23, 15);
	viewCursor();
	scanf("%d", &player_num); getchar();

	p = (Player **)malloc(sizeof(Player *) * player_num);	// Player 포인터 배열 만들기
	if (p == NULL)
		return 0;
	return 1;
}

/*
* 함수 이름 : makePlayers
* return : void
* 인자 : void
* 기능 : player 수를 정하고, 각 player마다 메모리 할당 및 이름 설정
* last modified : 2019/02/25
* 수정자 : 박희완
*/

void makePlayers(void) {
	setPlayerNum();

	char name[PLAYER_NAME_SIZE];
	for (int i = 0; i < player_num; i++) {
//		setCursor(0, 0);
		switch (i) {
		case 0:
			RED;
			break;
		case 1:
			BLUE;
			break;
		case 2:
			HIGH;
			break;
		case 3:
			SKY;
			break;
		}
		printf("Player %d", i + 1);
		YELLOW;
		printf("의 이름을 입력하시오");
		//setCursor(22, 25);
		puts("----------------------------");


		switch (i) {
		case 0:
			RED;
			break;
		case 1:
			BLUE;
			break;
		case 2:
			HIGH;
			break;
		case 3:
			SKY;
			break;
		}

		viewCursor();
		scanf("%s", name); getchar();
		p[i] = makePlayer(name);

	}
}

void makePlayerForNet(void) {
	char name[PLAYER_NAME_SIZE];

	YELLOW;
	printf("Player 이름을 입력하시오");
	//setCursor(22, 25);
	puts("----------------------------");

	RED;
	viewCursor();
	scanf("%s", name); getchar();
	p_net = makePlayer(name);
}


/*
* 함수 이름 : makeCCs
* return : void
* 인자 : void
* 기능 : CC를 만들고 메모리 할당 및 init
* last modified : 2019/02/23
* 수정자 : 박희완
*/

void makeCCs(void) {
	char * ccName[20] = {
		"편안한 휴식", "여행", "월급받는날", "d", "e", "f", "g", "h", "i", "j"
	};
	char * ccExplain[100] = {
		"무인도로 이동", "기차 여행", "Start 지점으로 이동", "D", "E", "F", "G", "H", "I", "J"
	};
	int(*ccAction[20])() = {
		moveToIsland, moveToTrain, moveToStart
	};

	cc = (ChanceCard **)malloc(sizeof(ChanceCard *) * CHANCE_CARD_NUM);

	for (int i = 0; i < CHANCE_CARD_NUM; i++) {
		cc[i] = makeCC(ccName[i], ccExplain[i], i, ccAction[i]);
	}
}

/*
* 함수 이름 : makeNations
* return : void
* 인자 : void
* 기능 : nation을 만들고 메모리 할당 및 init
* last modified : 2019/02/24
* 수정자 : 구종석
*/

void makeNations(void) {
	//첫번째 start형이 chanceCard_action_controller.c에 찬스카드 start 로 리턴 하신 것 같아서 이름 Start로 해놨어요~
	/*
int moveToStart(void * p) {
	p = (Player *)p;
	return movePlayerByName("Start");
}*/
	char city_name[][20] = { { "Start" },{ "수원" },{ "세금납부" },{ "용인" },{ "군산" },{ "복불복" },{ "익산" },{ "전주" },{ "무인도" }, //가로윗줄
	{ "경주" },{ "포항" },{ "대구" },{ "찬스카드" },{ "창원" },{ "유니세프" },
	{ "울산" },{ "부산" },{ "휴게소" },{ "공주" },{ "여수" },{ "찬스카드" },{ "강릉" },{ "KTX" },
	{ "청주" },{ "천안" },{ "인천" },{ "기부천사" },{ "서울" } };

	//int price[CITY_COUNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
	//	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	//	21, 22, 23, 24, 25, 26, 27, 28
	//};

	/*세금납부 건물X가격이라 가격은 일단0으로했고 세금납부가격은 건물X8만원 로정해놨어요 시작가격250만원으로 할 생각이고
	  기부천사는 15만원으로 정했어요~ 그밖에도 특수한경우는 다 0원으로 해놨어요
	  휴게소 = 0원이고 한번 쉬다가는 곳
	*/
	int price[CITY_COUNT] = {0,5,0,8,8,0,12,12,0,
		14,16,16,0,18,0,
		22,28,0,24,26,0,26,0,
		30,32,32,0,35
	};



	/* 
	세금납부 -> KIND_FUND 인데 RECEIVE X BANK만 돈 전달
	복불복 -> KIND_CHNACECARD로 처리해도 되는지
	휴게소 -> KIND_CITY 로 0원 하면 될 것 같다
	*/
	Nation_Staus city_status[CITY_COUNT] = { KIND_START, KIND_CITY, KIND_FUND, KIND_CITY, KIND_CITY,  KIND_CHANCECARD, KIND_CITY, KIND_CITY, KIND_DESERTISLNAD,
	KIND_CITY, KIND_CITY, KIND_CITY, KIND_CHANCECARD, KIND_CITY, KIND_FUND_RECEIVE,
	KIND_CITY, KIND_CITY, KIND_CITY, KIND_CITY, KIND_CITY, KIND_CHANCECARD, KIND_CITY, KIND_TRAVEL,
	KIND_CITY, KIND_CITY, KIND_CITY, KIND_FUND, KIND_CITY
	};

	city = (Nation **)malloc(sizeof(Nation *) * CITY_COUNT);

	for (int i = 0; i < CITY_COUNT; i++) {
		city[i] = makeNation(city_name[i], price[i], city_status[i], i);
	}
}

/*
* 함수 이름 : turnInit
* return : int. 해당 turn return
* 인자 : void
* 기능 : 맨 처음 turn으로 시작할 사람 정하기
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int turnInit(void) {
	int t = -1;


	turn = t;
	return t;
}

/*
* 함수 이름 : makeBanks
* return : void
* 인자 : void
* 기능 : bank 생성
* last modified : 2019/02/23
* 수정자 : 박희완
*/

void makeBanks(void) {
	int bank_money = 1000000;
	int fund_money = 0;
	bank = makeBank(bank_money, fund_money);
}

/*
* 함수 이름 : chooseTurn
* return : int. 해당 turn return
* 인자 : void
* 기능 : 매 턴마다 어떤 player 차례인지를 결정
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int chooseTurn(void) {
	srand((unsigned int)time(NULL));
	turn = (++turn) % player_num;
	p_turn = p[turn];

	for (int i = 0; i < player_num; i++) { // 모든 player의 turn 초기화
		losePlayerTurn(p[i]);
	}
	givePlayerTurn(p_turn);	// 정해진 player의 turn 설정

	return turn;
}

int chooseTurnForNet(void) {
	srand((unsigned int)time(NULL));
	turn = (++turn) % 2;
	if (turn)
		p_turn = p_net;
	else
		p_turn = &p_op_net;
//	p_turn = p[turn];

	losePlayerTurn(p_net);
	losePlayerTurn(&p_op_net);

	givePlayerTurn(p_turn);	// 정해진 player의 turn 설정

	return turn;
}

/*
* 함수 이름 : checkPlayer
* return : int
* 인자 : void
* 기능 : player가 정해지면, 해당 player의 상태를 점검
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int checkPlayer(void) {
	switch (getPlayerStatus(p_turn)) {
	case STAT_GAMING:	// 게임중인 player

		return STAT_GAMING;
	case STAT_FAIL:		// 파산한 player

		return -1;
	case STAT_WINNER:	// 이미 이긴 player

		return -1;
	case STAT_DESERTISLAND:	// 무인도에 있는 player

		return -1;
	case STAT_TRAVEL:	// 우주여행을 해야 하는 player

		return STAT_TRAVEL;
	}
	return -1;
}

/*
* 함수 이름 : throwDice
* return : int double이면 2, 정상이면 1, 실패시 0
* 인자 : int twice
* 기능 : 주사위를 굴려, move 할 눈금을 정한다
* last modified : 2019/02/25
* 수정자 : 박희완
*/

int throwDice(int twice) {
	int dice1;
	int dice2;

	srand((unsigned int)time(NULL));

	//여기다넣으면된다//
	
	printf("Enter를 누르시면 주사위를 굴립니다\n");
	while (getchar() != '\n');
	
	while (1) {
		dice1 = rand() % DICE_COUNT + 1;
		dice2 = rand() % DICE_COUNT + 1;
		gui_dice(dice1, dice2);
		fflush(stdin);
		Sleep(60);
		if (kbhit()) {
			fflush(stdin);
			setCursor(64, 28);
//			printf("%d칸 이동합니다\n", dice1 + dice2);
			break;
		}
	}


	if (twice != 1) {
		move_location = dice1 + dice2;
	}
	else {
		move_location += (dice1 + dice2);
	}
	
	printf("Dice 1 : %d\tDice 2 : %d\n", dice1, dice2);
	
	
	printf("총 이동 거리는 %d 입니다\n", move_location);
	if (dice1 == dice2)
		return 2;
	else
		return 1;

	return 0;
}

/*
* 함수 이름 : movePlayer
* return : int 옮긴 다음의 player의 location을 return
* 인자 : int move_location
* 기능 : move_location에 따라 player의 location을 옮긴다
* last modified : 2019/02/22
* 수정자 : 박희완
*/

int movePlayer(int move) {
	int move_count = move;
	int player_location;
	int i;
	Nation * find;

	find = findLocation(city, "Start");

	player_location = getPlayerLocation(p_turn);


	// 좀 더 코드의 최적화가 필요하다

	if (move_count < 0) {
		move_count = -move_count;
		for (i = 0; i < move_count; i++) {
			if (player_location == 0) {
				setPlayerLocation(p_turn, 27);			// 맨 끝쪽으로 보낸다
			}
			else
				setPlayerLocation(p_turn, --player_location);
			player_location = getPlayerLocation(p_turn);
			if (player_location == getNationLocationNum(find)) { //start지점이면, 월급 준다
				int sal = getBankMoney(bank);
				if (sal - SALARY < 0)
					continue;
				else
					setBankMoney(bank, (getBankMoney(bank) - SALARY));
				setPlayerMoney(p_turn, getPlayerMoney(p_turn) + SALARY);
				
				printf("%s에게 월급 %d 이 이 지급되었습니다\n", getPlayerName(p_turn), SALARY);
			}
		}
	}
	else {
		for (i = 0; i < move_count; i++) {
//			setPlayerLocation(p_turn, ++player_location % BOARD_SIZE);
			setPlayerLocation(p_turn, ++player_location % 28);
			player_location = getPlayerLocation(p_turn);
			
			if (player_location == getNationLocationNum(find)) { //start지점이면, 월급 준다
				int sal = getBankMoney(bank);
				if (sal - SALARY < 0)
					continue;
				else
					setBankMoney(bank, (getBankMoney(bank) - SALARY));
				setPlayerMoney(p_turn, getPlayerMoney(p_turn) + SALARY);
				
				printf("%s에게 월급 %d 이 이 지급되었습니다\n", getPlayerName(p_turn), SALARY);
			}
		}
	}

	return player_location;
}

/*
* 함수 이름 : movePlayerByName
* return : int 옮긴 다음의 player의 location을 return. 실패시 -1
* 인자 : char * name
* 기능 : name에 해당하는 장소로 player를 옮긴다
* last modified : 2019/02/21
* 수정자 : 박희완
*/

int movePlayerByName(char * name) {
	int move_count = move_location;
	Nation * go;
	int player_location;
	// 수정 필요
//	go = findLocation(city, name);

//	movePlayer(go->location_num - p_turn->location);
	

	go = 0;	//임시
//	if (!setPlayerLocation(p_turn, go))
//		return -1;
	return go;
}
