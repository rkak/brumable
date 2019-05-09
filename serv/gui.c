
/*********************************
* ���� �̸� : gui.c
* ��� : �η縶���� ��� gui �Լ� ����
* last modified : 2019/02/24
* ������ : ������
**********************************/

//setCursor(18, 9);
//printf("������ܸ𼭸�");
//setCursor(112, 9);
//printf("������ܸ𼭸�");

//setCursor(18, 47);
//printf("�����ϴܸ𼭸�");
//setCursor(112, 47);
//printf("�����ϴܸ𼭸�");

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

//�ε� ȭ��
void gui_loading_display() {
	system("mode con lines=25 cols=120"); // ȭ�� ũ�� ����

	removeCursor(); WHITE;
	setCursor(6, 1); printf("��ᡡ��������ᡡ����ᡡ������������ᡡ����������ᡡ����ᡡ��������ᡡ�����������������");
	setCursor(6, 2); printf("��ᡡ��������ᡡ����ᡡ������������ᡡ����������ᡡ����ᡡ���������                ���");
	setCursor(6, 3); printf("��������ᡡ����ᡡ����ᡡ��������������������ᡡ��������ᡡ����ᡡ�������������������");
	setCursor(6, 4); printf("��������ᡡ����ᡡ������������ᡡ����ᡡ��������ᡡ����ᡡ�������������������");
	setCursor(6, 5); printf("��ᡡ��������ᡡ����ᡡ������������ᡡ����ᡡ��������ᡡ����ᡡ���������                ���");
	setCursor(6, 6); printf("��ᡡ��������ᡡ����ᡡ����ᡡ��������������������ᡡ��������ᡡ������ᡡ����� ����           ���");
	setCursor(6, 7); printf("��ᡡ��������ᡡ����ᡡ������������ᡡ����ᡡ��������ᡡ������ᡡ���������������");
	setCursor(6, 8); printf("��ᡡ��������ᡡ����ᡡ������������ᡡ����ᡡ��������ᡡ����ᡡ�������������������");
	setCursor(6, 9); printf("��ᡡ��������ᡡ����ᡡ����������������������������ᡡ��������ᡡ����ᡡ������������������������������");
	setCursor(6, 10); printf("��ᡡ��������ᡡ����ᡡ����������������������������ᡡ��������ᡡ����ᡡ������������������������������");
	setCursor(6, 11); printf("��ᡡ��������ᡡ����ᡡ����������������������������ᡡ��������ᡡ����ᡡ�������������������");
	setCursor(6, 12); printf("��������ᡡ����ᡡ������������ᡡ����������ᡡ����ᡡ�������������������");
	setCursor(6, 13); printf("��������ᡡ����ᡡ������������ᡡ����������ᡡ����ᡡ��������������������������������");
	setCursor(6, 14); printf("��������������������������������������������������������������������������������������������������������������");
	setCursor(6, 15); printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�����������������ᡡ");
	setCursor(6, 16); printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�����������������ᡡ");
	setCursor(6, 17); printf("�ڡ١����������������������������������������������������������������������١ڡ���������������������������ᡡ");
	setCursor(6, 18); printf("�١ڡ����������������������������������������������������������������������ڡ١���������������������������ᡡ");
	setCursor(6, 19); printf("�ڡ١����������������������������������������������������������������������١ڡ�����������������ᡡ");
	setCursor(6, 20); printf("�١ڡ����������������������������������������������������������������������ڡ١�����������������ᡡ");
	setCursor(6, 21); printf("�ڡ١����������������������������������������������������������������������١ڡ�������ᡡ��������������������");
	setCursor(6, 22); printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�����������������ᡡ");
	setCursor(6, 23); printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�����������������ᡡ");

	//press any key..
	setCursor(36, 19); YELLOW;
	while (1)
	{
		printf("�ƹ�Ű�� ��������!");
		Sleep(500);
		if (kbhit()) {
			setCursor(36, 19);
			printf("                  ");
			setCursor(42, 18);
			printf("���� ����");
			setCursor(42, 20);
			printf("���� ����");
			break;
		}
		setCursor(36, 19);
		printf("                  ");
		Sleep(500);
		setCursor(36, 19);
	}

}

