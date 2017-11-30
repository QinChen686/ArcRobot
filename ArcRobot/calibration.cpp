#include "stdafx.h"
#include "calibration.h"
using namespace Eigen;
using namespace std;

int Calibration::AddCaliData(CaliStruct &caliStruct)
{
	caliData.push_back(caliStruct);
	return 0;
}


Matrix4d Calibration::calculateT()
{
	Matrix4d T = Matrix4d::Zero();
	int pointNum = caliData.size();
	if (pointNum < 3)
		return T;
	for (int i = 0; i != pointNum; i++)
	{
		rpy2rot(caliData[i]);
	}
	Matrix4d TP;
	Vector4d abc;
	MatrixXd M = MatrixXd::Ones(3, pointNum);
	MatrixXd ABC(3, pointNum);

	for (int i = 0; i != pointNum; i++)
	{
		for (int j = 0; j != 3; j++)
			for (int k = 0; k != 3; k++)
				TP(j, k) = caliData[i].R[j][k];
		TP(0, 3) = caliData[i].EndPos[0];
		TP(1, 3) = caliData[i].EndPos[1];
		TP(2, 3) = caliData[i].EndPos[2];
		TP(3, 0) = 0; TP(3, 1) = 0; TP(3, 2) = 0; TP(3, 3) = 1;
		//cout << "TP:" << endl;
		//cout << TP << endl;
		//cout << "TPInverse:" << endl;
		//cout << TP.inverse() << endl;

		Vector4d pointPosMatrix;
		pointPosMatrix << caliData[i].pointPos[0], caliData[i].pointPos[1], caliData[i].pointPos[2], 1;
		abc = TP.inverse()*pointPosMatrix;
		//cout << pointPosMatrix << endl;
		//cout << abc << endl;
		M(0, i) = caliData[i].delta[0];
		M(1, i) = caliData[i].delta[1];
		ABC(0, i) = abc(0);
		ABC(1, i) = abc(1);
		ABC(2, i) = abc(2);
	}
	//cout << "ABC:" << endl;
	//cout << ABC << endl;
	//cout << "M:" << endl;
	//cout << M << endl;
	//here is right 17/11/22 19:49

	//求解广义逆存在问题 
	MatrixXd MT = M.transpose(), ABCT = ABC.transpose();
	//cout << "MT:" << endl;
	//cout << MT << endl;
	//cout << "ABCT:" << endl;
	//cout << ABCT << endl;
	MatrixXd T0T = MT.fullPivHouseholderQr().solve(ABCT);

	MatrixXd T0 = T0T.transpose();
	//cout << "T0:" << endl;
	//cout << T0 << endl;

	Vector3d o = T0.block(0, 0, 3, 1);
	Vector3d a = T0.block(0, 1, 3, 1);
	o = o / o.norm();
	a = a / a.norm();
	Vector3d n = o.cross(a);

	T(0, 0) = n(0); T(1, 0) = n(1); T(2, 0) = n(2); T(3, 0) = 0;
	T(0, 1) = o(0); T(1, 1) = o(1); T(2, 1) = o(2); T(3, 1) = 0;
	T(0, 2) = a(0); T(1, 2) = a(1); T(2, 2) = a(2); T(3, 2) = 0;
	T(0, 3) = T0(0, 2); T(1, 3) = T0(1, 2); T(2, 3) = T0(2, 2); T(3, 3) = 1;
	return T;
}


int Calibration::rpy2rot(CaliStruct &caliStruct)
{
	double alfa = caliStruct.rpy[0];
	double beta = caliStruct.rpy[1];
	double gama = caliStruct.rpy[2];
	vector<double> temR{ cos(alfa)*cos(beta), cos(alfa)*sin(beta)*sin(gama) - sin(alfa)*cos(gama), cos(alfa)*sin(beta)*cos(gama) + sin(alfa)*sin(gama),
		sin(alfa)*cos(beta), sin(alfa)*sin(beta)*sin(gama) + cos(alfa)*cos(gama), sin(alfa)*sin(beta)*cos(gama) - cos(alfa)*sin(gama),
		-sin(beta), cos(beta)*sin(gama), cos(beta)*cos(gama) };
	for (int i = 0; i != caliStruct.R.size(); i++)
		for (int j = 0; j != caliStruct.R[i].size(); j++)
			caliStruct.R[i][j] = temR[i * 3 + j];
	return 0;
}

