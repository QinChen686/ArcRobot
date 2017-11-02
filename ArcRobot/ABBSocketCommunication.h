#pragma once

#include "winsock2.h"  
#pragma comment(lib, "ws2_32.lib")  
#include <vector>
#include "ProcessLog.h"
#define _WINSOCK_DEPRECATECD_NO_WARNINGS
using namespace std;

class ABBSocket : public ProcessLog
{
public:
	int SocketMain();
};