//�޴� ���� ������ �������� �ٷ� ��������
int gui_menu_choice() {
	//���ӽ��� / ��������
	int return_n = 0;

	while (1) //Ű���� ������
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
				case 72: //��
					setCursor(38, 18 + return_n);
					printf("  ");
					return_n -= 2;
					if (return_n < 0) return_n = 0;
					setCursor(38, 18 + return_n);
					printf("��");
					break;
				case 80: //��
					setCursor(38, 18 + return_n);
					printf("  ");
					return_n += 2;
					if (return_n > 2) return_n = 2;
					setCursor(38, 18 + return_n);
					printf("��");
					break;
				default:
					break;
				}
			}
			else
				if (key == 13)//����
					return return_n;
		}
	}
}


/*
 *
 *
 * last modified : 2018/02/25
 * ������ : �����
 */

// �η縶�� �� �׸��� �Լ�
void gui_map_Init(Nation **city)
{
	int x, y;
	system("mode con lines=56 cols=144"); //8X7 ==����7ĭ  16X9 // ����9ĭ

										  //�η縶�� �� ������ ��
	WHITE;
	for (x = 0; x <= 143; x++) {

		setCursor(x, 8);	//  ������ ���� ��
		printf("��");

		if (x < 17 || x>126) {

			setCursor(x, 16);
			printf("��");

			setCursor(x, 24);
			printf("��");

			setCursor(x, 32);
			printf("��");

			setCursor(x, 40);
			printf("��");
		}

		setCursor(x, 48);	// ������ �Ʒ��� ��
		printf("��");

	}

	////�η縶�� �� ������ ��  //�����ٰ� �������� ������ ��� ����ϰ� ���� => ����������'
	for (y = 0; y <= 55; y++) {

		setCursor(16, y);
		printf("��");

		if (y < 8 || y>48)
		{
			setCursor(31, y);
			printf("��");
			setCursor(47, y);
			printf("��");
			setCursor(63, y);
			printf("��");
			setCursor(79, y);
			printf("��");
			setCursor(95, y);
			printf("��");
			setCursor(111, y);
			printf("��");
			setCursor(126, y);
			printf("��");
		}

		if (y == 8) {
			setCursor(16, y);
			printf("��");
			setCursor(31, y);
			printf("��");
			setCursor(47, y);
			printf("��");
			setCursor(63, y);
			printf("��");
			setCursor(79, y);
			printf("��");
			setCursor(95, y);
			printf("��");
			setCursor(111, y);
			printf("��");
			setCursor(126, y);
			printf("��");
		}

		if (y == 16 || y == 24 || y == 32 || y == 40) {
			setCursor(16, y);
			printf("��");
		}

		if (y == 48) {
			setCursor(16, y);
			printf("��");
			setCursor(31, y);
			printf("��");
			setCursor(47, y);
			printf("��");
			setCursor(63, y);
			printf("��");
			setCursor(79, y);
			printf("��");
			setCursor(95, y);
			printf("��");
			setCursor(111, y);
			printf("��");
			setCursor(126, y);
			printf("��");
		}

		setCursor(126, y);
		printf("��");

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
				printf("��");
			}
		}

	}
}


