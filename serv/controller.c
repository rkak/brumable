/*********************************
* ���� �̸� : controller.c
* ��� : controller ��� ����
* last modified : 2019/02/25
* ������ : �����
**********************************/

#include <time.h>

#include "controller.h"
#include "common.h"
#include "action_controller.h"
#include "chanceCard_action_controller.h"
#include "bank.h"
#include "gui.h"


// information ����ϴ� �κп� ��Ȯ�� ��µǵ��� �ϴ� �Լ��� ���� ����
//#define infoPrintf(str) setCursor(info_print_cursor_x, info_print_cursor_y++); printf(str)


static int turn;
static int move_location;

int player_num;
int info_print_cursor_x = 23;
int info_print_cursor_y = 9;
 
extern int player_num;

Player **p;
Player * p_turn;	// ���� turn�� player
Nation ** city;
ChanceCard ** cc;
Bank * bank;

/*
* �Լ� �̸� : bitmable
* return : void
* ���� : void
* ��� : ��ü���� game�� flow ����
* last modified : 2019/02/25
* ������ : �����
*/

void bitmable(void) {
	int player_status;

	gui_loading_display();	

	int return_n = gui_menu_choice();	
	
	if (return_n != 0) {	
		return 0;
	}
	mableInit();

	//�÷��̾� ��������� ���� ���� �� ���� -> �÷��̾ �Ǿȿ� ǥ�� �Ǿ����
	system("cls");


	turnInit();         //�� �־�����
						//ǥ�� �ʿ� (START����)

	while (1) {
		removeCursor();
		info_print_cursor_y = 9;
		system("cls");
		gui_map_Init(city); //�ʱ׷�����

		// system("cls");

		/*
		printf("�� ������ �����Դϴ�\n");
		for (int i = 0; i < CITY_COUNT; i+=2) {
			printf("%10s : %10s\t", getNationName(city[i]), getNationOwner(city[i]));
			printf("%10s : %10s\n", getNationName(city[i+1]), getNationOwner(city[i+1]));
		}
		*/

		
		WHITE;
		SetInfoCursor();
		
		printf("player �����Դϴ�\n");
		for (int i = 0; i < player_num; i++) {
			SetInfoCursor();
			printf("%10s : %10d", getPlayerName(p[i]), getPlayerMoney(p[i]));
		}
		puts("");

		SetInfoCursor();
		printf("bank �����Դϴ�\n");

		SetInfoCursor();
		printf("%10d : %10d\n", getBankMoney(bank), getFundMoney(bank));

		chooseTurn();

		SetInfoCursor();
		printf("%s�� ���Դϴ�\n", getPlayerName(p_turn));

		player_status = checkPlayer();
		

		if (player_status == -1) {
			continue;
		}
		else if (player_status == STAT_DESERTISLAND) {
			int player_break_turn = getPlayerBreakTurn(p_turn);
			if (throwDice(0) == 2 || player_break_turn <= 0) {	// �� �ֻ��� double �� return 2
				// test �ʿ�
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
			char player_want_place[20]; // �ӽ�
			Nation * target;		// �̵��ϰ��� �ϴ� ����

			SetInfoCursor();
			printf("���ϴ� ��Ҹ� �Է��ϼ��� : ");

			scanf("%s", player_want_place); getchar();
			target = findLocation(city, player_want_place);
			if (target == NULL)
				return 0;

			SetInfoCursor();
			printf("%s�� �̵��մϴ�", getNationName(target));

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
			if (throwDice(0) == 2) {	// ���� double�� �Ͼ�ٸ�
				while (getchar() != '\n');

				//infoPrintf("double! �ѹ� �� ��������\n");
				SetInfoCursor();
				printf("double! �ѹ� �� ��������\n");
				throwDice(1);
			}
			while (getchar() != '\n');
		}
		
		// nation�� ���� �׽�Ʈ �� �̰����� move_location ����

		movePlayer(move_location);

		action();

		while (getchar() != '\n');

		/*if (exit())
			break;*/
	}
}

/*
* �Լ� �̸� : mableInit
* return : void
* ���� : void
* ��� : mable game�� init ����, ��� ������ init�� ����
* last modified : 2019/02/25
* ������ : �����
*/

void mableInit(void) {
	system("cls");

	makeNations();
	makeCCs();
	makeBanks();
	makePlayers();
}

/*
* �Լ� �̸� : setPlayerNum
* return : int. ������ 1, ���н� 0
* ���� : void
* ��� : player �� ���� �� Player ** p�� �޸� �Ҵ�
* last modified : 2019/02/25
* ������ : �����
*/


int setPlayerNum(void) {
	YELLOW;
	//setCursor(22, 12);
	puts("Player ���� �Է��Ͻÿ�");
	//setCursor(22, 13);
	puts("-----------------------");
	setCursor(3, 3);
	//setCursor(25, 15);
	printf("��");
	setCursor(1, 3);
	//setCursor(23, 15);
	viewCursor();
	scanf("%d", &player_num); getchar();

	p = (Player **)malloc(sizeof(Player *) * player_num);	// Player ������ �迭 �����
	if (p == NULL)
		return 0;
	return 1;
}

/*
* �Լ� �̸� : makePlayers
* return : void
* ���� : void
* ��� : player ���� ���ϰ�, �� player���� �޸� �Ҵ� �� �̸� ����
* last modified : 2019/02/25
* ������ : �����
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
		printf("�� �̸��� �Է��Ͻÿ�");
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

		// ���� �� ���� ���� �ڵ�� ��ü.

		//if(i==0) {
		//	RED;
		//	//setCursor(22, 18);
		//	printf("Player %d", i + 1);
		//	YELLOW;
		//	printf("�� �̸��� �Է��Ͻÿ�");
		//	//setCursor(22, 19);
		//	puts("----------------------------");
		//	//setCursor(22, 21);
		//	RED;
		//	viewCursor();
		//	scanf("%s", name); getchar();
		//	p[i] = makePlayer(name);
		//}
		//else if (i == 1) {
		//	BLUE;
		//	//setCursor(22, 24);
		//	printf("Player %d", i + 1);
		//	
		//	//setCursor(22, 27);
		//	BLUE;
		//	
		//}
		//else if (i == 2) {
		//	HIGH;
		//	//setCursor(22,30);
		//	printf("Player %d", i + 1);
		//	YELLOW;
		//	printf("�� �̸��� �Է��Ͻÿ�");
		//	//setCursor(22, 31);
		//	puts("----------------------------");
		//	//setCursor(22, 33);
		//	HIGH;
		//	viewCursor();
		//	scanf("%s", name); getchar();
		//	p[i] = makePlayer(name);
		//}
		//else if (i == 3) {
		//	SKY;
		//	//setCursor(22, 36);
		//	printf("Player %d", i + 1);
		//	YELLOW;
		//	printf("�� �̸��� �Է��Ͻÿ�");
		//	//setCursor(22, 37);
		//	puts("----------------------------");
		//	//setCursor(22, 39);
		//	SKY;
		//	viewCursor();
		//	scanf("%s", name); getchar();
		//	p[i] = makePlayer(name);
		//}

	}
}

/*
* �Լ� �̸� : makeCCs
* return : void
* ���� : void
* ��� : CC�� ����� �޸� �Ҵ� �� init
* last modified : 2019/02/23
* ������ : �����
*/

void makeCCs(void) {
	char * ccName[20] = {
		"����� �޽�", "����", "���޹޴³�", "d", "e", "f", "g", "h", "i", "j"
	};
	char * ccExplain[100] = {
		"���ε��� �̵�", "���� ����", "Start �������� �̵�", "D", "E", "F", "G", "H", "I", "J"
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
* �Լ� �̸� : makeNations
* return : void
* ���� : void
* ��� : nation�� ����� �޸� �Ҵ� �� init
* last modified : 2019/02/24
* ������ : ������
*/

void makeNations(void) {
	//ù��° start���� chanceCard_action_controller.c�� ����ī�� start �� ���� �Ͻ� �� ���Ƽ� �̸� Start�� �س����~
	/*
int moveToStart(void * p) {
	p = (Player *)p;
	return movePlayerByName("Start");
}*/
	char city_name[][20] = { { "Start" },{ "����" },{ "���ݳ���" },{ "����" },{ "����" },{ "���Һ�" },{ "�ͻ�" },{ "����" },{ "���ε�" }, //��������
	{ "����" },{ "����" },{ "�뱸" },{ "����ī��" },{ "â��" },{ "���ϼ���" },
	{ "���" },{ "�λ�" },{ "�ްԼ�" },{ "����" },{ "����" },{ "����ī��" },{ "����" },{ "KTX" },
	{ "û��" },{ "õ��" },{ "��õ" },{ "���õ��" },{ "����" } };

	//int price[CITY_COUNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
	//	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	//	21, 22, 23, 24, 25, 26, 27, 28
	//};

	/*���ݳ��� �ǹ�X�����̶� ������ �ϴ�0�����߰� ���ݳ��ΰ����� �ǹ�X8���� �����س���� ���۰���250�������� �� �����̰�
	  ���õ��� 15�������� ���߾��~ �׹ۿ��� Ư���Ѱ��� �� 0������ �س����
	  �ްԼ� = 0���̰� �ѹ� ���ٰ��� ��
	*/
	int price[CITY_COUNT] = {0,5,0,8,8,0,12,12,0,
		14,16,16,0,18,0,
		22,28,0,24,26,0,26,0,
		30,32,32,0,35
	};



	/* 
	���ݳ��� -> KIND_FUND �ε� RECEIVE X BANK�� �� ����
	���Һ� -> KIND_CHNACECARD�� ó���ص� �Ǵ���
	�ްԼ� -> KIND_CITY �� 0�� �ϸ� �� �� ����
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
* �Լ� �̸� : turnInit
* return : int. �ش� turn return
* ���� : void
* ��� : �� ó�� turn���� ������ ��� ���ϱ�
* last modified : 2019/02/22
* ������ : �����
*/

int turnInit(void) {
	int t = -1;


	turn = t;
	return t;
}

/*
* �Լ� �̸� : makeBanks
* return : void
* ���� : void
* ��� : bank ����
* last modified : 2019/02/23
* ������ : �����
*/

void makeBanks(void) {
	int bank_money = 1000000;
	int fund_money = 0;
	bank = makeBank(bank_money, fund_money);
}

/*
* �Լ� �̸� : chooseTurn
* return : int. �ش� turn return
* ���� : void
* ��� : �� �ϸ��� � player ���������� ����
* last modified : 2019/02/21
* ������ : �����
*/

int chooseTurn(void) {
	srand((unsigned int)time(NULL));
	turn = (++turn) % player_num;
	p_turn = p[turn];

	for (int i = 0; i < player_num; i++) { // ��� player�� turn �ʱ�ȭ
		losePlayerTurn(p[i]);
	}
	givePlayerTurn(p_turn);	// ������ player�� turn ����

	return turn;
}

/*
* �Լ� �̸� : checkPlayer
* return : int
* ���� : void
* ��� : player�� ��������, �ش� player�� ���¸� ����
* last modified : 2019/02/21
* ������ : �����
*/

int checkPlayer(void) {
	switch (getPlayerStatus(p_turn)) {
	case STAT_GAMING:	// �������� player

		return STAT_GAMING;
	case STAT_FAIL:		// �Ļ��� player

		return -1;
	case STAT_WINNER:	// �̹� �̱� player

		return -1;
	case STAT_DESERTISLAND:	// ���ε��� �ִ� player

		return -1;
	case STAT_TRAVEL:	// ���ֿ����� �ؾ� �ϴ� player

		return STAT_TRAVEL;
	}
	return -1;
}

/*
* �Լ� �̸� : throwDice
* return : int double�̸� 2, �����̸� 1, ���н� 0
* ���� : int twice
* ��� : �ֻ����� ����, move �� ������ ���Ѵ�
* last modified : 2019/02/25
* ������ : �����
*/

int throwDice(int twice) {
	int dice1;
	int dice2;

	srand((unsigned int)time(NULL));

	//����ٳ�����ȴ�//
	SetInfoCursor();
	printf("Enter�� �����ø� �ֻ����� �����ϴ�\n");
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
//			printf("%dĭ �̵��մϴ�\n", dice1 + dice2);
			break;
		}
	}


	if (twice != 1) {
		move_location = dice1 + dice2;
	}
	else {
		move_location += (dice1 + dice2);
	}
	SetInfoCursor();
	printf("Dice 1 : %d\tDice 2 : %d\n", dice1, dice2);
	
	SetInfoCursor();
	printf("�� �̵� �Ÿ��� %d �Դϴ�\n", move_location);
	if (dice1 == dice2)
		return 2;
	else
		return 1;

	return 0;
}

/*
* �Լ� �̸� : movePlayer
* return : int �ű� ������ player�� location�� return
* ���� : int move_location
* ��� : move_location�� ���� player�� location�� �ű��
* last modified : 2019/02/22
* ������ : �����
*/

int movePlayer(int move_location) {
	int move_count = move_location;
	int player_location;
	int i;
	Nation * find;

	find = findLocation(city, "Start");

	player_location = getPlayerLocation(p_turn);


	// �� �� �ڵ��� ����ȭ�� �ʿ��ϴ�

	if (move_count < 0) {
		move_count = -move_count;
		for (i = 0; i < move_count; i++) {
			if (player_location == 0) {
				setPlayerLocation(p_turn, 27);			// �� �������� ������
			}
			else
				setPlayerLocation(p_turn, --player_location);
			player_location = getPlayerLocation(p_turn);
			if (player_location == getNationLocationNum(find)) { //start�����̸�, ���� �ش�
				int sal = getBankMoney(bank);
				if (sal - SALARY < 0)
					continue;
				else
					setBankMoney(bank, (getBankMoney(bank) - SALARY));
				setPlayerMoney(p_turn, getPlayerMoney(p_turn) + SALARY);
				SetInfoCursor();
				printf("%s���� ���� %d �� �� ���޵Ǿ����ϴ�\n", getPlayerName(p_turn), SALARY);
			}
		}
	}
	else {
		for (i = 0; i < move_count; i++) {
//			setPlayerLocation(p_turn, ++player_location % BOARD_SIZE);
			setPlayerLocation(p_turn, ++player_location % 28);
			player_location = getPlayerLocation(p_turn);
			
			if (player_location == getNationLocationNum(find)) { //start�����̸�, ���� �ش�
				int sal = getBankMoney(bank);
				if (sal - SALARY < 0)
					continue;
				else
					setBankMoney(bank, (getBankMoney(bank) - SALARY));
				setPlayerMoney(p_turn, getPlayerMoney(p_turn) + SALARY);
				SetInfoCursor();
				printf("%s���� ���� %d �� �� ���޵Ǿ����ϴ�\n", getPlayerName(p_turn), SALARY);
			}
		}
	}

	return player_location;
}

/*
* �Լ� �̸� : movePlayerByName
* return : int �ű� ������ player�� location�� return. ���н� -1
* ���� : char * name
* ��� : name�� �ش��ϴ� ��ҷ� player�� �ű��
* last modified : 2019/02/21
* ������ : �����
*/

int movePlayerByName(char * name) {
	int move_count = move_location;
	Nation * go;
	int player_location;
	// ���� �ʿ�
//	go = findLocation(city, name);

//	movePlayer(go->location_num - p_turn->location);
	

	go = 0;	//�ӽ�
//	if (!setPlayerLocation(p_turn, go))
//		return -1;
	return go;
}