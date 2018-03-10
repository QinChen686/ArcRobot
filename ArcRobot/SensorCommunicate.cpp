#pragma once
#include "stdafx.h"
#include "SensorCommunicate.h"
int SensorSocket::SocketListen()
{
	//初始化套结字动态库  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return 1;
	}

	//创建套接字  
	//int socket(int family, int type, int protocol);
	//family指定协议族；
	//type参数指定socket的类型：SOCK_STREAM：流式socket使用TCP协议可靠面向链接、
	//SOCK_DGRAM:无连接的UDP、SOCK_RAW:原始套接字；
	//protocol：协议，通常赋值"0"。
	//sServer:socket描述符
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{

		cout << "socket failed!" << endl;
		WSACleanup();//释放套接字资源;  
		return  -1;
	}

	//服务器套接字地址
	//addrServ：服务器地址结构体:socketaddr_in
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(60000);//host to short 端口号
	addrServ.sin_addr.s_addr = 0;//获得本机ip地址
								 //绑定套接字 
								 //typedef socketaddr* LPSOCKADDR:指向本地地址的指针

	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed!" << endl;
		closesocket(sServer);   //关闭套接字  
		WSACleanup();           //释放套接字资源;  
		return -1;
	}

	cout << "start listen" << endl;
	//开始监听
	//socket系统调用返回的服务器端socket描述符；
	//backlog指定在请求队列中允许的最大请求数，进入的连接请求将在队列中等待accept()它们。
	//backlog对队列中等待服务的请求的数目进行了限制，大多数系统缺省值为20。
	//当listen遇到错误时返回-1,SOCKET_ERROR.
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed!" << endl;
		closesocket(sServer);   //关闭套接字  
		WSACleanup();           //释放套接字资源;
		return -1;
	}
	return 0;
}


int SensorSocket::SocketAccept()
{
	//接受客户端请求 
	//int accept(int sockfd, struct sockaddr *addr, int *addrlen);
	// sockfd是被监听的服务器socket描述符，addr通常是一个指向sockaddr_in变量的指针，该变量用来存放提出连接请求的客户端地址；
	//addrten通常为一个指向值为sizeof(struct sockaddr_in)的整型指针变量。
	//错误发生时返回一个-1并且设置相应的errno值。
	//accept()函数将返回一个新的socket描述符，来供这个新连接来使用，在新的socket描述符上进行数据send()和recv()操作。
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
	if (INVALID_SOCKET == sClient)
	{
		cout << "accept failed!" << endl;
		closesocket(sServer);   //关闭套接字  
		WSACleanup();           //释放套接字资源;  
		return -1;
	}
	ZeroMemory(buf, BUF_SIZE2);//清空内存
	return 0;
}

int SensorSocket::SocketStart(char* Data)
{
	sprintf_s(sendBuf, Data);
	send(sClient, sendBuf, strlen(sendBuf), 0);
	return 1;
}

int SensorSocket::RecvLine(char *vptr, int maxlen, char partChar)
{
	int n, rc;
	char c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++)
	{
		if ((rc = my_read(&c)) == 1)
		{
			*ptr++ = c;
			if (c == partChar)
			{
				break;
			}	
		}	
		else if (rc == 0)
			{
				*ptr = 0;
				return(n - 1);
			}	
		else
				return(-1);
	}
	*ptr = 0;
	return(n);
}

int SensorSocket::my_read(char *ptr)
{
	if(read_cnt<=0)
	{	
	again:
		if ((read_cnt = recv(sClient, read_buf, sizeof(read_buf), 0)) < 0)
		//注意运算的优先级，比较运算高于赋值
		{
			if (errno == EINTR)
				goto again;
			return (-1);
		}
		else if (read_cnt == 0)
			return (0);
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return (1);

}

int SensorSocket::read_cnt;
char *SensorSocket::read_ptr;
char SensorSocket::read_buf[BUF_SIZE2];
