#pragma once
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>
#include <vector>
#include <fstream>  
#include <iostream>

#include "Vector3D.h"
#include "Position3D.h"
#include "Matrix4D.h"
using namespace std;

struct norver
{
	double normal1;
	double normal2;
	double normal3;
	double vertex1;
	double vertex2;
	double vertex3;
};
class glDisplay
{
public:
	vector<norver> NorverVec;
	int count=0;

	glDisplay()
	{
		NorverVec.resize(10000);
		OldMouse = new Position3D();
		Mouse = new Position3D();

		NewEye = new Vector3D(1000, 0, 0);
		NewUp = new Vector3D(0, 0, 1);
		NewView = new Vector3D(0, 0, 0);

		AuxY = new Vector3D(0, 1, 0);
		AuxZ = new Vector3D();
		*AuxZ = (Vector3D)*NewEye - (Vector3D)*NewView;
		AuxX = new Vector3D();
		*AuxX = Vector3D::crossProduct(*AuxY, *AuxZ);
		AuxX->normalize();

		TempTranslateVec = new Vector3D(0, 0, 0);
		TempscaleFactor = 1;
	}
	int ReadSlpFile();
	void GLDraw();
	//void render();
	void executeRotateOperation(int x, int y);
	void executeScaleOperation(float factor);
	void executeTranslateOperation(int x, int y);
	void getInitPos(int x, int y);
private:
	//辅助坐标系三根轴
	Vector3D *AuxX;
	Vector3D *AuxY;
	Vector3D *AuxZ;

	//旋转后观察点方向与视线向上方向
	Vector3D*NewEye;
	Vector3D*NewUp;
	Vector3D *NewView;

	Position3D *OldMouse;
	Position3D *Mouse;

	Vector3D *TempTranslateVec;
	float TempscaleFactor;


};