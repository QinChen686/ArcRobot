#pragma once

#include "winsock2.h"  
#pragma comment(lib, "ws2_32.lib")  
#include <vector>
#include "ProcessLog.h"
#define _WINSOCK_DEPRECATECD_NO_WARNINGS
using namespace std;
const int BUF_SIZE = 600;

class ABBSocket : public ProcessLog
{
public:
	int SocketListen();
	int SocketAccept();
	int SocketSendPos(vector<vector<char *>>);
	int SocketStop();
	int SocketSend(char* Data);
	char* GetCurPos();
private:

	WSADATA         wsd;            //WSADATA变量  
	SOCKET          sServer;        //服务器套接字  
	SOCKET          sClient;        //客户端套接字  
	SOCKADDR_IN     addrServ;;      //服务器地址  
	char            buf[BUF_SIZE];  //接收数据缓冲区  
	char            sendBuf[BUF_SIZE];//返回给客户端得数据  
	int             retVal;         //返回值  
};