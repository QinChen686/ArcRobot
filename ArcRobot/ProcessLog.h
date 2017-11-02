#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>  
#include <fcntl.h>  
using namespace std;

class ProcessLog
{
public:
	ProcessLog()
	{ 
		//AllocConsole();
		//HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		//HANDLE hInPut = GetStdHandle(STD_INPUT_HANDLE);
		//redirect stdout and stdin
		//int hCrt;
		//FILE *hf, *hf2;
		//hCrt = _open_osfhandle((intptr_t)hOutput, 0x4000);
		//hf = _fdopen(hCrt, "w");
		//*stdout = *hf;
		//hCrt = _open_osfhandle((intptr_t)hInPut, 0x4000);
		//hf2 = _fdopen(hCrt, "r");
		//*stdin = *hf2;


		FILE* fpout;
		freopen_s(&fpout, "out.log", "w", stdout);
		cout << "打开控制台成功" << endl;
		cout << "打开控制台成功" << endl;

	}

};
