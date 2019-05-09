
/*********************************
* ÆÄÀÏ ÀÌ¸§ : gui.c
* ±â´É : ºÎ·ç¸¶ºíÀÇ ¸ðµç gui ÇÔ¼ö ¼±¾ð
* last modified : 2019/02/24
* ¼öÁ¤ÀÚ : ±¸Á¾¼®
**********************************/

//setCursor(18, 9);
//printf("ÁÂÃø»ó´Ü¸ð¼­¸®");
//setCursor(112, 9);
//printf("¿ìÃø»ó´Ü¸ð¼­¸®");

//setCursor(18, 47);
//printf("ÁÂÃøÇÏ´Ü¸ð¼­¸®");
//setCursor(112, 47);
//printf("¿ìÃøÇÏ´Ü¸ð¼­¸®");

#include "gui.h"
#include "nation.h"
#include "player.h"

extern Player **p;
extern int player_num;

extern Player * p_turn;

void removeCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void viewCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 100;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void setCursor(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//·Îµù È­¸é
void gui_loading_display() {
	system("mode con lines=25 cols=120"); // È­¸é Å©±â ¼³Á¤

	removeCursor(); WHITE;
	setCursor(6, 1); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á");
	setCursor(6, 2); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á                ¡á¡á");
	setCursor(6, 3); printf("¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	setCursor(6, 4); printf("¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	setCursor(6, 5); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á                ¡á¡á");
	setCursor(6, 6); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡á¡á ¡¡¡¡           ¡á¡á");
	setCursor(6, 7); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	setCursor(6, 8); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	setCursor(6, 9); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	setCursor(6, 10); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	setCursor(6, 11); printf("¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	setCursor(6, 12); printf("¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	setCursor(6, 13); printf("¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	setCursor(6, 14); printf("¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	setCursor(6, 15); printf("¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡");
	setCursor(6, 16); printf("¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡");
	setCursor(6, 17); printf("¡Ú¡Ù¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡Ù¡Ú¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡");
	setCursor(6, 18); printf("¡Ù¡Ú¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡Ú¡Ù¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡");
	setCursor(6, 19); printf("¡Ú¡Ù¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡Ù¡Ú¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡");
	setCursor(6, 20); printf("¡Ù¡Ú¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡Ú¡Ù¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡");
	setCursor(6, 21); printf("¡Ú¡Ù¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡Ù¡Ú¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	setCursor(6, 22); printf("¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡");
	setCursor(6, 23); printf("¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡Ù¡Ú¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡");

	//press any key..
	setCursor(36, 19); YELLOW;
	while (1)
	{
		printf("¾Æ¹«Å°³ª ´©¸£¼¼¿ä!");
		Sleep(500);
		if (kbhit()) {
			setCursor(36, 19);
			printf("                  ");
			setCursor(42, 18);
			printf("°ÔÀÓ ½ÃÀÛ");
			setCursor(42, 20);
			printf("°ÔÀÓ Á¾·á");
			break;
		}
		setCursor(36, 19);
		printf("                  ");
		Sleep(500);
		setCursor(36, 19);
	}

}

//¸Þ´º ¼±ÅÃ °ÔÀÓÀ» ½ÃÀÛÇÒÁö ¹Ù·Î Á¾·áÇÒÁö
int gui_menu_choice() {
	//°ÔÀÓ½ÃÀÛ / °ÔÀÓÁ¾·á
	int return_n = 0;

	while (1) //Å°º¸µå ¿òÁ÷ÀÓ
	{
		int key;
		if (kbhit())
		{
			key = getch();
			if (key == 224 || key == 0)
			{
				key = getch();
				switch (key)
				{
				case 72: //»ó
					setCursor(38, 18 + return_n);
					printf("  ");
					return_n -= 2;
					if (return_n < 0) return_n = 0;
					setCursor(38, 18 + return_n);
					printf("¢º");
					break;
				case 80: //ÇÏ
					setCursor(38, 18 + return_n);
					printf("  ");
					return_n += 2;
					if (return_n > 2) return_n = 2;
					setCursor(38, 18 + return_n);
					printf("¢º");
					break;
				default:
					break;
				}
			}
			else
				if (key == 13)//¿£ÅÍ
					return return_n;
		}
	}
}


/*
 *
 *
 * last modified : 2018/02/25
 * ¼öÁ¤ÀÚ : ¹ÚÈñ¿Ï
 */

// ºÎ·ç¸¶ºí ¸Ê ±×¸®´Â ÇÔ¼ö
void gui_map_Init(Nation **city)
{
	int x, y;
	system("mode con lines=56 cols=144"); //8X7 ==¼¼·Î7Ä­  16X9 // °¡·Î9Ä­

										  //ºÎ·ç¸¶ºí ¸Ê °¡·ÎÁÙ ¦¬
	WHITE;
	for (x = 0; x <= 143; x++) {

		setCursor(x, 8);	//  °¡·ÎÁÙ À­ÂÊ ¸Ê
		printf("¦¬");

		if (x < 17 || x>126) {

			setCursor(x, 16);
			printf("¦¬");

			setCursor(x, 24);
			printf("¦¬");

			setCursor(x, 32);
			printf("¦¬");

			setCursor(x, 40);
			printf("¦¬");
		}

		setCursor(x, 48);	// °¡·ÎÁÙ ¾Æ·§ÂÊ ¸Ê
		printf("¦¬");

	}

	////ºÎ·ç¸¶ºÒ ¸Ê ¼¼·ÎÁÙ ¦­  //°¡·ÎÁÙ°ú ¼¼·ÎÁÙÀÌ ¸¸³ª´Â °æ¿ì ±ò²ûÇÏ°Ô ¼öÁ¤ => ¦§¦©¦ª¦¨¦«'
	for (y = 0; y <= 55; y++) {

		setCursor(16, y);
		printf("¦­");

		if (y < 8 || y>48)
		{
			setCursor(31, y);
			printf("¦­");
			setCursor(47, y);
			printf("¦­");
			setCursor(63, y);
			printf("¦­");
			setCursor(79, y);
			printf("¦­");
			setCursor(95, y);
			printf("¦­");
			setCursor(111, y);
			printf("¦­");
			setCursor(126, y);
			printf("¦­");
		}

		if (y == 8) {
			setCursor(16, y);
			printf("¦¶");
			setCursor(31, y);
			printf("¦µ");
			setCursor(47, y);
			printf("¦µ");
			setCursor(63, y);
			printf("¦µ");
			setCursor(79, y);
			printf("¦µ");
			setCursor(95, y);
			printf("¦µ");
			setCursor(111, y);
			printf("¦µ");
			setCursor(126, y);
			printf("¦¶");
		}

		if (y == 16 || y == 24 || y == 32 || y == 40) {
			setCursor(16, y);
			printf("¦´");
		}

		if (y == 48) {
			setCursor(16, y);
			printf("¦¶");
			setCursor(31, y);
			printf("¦³");
			setCursor(47, y);
			printf("¦³");
			setCursor(63, y);
			printf("¦³");
			setCursor(79, y);
			printf("¦³");
			setCursor(95, y);
			printf("¦³");
			setCursor(111, y);
			printf("¦³");
			setCursor(126, y);
			printf("¦¶");
		}

		setCursor(126, y);
		printf("¦­");

	}
	int i;
	int a = 0, b = 0, c = 0;
	int cursor_x, cursor_y;

	for (i = 0; i < 28; i++) {

		if (i < 9) {
			// setCursor(132 - (i * 15.9), 50);
			cursor_x = 132 - (i * 15.9);
			cursor_y = 50;
			//			printf("%s", city[i]->name);
		}
		else if (i >= 9 && i < 14) {
			// setCursor(5, 42-(a*8));
			cursor_x = 5;
			cursor_y = 42 - (a * 8);
			//			printf("%s", city[i]->name);
			a++;
		}
		else if (i >= 14 && i < 23) {
			// setCursor(4+(b*16.3), 1);
			cursor_x = 4 + (b*16.3);
			cursor_y = 1;
			//			printf("%s", city[i]->name);
			b++;
		}

		if (i >= 23 && i < 28) {
			// setCursor(132,10+(c*8));
			cursor_x = 132;
			cursor_y = 10 + (c * 8);
			//			printf("%s", city[i]->name);
			c++;
		}
		WHITE;
		setCursor(cursor_x, cursor_y);
		printf("%s", city[i]->name);
		for (int k = 0; k < player_num; k++) {
			if (i == getPlayerLocation(p[k])) {
				switch (k) {
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
				setCursor(cursor_x, cursor_y + k + 1);
				printf("¡Ú");
			}
		}

	}
}


void gui_bokbulbok(int com, int user) {

	YELLOW;
	setCursor(58, 11); printf("º¹ºÒº¹ °¡À§¹ÙÀ§º¸ ´ë°á");
	setCursor(50, 13); printf("ÀÌ±â¸é 100¸¸¿ø ºñ±â¸é 0¿ø Áö¸é -50¸¸¿ø");
	setCursor(63, 15); printf("PRESS ENTER");


	if (com == 0) {
		RED;
		setCursor(35, 18);  printf("C O M");
		setCursor(35, 20); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 21); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 22); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 23); printf("          rU1s1RHG7SBSIZF¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 24); printf("     rMu1BW.  Mu   M;   )M;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 25); printf("     DD B:   M.   B;      M:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 26); printf("    :M .B   r2 PW$rnf&aH;   M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 27); printf("    R_ vE   M.B.       :LOrx$¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 28); printf("    R  .B   D.rZ          :M_8¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 29); printf("   :R   B,  :B .Uxc;;        Mr¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 30); printf("   :M)   B   $1   MON         H¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 31); printf("   HLUD  D0;.xfrB8E.          D.¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 32); printf("   #r  :B27 ;i. Dx            M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 33); printf("    B          Z.           .Mi¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 34); printf("        M       M.         FR<:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 35); printf("        Dr     :8       UNp;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 36); printf("         B,    :x      GM¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 37); printf("         .BU         :B0¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 38); printf("           :cLi:::;rL)¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 39); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	}

	else if (com == 1) {
		RED;
		setCursor(35, 18);  printf("C O M");
		setCursor(35, 20);  printf("         .BMG        ri¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 21); printf("       R  :R       L1:;K_¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 22); printf("      B.  M7     HM     B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 23); printf("       B   1X    .M     iM¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 24); printf("      Br   .B    M;   .M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 25); printf("      .B    B   uR    B;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 26); printf("       M;   B:  B    :B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 27); printf("        rD .M  B.     M7¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 28); printf(" . .RFL8B.;:;B8W      B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 29); printf("LR3JB   HW::::x7SEu.. B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 30); printf(".M   M_    B      :D4ME¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 31); printf(".B  ;M    LML.        .8:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡:");
		setCursor(35, 32); printf(" M:  BI     ;BILu8      8:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 33); printf("  M_   B     M  7M      UH:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 34); printf("  BMr  :BriHW  7M       0x:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 35); printf("  KrrKU8:;:    r.      ,M:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 36); printf("   M                  .M,:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 37); printf("   :B.               1M.¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 38); printf("    ,MW;           .uB1¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 39); printf("      7j7::..:mm:rJL¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	}

	else if (com == 2) {
		RED;
		setCursor(35, 18);  printf("C O M");
		setCursor(35, 20); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 21); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 22); printf("        '     ZM8¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 23); printf("       :rn    R  p¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 24); printf("      MG B:  uP  N   DEu¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 25); printf("      )( .D  DC .B  MG B;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 26); printf("iCDE   D  B  M: rP MU :M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 27); printf("M  :D  M  R; 0, A.LR  8¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 28); printf("DP   B D;  DM   KGM  Mr¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 29); printf(" Rt   B0;        ,  DU¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 30); printf("  BL   :     )#    )0¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 31); printf("   Bo    :JDRT.PMGOjN: :XCF;Q¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 32); printf("   :BJ$Urul   Mr     EXU    H;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 33); printf("    M        M.         FXix:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 34); printf("    Dr      :8       UNp;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 35); printf("     B,     :x      GM¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 36); printf("     .BU          :B0¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 37); printf("       :cLi:::;rL)¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 38); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(35, 39); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	}



	if (user == 0) {
		BLUE;
		setCursor(75, 18); printf("P L A Y E A R");
		setCursor(75, 20); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 21); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 22); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 23); printf("          rU1s1RHG7SBSIZF¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 24); printf("     rMu1BW.  Mu   M;   )M;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 25); printf("     DD B:   M.   B;      M:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 26); printf("    :M .B   r2 PW$rnf&aH;   M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 27); printf("    R_ vE   M.B.       :LOrx$¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 28); printf("    R  .B   D.rZ          :M_8¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 29); printf("   :R   B,  :B .Uxc;;        Mr¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 30); printf("   :M)   B   $1   MON         H¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 31); printf("   HLUD  D0;.xfrB8E.          D.¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 32); printf("   #r  :B27 ;i. Dx            M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 33); printf("    B          Z.           .Mi¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 34); printf("        M       M.         FR<:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 35); printf("        Dr     :8       UNp;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 36); printf("         B,    :x      GM¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 37); printf("         .BU         :B0¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 38); printf("           :cLi:::;rL)¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 39); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	}

	else if (user == 1) {
		BLUE;
		setCursor(75, 18); printf("P L A Y E A R");
		setCursor(75, 20);  printf("         .BMG        ri¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 21); printf("       R  :R       L1:;K_¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 22); printf("      B.  M7     HM     B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 23); printf("       B   1X    .M     iM¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 24); printf("      Br   .B    M;   .M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 25); printf("      .B    B   uR    B;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 26); printf("       M;   B:  B    :B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 27); printf("        rD .M  B.     M7¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 28); printf(" . .RFL8B.;:;B8W      B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 29); printf("LR3JB   HW::::x7SEu.. B¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 30); printf(".M   M_    B      :D4ME¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 31); printf(".B  ;M    LML.        .8::¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 32); printf(" M:  BI     ;BILu8      8:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 33); printf("  M_   B     M  7M      UH:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 34); printf("  BMr  :BriHW  7M       0x:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 35); printf("  KrrKU8:;:    r.      ,M:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 36); printf("   M                  .M,:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 37); printf("   :B.               1M.¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 38); printf("    ,MW;           .uB1¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 39); printf("      7j7::..:mm:rJL¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	}

	else if (user == 2) {
		BLUE;
		setCursor(75, 18); printf("P L A Y E A R");
		setCursor(75, 20); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 21); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 22); printf("        '     ZM8¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 23); printf("       :rn    R  p¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 24); printf("      MG B:  uP  N   DEu¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 25); printf("      )( .D  DC .B  MG B;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 26); printf("iCDE   D  B  M: rP MU :M¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 27); printf("M  :D  M  R; 0, A.LR  8¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 28); printf("DP   B D;  DM   KGM  Mr¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 29); printf(" Rt   B0;        ,  DU¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 30); printf("  BL   :     )#    )0¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 31); printf("   Bo    :JDRT.PMGOjN: :XCF;Q¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 32); printf("   :BJ$Urul   Mr     EXU    H;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 33); printf("    M        M.         FXix:¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 34); printf("    Dr      :8       UNp;¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 35); printf("     B,     :x      GM¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 36); printf("     .BU          :B0¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 37); printf("       :cLi:::;rL)¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 38); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
		setCursor(75, 39); printf("          ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡");
	}
}

