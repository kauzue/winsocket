#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

#include <stdio.h>

#include <stdlib.h>

#include <WinSock2.h>



void ErrorHandling(char* message);



int main(int argc, char* argv[])

{

    WSADATA wsaData;

    SOCKET hSocket;

    SOCKADDR_IN servAddr;



    char message[30];

    int strLen;

    if (argc != 3)

    {

        printf("Usage:%s 192.168.0.2 9190\n", argv[0]);

        exit(1);

    }



    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리를 초기화하고 있다

        ErrorHandling("WSAStartup() error!");



    hSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성하고

    if (hSocket == INVALID_SOCKET)

        ErrorHandling("socket() error");



    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;

    servAddr.sin_addr.s_addr = inet_addr(argv[1]);

    servAddr.sin_port = htons(atoi(argv[2]));



    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //생성된 소켓을 바탕으로 서버에 연결요청을 하고 있다

        ErrorHandling("connect() error!");



    strLen = recv(hSocket, message, sizeof(message) - 1, 0); //recv 함수 호출을 통해서 서버로부터 전송되는 데이터를 수신하고 있다.

    if (strLen == -1)

        ErrorHandling("read() error");

    printf("Message from server:%s\n", message);

    closesocket(hSocket); //소켓 라이브러리 해제

    WSACleanup();

    return 0;

}



void ErrorHandling(char* message)

{

    fputs(message, stderr);

    fputc('\n', stderr);

    exit(1);

}