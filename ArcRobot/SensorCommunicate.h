
#pragma once
#include "winsock2.h"  
#pragma comment(lib, "ws2_32.lib")  
#pragma comment( lib,"winmm.lib" )
#include <Windows.h>
#include <Mmsystem.h>
#include <vector>
#include "ProcessLog.h"
#define _WINSOCK_DEPRECATECD_NO_WARNINGS
using namespace std;
const int BUF_SIZE2 = 600;

class SensorSocket
{
public:
	int SocketListen();
	int SocketAccept();
	int SocketStart(char* Data);
	int RecvLine(char *vptr, int maxlen = 150, char partChar = 0);
	int my_read(char *ptr);
	int closeSocket(){ return closesocket(sClient);  };


public:

	WSADATA         wsd;            //WSADATA变量  
	SOCKET          sServer;        //服务器套接字  
	SOCKET          sClient;        //客户端套接字  
	SOCKADDR_IN     addrServ;;      //服务器地址  
	char            buf[BUF_SIZE2];  //接收数据缓冲区  
	char            sendBuf[BUF_SIZE2];//返回给客户端得数据  
	int             retVal;         //返回值  

	static int read_cnt;
	static char *read_ptr;
	static char read_buf[BUF_SIZE2];
};
