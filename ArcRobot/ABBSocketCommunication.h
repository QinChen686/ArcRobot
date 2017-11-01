#pragma once

#include "winsock2.h"  
#pragma comment(lib, "ws2_32.lib")  
#include <iostream> 
#include <vector>
#define _WINSOCK_DEPRECATECD_NO_WARNINGS
using namespace std;

class ABBSocket
{
public:
	ABBSocket()
	{

	}
	int SocketMain();
};