void gui_dice(int n1, int n2)
{
	int gui_dice_x = 75;

	WHITE;
//	setCursor(58, 19);
//	printf("°¡¿îµ¥");
	if (n1 == 1) {
		setCursor(gui_dice_x, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x, 14); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x, 15); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x, 16); printf("¢È    ¡Ü    ¢È\n");
		setCursor(gui_dice_x, 17); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x, 18); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n1 == 2) {
		setCursor(gui_dice_x, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 15); printf("¢È      ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 16); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 17); printf("¢È  ¡Ü      ¢È\n");
		setCursor(gui_dice_x, 18); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n1 == 3) {
		setCursor(gui_dice_x, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 15); printf("¢È      ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 16); printf("¢È  ¡¡¡Ü¡¡  ¢È\n");
		setCursor(gui_dice_x, 17); printf("¢È  ¡Ü  ¡¡  ¢È\n");
		setCursor(gui_dice_x, 18); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n1 == 4) {
		setCursor(gui_dice_x, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x, 14); printf("¢È  ¡¡  ¡¡  ¢È\n");
		setCursor(gui_dice_x, 15); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 16); printf("¢È    ¡¡¡¡¡¡¢È\n");
		setCursor(gui_dice_x, 17); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 18); printf("¢È      ¡¡  ¢È\n");
		setCursor(gui_dice_x, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}

	else if (n1 == 5) {
		setCursor(gui_dice_x, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 15); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 16); printf("¢È ¡¡ ¡Ü¡¡  ¢È\n");
		setCursor(gui_dice_x, 17); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 18); printf("¢È ¡¡¡¡¡¡¡¡ ¢È\n");
		setCursor(gui_dice_x, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}

	else if (n1 == 6) {
		setCursor(gui_dice_x, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 15); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 16); printf("¢È  ¡Ü¡¡¡Ü  ¢È\n");
		setCursor(gui_dice_x, 17); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x, 18); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	if (n2 == 1) {
		setCursor(gui_dice_x + 18, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x + 18, 14); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x + 18, 15); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x + 18, 16); printf("¢È    ¡Ü    ¢È\n");
		setCursor(gui_dice_x + 18, 17); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x + 18, 18); printf("¢È    ¡¡    ¢È\n");
		setCursor(gui_dice_x + 18, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n2 == 2) {
		setCursor(gui_dice_x + 18, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x + 18, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 15); printf("¢È      ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 16); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 17); printf("¢È  ¡Ü      ¢È\n");
		setCursor(gui_dice_x + 18, 18); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n2 == 3) {
		setCursor(gui_dice_x + 18, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x + 18, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 15); printf("¢È      ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 16); printf("¢È  ¡¡¡Ü¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 17); printf("¢È  ¡Ü  ¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 18); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n2 == 4) {
		setCursor(gui_dice_x + 18, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x + 18, 14); printf("¢È  ¡¡  ¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 15); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 16); printf("¢È    ¡¡¡¡¡¡¢È\n");
		setCursor(gui_dice_x + 18, 17); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 18); printf("¢È      ¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n2 == 5) {
		setCursor(gui_dice_x + 18, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x + 18, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 15); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 16); printf("¢È ¡¡ ¡Ü¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 17); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 18); printf("¢È ¡¡¡¡¡¡¡¡ ¢È\n");
		setCursor(gui_dice_x + 18, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
	else if (n2 == 6) {
		setCursor(gui_dice_x + 18, 13); printf("¢É¢Ç¢Ç¢Ç¢Ç¢Ç¢Ê\n");
		setCursor(gui_dice_x + 18, 14); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 15); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 16); printf("¢È  ¡Ü¡¡¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 17); printf("¢È  ¡Ü  ¡Ü  ¢È\n");
		setCursor(gui_dice_x + 18, 18); printf("¢È  ¡¡¡¡¡¡  ¢È\n");
		setCursor(gui_dice_x + 18, 19); printf("¢Ê¢Ç¢Ç¢Ç¢Ç¢Ç¢É\n");
	}
}

//void main() {
//
//
//	gui_loading_display();
//	int return_n = gui_menu_choice();
//
//	if (return_n != 0) {
//		return 0;
//	}
//	else
//	{
//		gui_map_Init();
//	}


//ÁÖ»çÀ§
/*	srand(time(NULL));
int dice1, dice2;
while (1) {
dice1 = rand() % 6 + 1;
dice2 = rand() % 6 + 1;
dice(dice1, dice2);
fflush(stdin);
Sleep(60);
if (kbhit()) {
fflush(stdin);
setCursor(64, 28);
printf("%dÄ­ ÀÌµ¿ÇÕ´Ï´Ù\n", dice1 + dice2);
break;
}
}*/

//°¡À§¹ÙÀ§º¸
/*
int userson, comson;
int i = 0;
while (1)
{
comson = rand() % 3;   //ÄÄÇ»ÅÍ°¡ ³¾ ¼Õ ·£´ý°ª
userson = rand() % 3; //À¯Àú°¡ ³¾ ¼Õ ·£´ý°ª
gui_bokbulbok(comson, userson);
fflush(stdin);
Sleep(30);
if (kbhit()) {
fflush(stdin);
if (userson == comson)
{
YELLOW;
setCursor(62, 41);
printf("¹« ½Â ºÎ $0 È¹µæ");
}
else if (comson == (userson + 1) % 3)
{
YELLOW;
setCursor(62, 41);
printf("½Â ¸® $100 È¹µæ");
}
else
{
YELLOW;
setCursor(62, 41);
printf("ÆÐ ¹è $50 Â÷°¨");
}
break;
}
}
*/
//}