void gui_bokbulbok(int com, int user) {

	YELLOW;
	setCursor(58, 11); printf("���Һ� ���������� ���");
	setCursor(50, 13); printf("�̱�� 100���� ���� 0�� ���� -50����");
	setCursor(63, 15); printf("PRESS ENTER");


	if (com == 0) {
		RED;
		setCursor(35, 18);  printf("C O M");
		setCursor(35, 20); printf("          ������������������");
		setCursor(35, 21); printf("          ������������������");
		setCursor(35, 22); printf("          ������������������");
		setCursor(35, 23); printf("          rU1s1RHG7SBSIZF������������������");
		setCursor(35, 24); printf("     rMu1BW.  Mu   M;   )M;������������������");
		setCursor(35, 25); printf("     DD B:   M.   B;      M:������������������");
		setCursor(35, 26); printf("    :M .B   r2 PW$rnf&aH;   M������������������");
		setCursor(35, 27); printf("    R_ vE   M.B.       :LOrx$������������������");
		setCursor(35, 28); printf("    R  .B   D.rZ          :M_8������������������");
		setCursor(35, 29); printf("   :R   B,  :B .Uxc;;        Mr������������������");
		setCursor(35, 30); printf("   :M)   B   $1   MON         H������������������");
		setCursor(35, 31); printf("   HLUD  D0;.xfrB8E.          D.������������������");
		setCursor(35, 32); printf("   #r  :B27 ;i. Dx            M������������������");
		setCursor(35, 33); printf("    B          Z.           .Mi������������������");
		setCursor(35, 34); printf("        M       M.         FR<:������������������");
		setCursor(35, 35); printf("        Dr     :8       UNp;������������������");
		setCursor(35, 36); printf("         B,    :x      GM������������������");
		setCursor(35, 37); printf("         .BU         :B0������������������");
		setCursor(35, 38); printf("           :cLi:::;rL)������������������");
		setCursor(35, 39); printf("          ������������������");
	}

	else if (com == 1) {
		RED;
		setCursor(35, 18);  printf("C O M");
		setCursor(35, 20);  printf("         .BMG        ri������������������");
		setCursor(35, 21); printf("       R  :R       L1:;K_������������������");
		setCursor(35, 22); printf("      B.  M7     HM     B������������������");
		setCursor(35, 23); printf("       B   1X    .M     iM������������������");
		setCursor(35, 24); printf("      Br   .B    M;   .M������������������");
		setCursor(35, 25); printf("      .B    B   uR    B;������������������");
		setCursor(35, 26); printf("       M;   B:  B    :B������������������");
		setCursor(35, 27); printf("        rD .M  B.     M7������������������");
		setCursor(35, 28); printf(" . .RFL8B.;:;B8W      B������������������");
		setCursor(35, 29); printf("LR3JB   HW::::x7SEu.. B������������������");
		setCursor(35, 30); printf(".M   M_    B      :D4ME������������������");
		setCursor(35, 31); printf(".B  ;M    LML.        .8:������������������:");
		setCursor(35, 32); printf(" M:  BI     ;BILu8      8:������������������");
		setCursor(35, 33); printf("  M_   B     M  7M      UH:������������������");
		setCursor(35, 34); printf("  BMr  :BriHW  7M       0x:������������������");
		setCursor(35, 35); printf("  KrrKU8:;:    r.      ,M:������������������");
		setCursor(35, 36); printf("   M                  .M,:������������������");
		setCursor(35, 37); printf("   :B.               1M.������������������");
		setCursor(35, 38); printf("    ,MW;           .uB1������������������");
		setCursor(35, 39); printf("      7j7::..:mm:rJL������������������");
	}

	else if (com == 2) {
		RED;
		setCursor(35, 18);  printf("C O M");
		setCursor(35, 20); printf("          ������������������");
		setCursor(35, 21); printf("          ������������������");
		setCursor(35, 22); printf("        '     ZM8������������������");
		setCursor(35, 23); printf("       :rn    R  p������������������");
		setCursor(35, 24); printf("      MG B:  uP  N   DEu������������������");
		setCursor(35, 25); printf("      )( .D  DC .B  MG B;������������������");
		setCursor(35, 26); printf("iCDE   D  B  M: rP MU :M������������������");
		setCursor(35, 27); printf("M  :D  M  R; 0, A.LR  8������������������");
		setCursor(35, 28); printf("DP   B D;  DM   KGM  Mr������������������");
		setCursor(35, 29); printf(" Rt   B0;        ,  DU������������������");
		setCursor(35, 30); printf("  BL   :     )#    )0������������������");
		setCursor(35, 31); printf("   Bo    :JDRT.PMGOjN: :XCF;Q������������������");
		setCursor(35, 32); printf("   :BJ$Urul   Mr     EXU    H;������������������");
		setCursor(35, 33); printf("    M        M.         FXix:������������������");
		setCursor(35, 34); printf("    Dr      :8       UNp;������������������");
		setCursor(35, 35); printf("     B,     :x      GM������������������");
		setCursor(35, 36); printf("     .BU          :B0������������������");
		setCursor(35, 37); printf("       :cLi:::;rL)������������������");
		setCursor(35, 38); printf("          ������������������");
		setCursor(35, 39); printf("          ������������������");
	}



	if (user == 0) {
		BLUE;
		setCursor(75, 18); printf("P L A Y E A R");
		setCursor(75, 20); printf("          ������������������");
		setCursor(75, 21); printf("          ������������������");
		setCursor(75, 22); printf("          ������������������");
		setCursor(75, 23); printf("          rU1s1RHG7SBSIZF������������������");
		setCursor(75, 24); printf("     rMu1BW.  Mu   M;   )M;������������������");
		setCursor(75, 25); printf("     DD B:   M.   B;      M:������������������");
		setCursor(75, 26); printf("    :M .B   r2 PW$rnf&aH;   M������������������");
		setCursor(75, 27); printf("    R_ vE   M.B.       :LOrx$������������������");
		setCursor(75, 28); printf("    R  .B   D.rZ          :M_8������������������");
		setCursor(75, 29); printf("   :R   B,  :B .Uxc;;        Mr������������������");
		setCursor(75, 30); printf("   :M)   B   $1   MON         H������������������");
		setCursor(75, 31); printf("   HLUD  D0;.xfrB8E.          D.������������������");
		setCursor(75, 32); printf("   #r  :B27 ;i. Dx            M������������������");
		setCursor(75, 33); printf("    B          Z.           .Mi������������������");
		setCursor(75, 34); printf("        M       M.         FR<:������������������");
		setCursor(75, 35); printf("        Dr     :8       UNp;������������������");
		setCursor(75, 36); printf("         B,    :x      GM������������������");
		setCursor(75, 37); printf("         .BU         :B0������������������");
		setCursor(75, 38); printf("           :cLi:::;rL)������������������");
		setCursor(75, 39); printf("          ������������������");
	}

	else if (user == 1) {
		BLUE;
		setCursor(75, 18); printf("P L A Y E A R");
		setCursor(75, 20);  printf("         .BMG        ri������������������");
		setCursor(75, 21); printf("       R  :R       L1:;K_������������������");
		setCursor(75, 22); printf("      B.  M7     HM     B������������������");
		setCursor(75, 23); printf("       B   1X    .M     iM������������������");
		setCursor(75, 24); printf("      Br   .B    M;   .M������������������");
		setCursor(75, 25); printf("      .B    B   uR    B;������������������");
		setCursor(75, 26); printf("       M;   B:  B    :B������������������");
		setCursor(75, 27); printf("        rD .M  B.     M7������������������");
		setCursor(75, 28); printf(" . .RFL8B.;:;B8W      B������������������");
		setCursor(75, 29); printf("LR3JB   HW::::x7SEu.. B������������������");
		setCursor(75, 30); printf(".M   M_    B      :D4ME������������������");
		setCursor(75, 31); printf(".B  ;M    LML.        .8::������������������");
		setCursor(75, 32); printf(" M:  BI     ;BILu8      8:������������������");
		setCursor(75, 33); printf("  M_   B     M  7M      UH:������������������");
		setCursor(75, 34); printf("  BMr  :BriHW  7M       0x:������������������");
		setCursor(75, 35); printf("  KrrKU8:;:    r.      ,M:������������������");
		setCursor(75, 36); printf("   M                  .M,:������������������");
		setCursor(75, 37); printf("   :B.               1M.������������������");
		setCursor(75, 38); printf("    ,MW;           .uB1������������������");
		setCursor(75, 39); printf("      7j7::..:mm:rJL������������������");
	}

	else if (user == 2) {
		BLUE;
		setCursor(75, 18); printf("P L A Y E A R");
		setCursor(75, 20); printf("          ������������������");
		setCursor(75, 21); printf("          ������������������");
		setCursor(75, 22); printf("        '     ZM8������������������");
		setCursor(75, 23); printf("       :rn    R  p������������������");
		setCursor(75, 24); printf("      MG B:  uP  N   DEu������������������");
		setCursor(75, 25); printf("      )( .D  DC .B  MG B;������������������");
		setCursor(75, 26); printf("iCDE   D  B  M: rP MU :M������������������");
		setCursor(75, 27); printf("M  :D  M  R; 0, A.LR  8������������������");
		setCursor(75, 28); printf("DP   B D;  DM   KGM  Mr������������������");
		setCursor(75, 29); printf(" Rt   B0;        ,  DU������������������");
		setCursor(75, 30); printf("  BL   :     )#    )0������������������");
		setCursor(75, 31); printf("   Bo    :JDRT.PMGOjN: :XCF;Q������������������");
		setCursor(75, 32); printf("   :BJ$Urul   Mr     EXU    H;������������������");
		setCursor(75, 33); printf("    M        M.         FXix:������������������");
		setCursor(75, 34); printf("    Dr      :8       UNp;������������������");
		setCursor(75, 35); printf("     B,     :x      GM������������������");
		setCursor(75, 36); printf("     .BU          :B0������������������");
		setCursor(75, 37); printf("       :cLi:::;rL)������������������");
		setCursor(75, 38); printf("          ������������������");
		setCursor(75, 39); printf("          ������������������");
	}
}

