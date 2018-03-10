#include "stdafx.h"
#include "CalPos.h"

int calWeldLine::GetSensorPos(double *resa, double *resb, DWORD* GetWeldLineTime)
{
	*GetWeldLineTime = timeGetTime();
	*resa =-20 + rand() / double(RAND_MAX) * 40;
	*resb =-20 + rand() / double(RAND_MAX) * 40;
	return 0;
};

int calWeldLine::calWeldLinePos(vector<double>& SensorPos, vector<double>& RealPos)
{
	Matrix4d TB(quater2T(SensorPos));
	Vector4d SP;
	SP << 0, SensorPos[8], SensorPos[9], 1;
	Vector4d WorldPos(TB*T*SP);
	RealPos[0] = WorldPos[0]; RealPos[1] = WorldPos[1]; RealPos[2] = WorldPos[2];
	RealPos[3] = SensorPos[4]; RealPos[4] = SensorPos[5]; RealPos[5] = SensorPos[6]; RealPos[6] = SensorPos[7];
	cout << "RealPos:";
	for (double kk : RealPos)
		cout << kk << " ";
	cout << endl;
	return 0;
};

Matrix4d calWeldLine::quater2T(vector<double>& SensorPos)
{
	Matrix4d TB;
	double p1 = SensorPos[1],	p2 = SensorPos[2],	p3 = SensorPos[3],	x = SensorPos[4],	y = SensorPos[5],	z = SensorPos[6],	w = SensorPos[7];
	TB(0, 0) = 1 - 2 * y*y - 2 * z*z;	TB(0, 1) = 2 * (x*y - z*w);			TB(0, 2) = 2 * (x*z + y*w);			TB(0, 3) = p1;
	TB(1, 0) = 2 * (x*y + z*w);			TB(1, 1) = 1 - 2 * x*x - 2 * z*z;	TB(1, 2) = 2 * (y*z - x*w);			TB(1, 3) = p2;
	TB(2, 0) = 2 * (x*z - y*w);			TB(2, 1) = 2 * (y*z + x*w);			TB(2, 2) = 1 - 2 * x*x - 2 * y*y;	TB(2, 3) = p3;
	TB(3, 0) = 0;						TB(3, 1) = 0;						TB(3, 2) = 0;						TB(3, 3) = 1;
	return TB;
}

Matrix4d calWeldLine::T;