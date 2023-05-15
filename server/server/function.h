#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)

IN_ADDR GetDefaultMyIP();

void AcceptLoop(SOCKET sock);//Accept Loop
void EventLoop(SOCKET sock);
void DoIt(void* param); //송수신 스레드 진입점
void AcceptProc(int index);
void ReadProc(int index);
void CloseProc(int index);