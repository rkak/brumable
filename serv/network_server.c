#include "common.h"
#include "network_server.h"

#define sPort	5000
#define PLAYER_SIZE	(sizeof(Player))

void ErrorHandling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

SOCKET hServSock, hClntSock;
int client[2];


// player number and client is each player socket number.
int player_num = 0;
Player p1;
Player p2;

int turn;

void doServ(void) {
	initServNet();
	connectClnt();
	doBrumable();
}

void doBrumable(void) {
	int strLen;
	turn = 0;
	int yesturn = 1;
	int noturn = 0;
	int move = 0;
	// turn을 정해서 한 사람에게 알려주기.
		// turn 0 은 client 0
	while (1) {
		if (turn == 0) {
			send(client[0], (char*)&yesturn, sizeof(int), 0);
			send(client[1], (char*)&noturn, sizeof(int), 0);

			strLen = recv(client[0], (char *)&move, sizeof(int), 0);
			send(client[1], (char *)&move, sizeof(int), 0);

			turn = 1;
		}
		else {
			send(client[0], (char*)&noturn, sizeof(int), 0);
			send(client[1], (char*)&yesturn, sizeof(int), 0);

			strLen = recv(client[1], (char *)&move, sizeof(int), 0);

			send(client[0], (char *)&move, sizeof(int), 0);

			turn = 0;
		}

		if (strLen == 0) {
			printf("연결을 종료합니다\n");
			return;
		}
	}
}

void connectClnt(void) {
	SOCKADDR_IN clntAddr;

	// for multiplexing
	fd_set reads, copy_reads;
	struct timeval timeout;
	int adrSz;
	int strLen, fdNum, i;
	//char buf[BUF_SIZE];
	

	FD_ZERO(&reads);
	FD_SET(hServSock, &reads);

	// read player info and count a number of player
	while(1) {
		copy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fdNum = select(0, &copy_reads, 0, 0, &timeout)) == -1)
			break;
		if (fdNum == 0)
			continue;

		/*
		
		system("cls");
		printf("Connecting Clients....\n");
		Sleep(1000);
		system("cls");
		*/

		// only connection with 2 clients
		for (int i = 0; i < reads.fd_count; i++) {
			if (FD_ISSET(reads.fd_array[i], &copy_reads)) {
				if (reads.fd_array[i] == hServSock)     // connection request!
				{
					system("cls");
					printf("Connecting Clients..\n");
					Sleep(1000);

					adrSz = sizeof(clntAddr);
					hClntSock =
						accept(hServSock, (SOCKADDR*)&clntAddr, &adrSz);
					FD_SET(hClntSock, &reads);

					system("cls");
					printf("Connecting Clients...\n");
					Sleep(1000);

					system("cls");


					printf("connected client: %d \n", hClntSock);
					client[player_num++] = hClntSock;
					if (player_num >= 2) {
						break;
					}
				}
			}
		}
		system("cls");
		for (int i = 0; i < player_num; i++) {
			printf("connected client: %d \n", client[i]);
		}
		if (player_num >= 2) {
			player_num = 0;
			break;
		}
	}
	int ins = 1;
	sendToClnt(client[0], TYPE_INS, (void *)&ins);
	sendToClnt(client[1], TYPE_INS, (void *)&ins);

	printf("Connection complete!\n");

	// send to client another client info.
	strLen = recv(client[0], (char *)&p1, sizeof(Player), 0);
	sendToClnt(client[1], TYPE_PLAYER, (void *)&p1);
	
	strLen = recv(client[1], (char *)&p2, sizeof(Player), 0);
	sendToClnt(client[0], TYPE_PLAYER, (void *)&p2);

	
	Bank b = *makeBank(100000, 0);
	sendToClnt(client[0], TYPE_BANK, (void *)&b);
	sendToClnt(client[1], TYPE_BANK, (void *)&b);

	return;


	// 나중에 쓸것!!---------------------------------
	if (strLen == 0)    // close request!
	{
		FD_CLR(reads.fd_array[client[0]], &reads);
		FD_CLR(reads.fd_array[client[1]], &reads);
		closesocket(copy_reads.fd_array[client[0]]);
		closesocket(copy_reads.fd_array[client[1]]);
		printf("closed client: %d \n", copy_reads.fd_array[client[0]]);
		printf("closed client: %d \n", copy_reads.fd_array[client[1]]);
	}


	
	closesocket(hServSock);
	WSACleanup();
}

SOCKET initServNet(void) {
	WSADATA	wsaData;
	SOCKADDR_IN servAddr;

	
	int szClntAddr;
//	char message[] = "Hello World!";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(sPort);
	//	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	return hServSock;
}

int sendToClnt(SOCKET hSocket, int data_type, void * data) {
	switch (data_type) {
	case TYPE_INS:
		send(hSocket, (char *)data, sizeof(int), 0);
		break;
	case TYPE_PLAYER:
		send(hSocket, (char *)data, sizeof(Player), 0);
		break;
	case TYPE_BANK:
		send(hSocket, (char *)data, sizeof(Bank), 0);
		break;
	case TYPE_CC:

		break;
	}

	return 0;
}

int receiveFromClnt(SOCKET hSocket, int data_type, void * data, int size) {
	int dataLen = recv(hSocket, (char *)data, size - 1, 0);
	if (dataLen < 0)
		ErrorHandling("recv() error");
}
