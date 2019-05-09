#include "common.h"
#include "network_client.h"

#define sPort	5000

void ErrorHandling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}


SOCKET hSocket;
extern Player * p_net;
int ins = 0;

void doServ(void) {
	initClntNet();

	int dataLen;

	dataLen = recv(hSocket, (char *)&ins, sizeof(int), 0);
//	printf("ins : %d\n", ins);

	if (dataLen == -1) {
		ErrorHandling("read() error!");
	}

	send(hSocket, (char *)p_net, sizeof(Player), 0);
}


SOCKET initClntNet(void) {
	WSADATA wsaData;
	SOCKADDR_IN servAddr;

	char sIP[] = "10.0.11.30";
//	char sIP[] = "192.168.43.90";
	//	char sPort[] = "5000";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(sIP);
	servAddr.sin_port = htons(sPort);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");

	return hSocket;
}


int sendToServ(int data_type, void * data, int size) {
	send(hSocket, (char *)data, size, 0);
	return 0;
}

int receiveFromServ(int data_type, void * data, int size) {
	// ----- 통신 시작
//	char message[100];
	int dataLen;

	dataLen = recv(hSocket, (char *)data, size, 0);
	if (dataLen == -1)
		ErrorHandling("read() error!");
//	p_net = (Player)
	printf("Message from server: %s \n", data);


	// ------ 통신 끝

	dataLen = recv(hSocket, (char *) data, size - 1, 0);
	if (dataLen < 0)
		ErrorHandling("recv() error");
}

void quitNet(void) {
	closesocket(hSocket);
	WSACleanup();
	getchar();
	return 0;

}

