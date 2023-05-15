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



    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //���� ���̺귯���� �ʱ�ȭ�ϰ� �ִ�

        ErrorHandling("WSAStartup() error!");



    hSocket = socket(PF_INET, SOCK_STREAM, 0); //������ �����ϰ�

    if (hSocket == INVALID_SOCKET)

        ErrorHandling("socket() error");



    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;

    servAddr.sin_addr.s_addr = inet_addr(argv[1]);

    servAddr.sin_port = htons(atoi(argv[2]));



    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //������ ������ �������� ������ �����û�� �ϰ� �ִ�

        ErrorHandling("connect() error!");



    strLen = recv(hSocket, message, sizeof(message) - 1, 0); //recv �Լ� ȣ���� ���ؼ� �����κ��� ���۵Ǵ� �����͸� �����ϰ� �ִ�.

    if (strLen == -1)

        ErrorHandling("read() error");

    printf("Message from server:%s\n", message);

    closesocket(hSocket); //���� ���̺귯�� ����

    WSACleanup();

    return 0;

}



void ErrorHandling(char* message)

{

    fputs(message, stderr);

    fputc('\n', stderr);

    exit(1);

}