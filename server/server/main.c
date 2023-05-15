#include <stdio.h>

#include <stdlib.h>

#include <WinSock2.h>



void ErrorHandling(char* message);



int main(int argc, char* argv[])

{

    WSADATA wsaData;

    SOCKET hServSock, hClntSock;

    SOCKADDR_IN servAddr, clntAddr;



    int szClntAddr;

    char message[] = "Hello World!";

    if (argc != 2)

    {

        printf("Usage:%s <port>\n", argv[0]);

        exit(1);

    }



    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리 초기화

        ErrorHandling("WSAStartup() error!");



    hServSock = socket(PF_INET, SOCK_STREAM, 0); //소켓생성

    if (hServSock == INVALID_SOCKET)

        ErrorHandling("socket() error");



    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;

    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servAddr.sin_port = htons(atoi(argv[1]));



    if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //소켓에 IP주소와 PORT 번호 할당

        ErrorHandling("bind() error");



    if (listen(hServSock, 5) == SOCKET_ERROR) //listen 함수호출을 통해서 생성한 소켓을 서버 소켓으로 완성

        ErrorHandling("listen() error");



    szClntAddr = sizeof(clntAddr);

    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); //클라이언트 연결요청 수락하기 위해 accept함수 호출

    if (hClntSock == INVALID_SOCKET)

        ErrorHandling("accept() error");



    send(hClntSock, message, sizeof(message), 0); //send함수 호출을 통해서 연결된 클라이언트에 데이터를 전송

    closesocket(hClntSock);

    closesocket(hServSock);

    WSACleanup(); //프로그램 종료 전에 초기화한 소켓 라이브러리 해제

    return 0;

}



void ErrorHandling(char* message)

{

    fputs(message, stderr);

    fputc('\n', stderr);

    exit(1);

}