#include "stdafx.h"
#include "ABBSocketCommunication.h"
int ABBSocket::SocketMain()
{
	const int BUF_SIZE = 600;
	WSADATA         wsd;            //WSADATA变量  
	SOCKET          sServer;        //服务器套接字  
	SOCKET          sClient;        //客户端套接字  
	SOCKADDR_IN     addrServ;;      //服务器地址  
	char            buf[BUF_SIZE];  //接收数据缓冲区  
	char            sendBuf[BUF_SIZE];//返回给客户端得数据  
	int             retVal;         //返回值  
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
	/*vector<vector<double>> targetPosvec = { { 1131.38, 173.02, 90.00 }, { 1138.58, -126.98, 77.49 },
	{740.74, -126.98, 90.00},{726.72, 187.09, 84.18},
	{943.61, 0.00, 1152.50} };*/
	/*vector<vector<char *>> targetPos = {
	{"[1131.38, 173.02, 90.00]", "[0.0918634, -0.942962, -0.296062, -0.12137]",
	"[0, -2, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[1138.58, -126.98, 77.49]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[-1, -2, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[740.74, -126.98, 90.00]", "[0.0918632, -0.942962, -0.296063, -0.12137]",
	"[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[726.72, 187.09, 84.18]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[0, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]"},
	{"[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]",
	"[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};*/
	vector<vector<char *>> targetPos = {
		{ "[757.05,-839.97,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[757.05,-1010.73,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[363.58, -1074.88, 945.65]","[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, 0, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[363.58, -704.45, 934.48]", "[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]", "[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};

	/*	vector<vector<char *>> targetPos = {
	{ "[1131.38, 173.02, 90.00]", "[0.0918634, -0.942962, -0.296062, -0.12137]",
	"[0, -2, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[1138.58, -126.98, 77.49]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[740.74, -126.98, 90.00]", "[0.0918632, -0.942962, -0.296063, -0.12137]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[726.72, 187.09, 84.18]", "[0.0918633, -0.942962, -0.296062, -0.12137]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
	{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]",
	"[0, 0, 0, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};
	*/
	for (int i = 0; i != targetPos.size(); i++)
	{
		//接收客户端数据  
		ZeroMemory(buf, BUF_SIZE);//清空内存
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
		if (buf[0] == '0')
			break;
		cout << buf << endl;
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