void gui_dice(int n1, int n2)
{
	int gui_dice_x = 75;

	WHITE;
//	setCursor(58, 19);
//	printf("���");
	if (n1 == 1) {
		setCursor(gui_dice_x, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x, 14); printf("��    ��    ��\n");
		setCursor(gui_dice_x, 15); printf("��    ��    ��\n");
		setCursor(gui_dice_x, 16); printf("��    ��    ��\n");
		setCursor(gui_dice_x, 17); printf("��    ��    ��\n");
		setCursor(gui_dice_x, 18); printf("��    ��    ��\n");
		setCursor(gui_dice_x, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n1 == 2) {
		setCursor(gui_dice_x, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 15); printf("��      ��  ��\n");
		setCursor(gui_dice_x, 16); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 17); printf("��  ��      ��\n");
		setCursor(gui_dice_x, 18); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n1 == 3) {
		setCursor(gui_dice_x, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 15); printf("��      ��  ��\n");
		setCursor(gui_dice_x, 16); printf("��  ���ܡ�  ��\n");
		setCursor(gui_dice_x, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 18); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n1 == 4) {
		setCursor(gui_dice_x, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x, 14); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 15); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 16); printf("��    ��������\n");
		setCursor(gui_dice_x, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 18); printf("��      ��  ��\n");
		setCursor(gui_dice_x, 19); printf("�ʢǢǢǢǢǢ�\n");
	}

	else if (n1 == 5) {
		setCursor(gui_dice_x, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 15); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 16); printf("�� �� �ܡ�  ��\n");
		setCursor(gui_dice_x, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 18); printf("�� �������� ��\n");
		setCursor(gui_dice_x, 19); printf("�ʢǢǢǢǢǢ�\n");
	}

	else if (n1 == 6) {
		setCursor(gui_dice_x, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 15); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 16); printf("��  �ܡ���  ��\n");
		setCursor(gui_dice_x, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x, 18); printf("��  ������  ��\n");
		setCursor(gui_dice_x, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	if (n2 == 1) {
		setCursor(gui_dice_x + 18, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x + 18, 14); printf("��    ��    ��\n");
		setCursor(gui_dice_x + 18, 15); printf("��    ��    ��\n");
		setCursor(gui_dice_x + 18, 16); printf("��    ��    ��\n");
		setCursor(gui_dice_x + 18, 17); printf("��    ��    ��\n");
		setCursor(gui_dice_x + 18, 18); printf("��    ��    ��\n");
		setCursor(gui_dice_x + 18, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n2 == 2) {
		setCursor(gui_dice_x + 18, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x + 18, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 15); printf("��      ��  ��\n");
		setCursor(gui_dice_x + 18, 16); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 17); printf("��  ��      ��\n");
		setCursor(gui_dice_x + 18, 18); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n2 == 3) {
		setCursor(gui_dice_x + 18, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x + 18, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 15); printf("��      ��  ��\n");
		setCursor(gui_dice_x + 18, 16); printf("��  ���ܡ�  ��\n");
		setCursor(gui_dice_x + 18, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 18); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n2 == 4) {
		setCursor(gui_dice_x + 18, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x + 18, 14); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 15); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 16); printf("��    ��������\n");
		setCursor(gui_dice_x + 18, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 18); printf("��      ��  ��\n");
		setCursor(gui_dice_x + 18, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n2 == 5) {
		setCursor(gui_dice_x + 18, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x + 18, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 15); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 16); printf("�� �� �ܡ�  ��\n");
		setCursor(gui_dice_x + 18, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 18); printf("�� �������� ��\n");
		setCursor(gui_dice_x + 18, 19); printf("�ʢǢǢǢǢǢ�\n");
	}
	else if (n2 == 6) {
		setCursor(gui_dice_x + 18, 13); printf("�ɢǢǢǢǢǢ�\n");
		setCursor(gui_dice_x + 18, 14); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 15); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 16); printf("��  �ܡ���  ��\n");
		setCursor(gui_dice_x + 18, 17); printf("��  ��  ��  ��\n");
		setCursor(gui_dice_x + 18, 18); printf("��  ������  ��\n");
		setCursor(gui_dice_x + 18, 19); printf("�ʢǢǢǢǢǢ�\n");
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


//�ֻ���
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
printf("%dĭ �̵��մϴ�\n", dice1 + dice2);
break;
}
}*/

//����������
/*
int userson, comson;
int i = 0;
while (1)
{
comson = rand() % 3;   //��ǻ�Ͱ� �� �� ������
userson = rand() % 3; //������ �� �� ������
gui_bokbulbok(comson, userson);
fflush(stdin);
Sleep(30);
if (kbhit()) {
fflush(stdin);
if (userson == comson)
{
YELLOW;
setCursor(62, 41);
printf("�� �� �� $0 ȹ��");
}
else if (comson == (userson + 1) % 3)
{
YELLOW;
setCursor(62, 41);
printf("�� �� $100 ȹ��");
}
else
{
YELLOW;
setCursor(62, 41);
printf("�� �� $50 ����");
}
break;
}
}
*/
//}



