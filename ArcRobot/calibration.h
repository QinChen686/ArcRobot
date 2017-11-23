#pragma once
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

struct CaliStruct
{
	//机器人第六个轴末端x,y,z位置坐标
	Eigen::Vector3d EndPos;

	//rpy值
	Eigen::Vector3d rpy;

	//激光坐标值
	Eigen::Vector2d delta;

	//机器人标定点相对于基座标位置坐标
	Eigen::Vector4d pointPos;

	//rotion
	Eigen::Matrix3d R;

	//quaternion
};

class calibration {

	vector<CaliStruct> caliData;
public:
	int AddCaliData(CaliStruct caliStruct)
	{
		caliData.push_back(caliStruct);
	}

	 int calculateT(Matrix4d T)
	{
		 int pointNum = caliData.size();
		 if (pointNum < 3)
			 return -1;
		 for (int i = 0; i != pointNum; i++)
		 {
			 rpy2rot(caliData[i]);
		 }
		 vector<Matrix4d> TP(pointNum, Matrix4d());
		 vector<Vector4d> abc(pointNum, Vector4d());
		 for (int i = 0; i != pointNum; i++)
		 {
			 for(int j=0;j!=3;j++)
				 for(int k=0;k!=3;k++)
					TP[i](j , k) = caliData[i].R(j, k);
			 TP[i](0, 3) = caliData[i].EndPos(0);
			 TP[i](1, 3) = caliData[i].EndPos(1);
			 TP[i](2, 3) = caliData[i].EndPos(2);
			 TP[i](3, 0) = 0; TP[i](3, 1) = 0; TP[i](3, 2) = 0; TP[i](3, 3) = 1;
			 abc[i] = TP[i].inverse()*caliData[i].pointPos;
		 }
		 MatrixXd M = MatrixXd::Ones(3, pointNum);
		 MatrixXd ABC(3, pointNum);
		 for (int i = 0; i != pointNum; i++)
		 {
			 M(0, i) = caliData[i].delta(0);
			 M(1, i) = caliData[i].delta(1);
			 ABC(0, i) = abc[i](0);
			 ABC(1, i) = abc[i](1);
			 ABC(2, i) = abc[i](2);
		 }
		
		 JacobiSVD<Eigen::MatrixXf> svd(M, ComputeThinU | ComputeThinV);
		 MatrixXd V = svd.matrixV(), U = svd.matrixU();
		 MatrixXd  S = U.inverse() * M * V.transpose().inverse(); // S = U^-1 * A * VT * -1
		 MatrixXd T0 = ABC*S;
		 Vector3d o = T0.block(0, 0, 3, 1);
		 Vector3d a = T0.block(0, 1, 3, 1);
		 o = o / o.norm();
		 a = a / a.norm();
		 Vector3d n = o.cross(a);

		 T(0, 0) = n(0); T(1, 0) = n(1); T(2, 0) = n(2); T(3, 0) = 0;
		 T(0, 1) = o(0); T(1, 1) = o(1); T(2, 1) = o(2); T(3, 1) = 0;
		 T(0, 2) = a(0); T(1, 2) = a(1); T(2, 2) = a(2); T(3, 2) = 0;
		 T(0, 3) = T0(0,3); T(1, 3) = T0(1, 3); T(2, 3) = T0(2, 3); T(3, 3) = 1;
		 return 0;
	}
	 int rpy2rot(CaliStruct &caliStruct)
	 {
		double alfa = caliStruct.rpy[0];
		double beta = caliStruct.rpy[1];
		double gama = caliStruct.rpy[2];
		caliStruct.R << cos(alfa)*cos(beta),cos(alfa)*sin(beta)*sin(gama) - sin(alfa)*cos(gama), cos(alfa)*sin(beta)*cos(gama) + sin(alfa)*sin(gama),
			sin(alfa)*cos(beta), sin(alfa)*sin(beta)*sin(gama) + cos(alfa)*cos(gama), sin(alfa)*sin(beta)*cos(gama) - cos(alfa)*sin(gama),
			- sin(beta), cos(beta)*sin(gama), cos(beta)*cos(gama);
	 }
};