#include "stdafx.h"
#include "ABBSocketCommunication.h"
#include "Resource.h"
using namespace std;

int ABBSocket::SocketListen()
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
	addrServ.sin_port = htons(4999);//host to short 端口号
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


int ABBSocket::SocketAccept()
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
	ZeroMemory(buf, BUF_SIZE);//清空内存
	return 0;
}


int ABBSocket::SocketSend(char* Data)
{
	sprintf_s(sendBuf, Data);
	send(sClient, sendBuf, strlen(sendBuf), 0);
	return 1;
}

char* ABBSocket::GetCurPos()
{
	ZeroMemory(buf, BUF_SIZE);//清空内存
	SocketSend("CurPos");
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << buf << endl;
	return buf;
	

}

char* ABBSocket::GetPointPos()
{
	ZeroMemory(buf, BUF_SIZE);//清空内存
	SocketSend("PointPos");
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << buf << endl;
	return buf;
}

char* ABBSocket::GetEndPos()
{
	ZeroMemory(buf, BUF_SIZE);//清空内存
	SocketSend("EndPos");
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << buf << endl;
	return buf;
}


//
int ABBSocket::SocketSendPos(vector<vector<char *>> targetPos,int num) 
{
	ZeroMemory(buf, BUF_SIZE);//清空内存
	SocketSend("RecPos");
	for (int i = 0; i != num; i++)
	{
		//接收客户端数据  
	    //原型：int recv(int sockfd,void *buf,int len,unsigned int flags); 
		//recive from :sockfd是接受数据的socket描述符；
		//buf 是存放接收数据的缓冲区；len是缓冲的长度。
		//flags也被置为0。
		//recv()返回实际上接收的字节数，或当出现错误时，返回 - 1并置相应的errno值。
		retVal = recv(sClient, buf, BUF_SIZE, 0);//接收函数
												 // int recv(int sockfd,void *buf,int len,unsigned int flags); 

		if (SOCKET_ERROR == retVal)
		{
			cout << "recv failed!" << endl;
			closesocket(sServer);   //关闭套接字  
			closesocket(sClient);   //关闭套接字       
			WSACleanup();           //释放套接字资源;  
			return -1;
		}
		if (buf[0] == '\0')
			break;
		cout << "dierci:" << buf <<  endl;
		//tans data

		sprintf_s(sendBuf, "Start");
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);

		sprintf_s(sendBuf, "%s", targetPos[i][0]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//rot data
		sprintf_s(sendBuf, "%s", targetPos[i][1]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//robconf data
		sprintf_s(sendBuf, "%s", targetPos[i][2]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//extax data
		sprintf_s(sendBuf, "%s", targetPos[i][3]);
		printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		cout << buf << endl;
		//sprintf_s(sendBuf,"[%.5f, %.5f, %.5f]", posx, posy, posz);


		//int send(int sockfd, const void *msg, int len, int flags);
		//send to:sockfd是你想用来传输数据的socket描述符，msg是一个指向要发送数据的指针。
		//len是以字节为单位的数据的长度。flags一般情况下置为0（关于该参数的用法可参照man手册）。
		//send()函数返回实际上发送出的字节数，可能会少于你希望发送的数据。所以需要对send()的返回值进行测量。
		//当send()返回值与len不匹配时，应该对这种情况进行处理。


	}
	recv(sClient, buf, BUF_SIZE, 0);
	cout << "ready?       " << buf << endl;
	sprintf_s(sendBuf, "End");
	send(sClient, sendBuf, strlen(sendBuf), 0);
	retVal = recv(sClient, buf, BUF_SIZE, 0);
	cout << "Last: " << buf << endl;
	return 0;
}

int ABBSocket::SocketScan(vector<vector<char *>> targetPos, DWORD* ScanStartTime, int num)
{
	ZeroMemory(buf, BUF_SIZE);//清空内存
	SocketSend("Scan");
	*ScanStartTime = timeGetTime();
	for (int i = 0; i != num; i++)
	{
		//接收客户端数据  
		//原型：int recv(int sockfd,void *buf,int len,unsigned int flags); 
		//recive from :sockfd是接受数据的socket描述符；
		//buf 是存放接收数据的缓冲区；len是缓冲的长度。
		//flags也被置为0。
		//recv()返回实际上接收的字节数，或当出现错误时，返回 - 1并置相应的errno值。
		retVal = recv(sClient, buf, BUF_SIZE, 0);//接收函数
												 // int recv(int sockfd,void *buf,int len,unsigned int flags); 

		if (SOCKET_ERROR == retVal)
		{
			cout << "recv failed!" << endl;
			closesocket(sServer);   //关闭套接字  
			closesocket(sClient);   //关闭套接字       
			WSACleanup();           //释放套接字资源;  
			return -1;
		}
		if (buf[0] == '\0')
			break;
		//cout << "dierci:" << buf << endl;
		//tans data

		sprintf_s(sendBuf, "Start");
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);

		sprintf_s(sendBuf, "%s", targetPos[i][0]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//rot data
		sprintf_s(sendBuf, "%s", targetPos[i][1]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//robconf data
		sprintf_s(sendBuf, "%s", targetPos[i][2]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//extax data
		sprintf_s(sendBuf, "%s", targetPos[i][3]);
		//printf("%s\n", sendBuf);
		send(sClient, sendBuf, strlen(sendBuf), 0);
		recv(sClient, buf, BUF_SIZE, 0);
		//cout << buf << endl;
		//sprintf_s(sendBuf,"[%.5f, %.5f, %.5f]", posx, posy, posz);


		//int send(int sockfd, const void *msg, int len, int flags);
		//send to:sockfd是你想用来传输数据的socket描述符，msg是一个指向要发送数据的指针。
		//len是以字节为单位的数据的长度。flags一般情况下置为0（关于该参数的用法可参照man手册）。
		//send()函数返回实际上发送出的字节数，可能会少于你希望发送的数据。所以需要对send()的返回值进行测量。
		//当send()返回值与len不匹配时，应该对这种情况进行处理。


	}
	recv(sClient, buf, BUF_SIZE, 0);
	//cout << "ready?       " << buf << endl;
	sprintf_s(sendBuf, "End");
	send(sClient, sendBuf, strlen(sendBuf), 0);
	retVal = recv(sClient, buf, BUF_SIZE, 0);
	//cout << "Last: " << buf << endl;


	//接收位置信息
	/*
	int recvTimeout = 2 * 1000;   //2s
	setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout, sizeof(int));
	while (-1 != recv(sClient, buf, BUF_SIZE, 0))
	{
		cout << buf << endl;
		ZeroMemory(buf, BUF_SIZE);//清空内存
	}
	*/
	return 0;
}

 char* ABBSocket::SocketPosRecv(int* rval)
{	
	int recvTimeout = 2 * 1000;   //2s
	setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout, sizeof(int));
	ZeroMemory(buf, BUF_SIZE);//清空内存
	int rVal=recv(sClient, buf, BUF_SIZE, 0);
	*rval = rVal;
	return buf;
}


 int ABBSocket::SetToZero()
 {
	 SocketSend("ToZero");
	 return 0;
 }

int ABBSocket::SocketStop()
{
	ZeroMemory(buf, BUF_SIZE);//清空内存
	retVal = recv(sClient, buf, BUF_SIZE, 0);//接收函数
	sprintf_s(sendBuf, "Stop");
	send(sClient, sendBuf, strlen(sendBuf), 0);
	recv(sClient, buf, BUF_SIZE, 0);
	//退出  
	closesocket(sServer);   //关闭套接字  
	closesocket(sClient);   //关闭套接字  
	WSACleanup();           //释放套接字资源;  
	return 0;
} 

WSADATA ABBSocket::wsd;            //WSADATA变量  
SOCKET ABBSocket::sServer;        //服务器套接字  
SOCKET ABBSocket::sClient;        //客户端套接字  
SOCKADDR_IN  ABBSocket::addrServ;      //服务器地址