#pragma once
#include <Windows.h>
#include <Mmsystem.h>
#include <stdlib.h> 
#include <Eigen/Dense>
#include <time.h> 
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace Eigen;
using namespace std;


class calWeldLine
{
public:
	calWeldLine()
	{
		srand((unsigned)time(NULL));
		T << -0.462978,	0.845702,	-0.0689446,	-55.5626,
			  0.801837, 0.525382,	0.332724,	62.3512,
			  0.317608,	-0.0936039,	-0.940501,	467.312,
			  0, 0, 0, 1;

	}
	static Matrix4d T;
	bool InitFlag=false;
	int GetSensorPos(double *resa, double *resb, DWORD* GetWeldLineTime);
	int calWeldLinePos(vector<double>& SensorPos, vector<double>& RealPos);
	Matrix4d quater2T(vector<double>& SensorPos);
};

