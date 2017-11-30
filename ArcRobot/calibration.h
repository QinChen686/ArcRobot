#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/StdVector>
using namespace Eigen;
using namespace std;


struct CaliStruct
{

	CaliStruct()
	{
		EndPos.resize(3);
		rpy.resize(3);
		delta.resize(3);
		pointPos.resize(3);
		R.resize(3);
		R[0].resize(3); R[1].resize(3); R[2].resize(3);
	}
	//机器人第六个轴末端x,y,z位置坐标
	vector<double> EndPos;

	//rpy值
	vector<double> rpy;

	//激光坐标值
	vector<double> delta;

	//机器人标定点相对于基座标位置坐标
	vector<double> pointPos;

	//rotion
	vector<vector<double>> R;

	//quaternion


};

//EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(CaliStruct);

class Calibration {

	vector<CaliStruct> caliData;
public:
	int AddCaliData(CaliStruct &caliStruct);

	Matrix4d calculateT();

	int rpy2rot(CaliStruct &caliStruct);
};


//int main()
//{
//	CaliStruct cst[4];
//	Calibration clbrt;
//
//	cst[0].delta[0] = 7.41; cst[0].delta[1] = 4.66;
//	cst[0].EndPos[0] = 557.99; cst[0].EndPos[1] = -465.86; cst[0].EndPos[2] = 636.39;
//	cst[0].pointPos[0] = 773.2; cst[0].pointPos[1] = -457.9; cst[0].pointPos[2] = 219.81;
//	cst[0].rpy[0] = 117.28 / 180 * 3.1415926; cst[0].rpy[1] = 5.89 / 180 * 3.1415926; cst[0].rpy[2] = 163.77 / 180 * 3.1415926;
//	clbrt.AddCaliData(cst[0]);
//
//	cst[1].delta[0] = 12.51; cst[1].delta[1] = 2.55;
//	cst[1].EndPos[0] = 505.85, cst[1].EndPos[1] = -338.14; cst[1].EndPos[2] = 588.98;
//	cst[1].pointPos[0] = 773.2; cst[1].pointPos[1] = -457.9; cst[1].pointPos[2] = 219.81;
//	cst[1].rpy[0] = 94.48 / 180 * 3.1415926; cst[1].rpy[1] = 14.47 / 180 * 3.1415926, cst[1].rpy[2] = 155.44 / 180 * 3.1415926;
//	clbrt.AddCaliData(cst[1]);
//
//	cst[2].delta[0] = 1.89; cst[2].delta[1] = 3.14;
//	cst[2].EndPos[0] = 652.55, cst[2].EndPos[1] = -326; cst[2].EndPos[2] = 656.17;
//	cst[2].pointPos[0] = 773.2; cst[2].pointPos[1] = -457.9; cst[2].pointPos[2] = 219.81;
//	cst[2].rpy[0] = 65.03 / 180 * 3.1415926; cst[2].rpy[1] = 1.93 / 180 * 3.1415926; cst[2].rpy[2] = 167.3 / 180 * 3.1415926;
//	clbrt.AddCaliData(cst[2]);
//
//	cst[3].delta[0] = -5.43; cst[3].delta[1] = 8.96;
//	cst[3].EndPos[0] = 735.5; cst[3].EndPos[1] = -311.82; cst[3].EndPos[2] = 662.41;
//	cst[3].pointPos[0] = 773.2, cst[3].pointPos[1] = -457.9; cst[3].pointPos[2] = 219.81;
//	cst[3].rpy[0] = 46.53 / 180 * 3.1415926; cst[3].rpy[1] = 2.38 / 180 * 3.1415926; cst[3].rpy[2] = 171.68 / 180 * 3.1415926;
//	clbrt.AddCaliData(cst[3]);
//
//	//cout << "hello" << endl;
//
//	/*
//	int k = 5;
//	MatrixXd A(5,5), Ainv(5,5);
//	MatrixXd I = MatrixXd::Identity(k, k); // I is an identity matrix
//	A << 2, -1, -1, 3, 8,
//	-9, 6, 13, 2, -3,
//	2, 1, -1, 3, 8,
//	-9, 6, 2, 2, -3,
//	6, 13, 2, -3, 7;
//	Ainv = A.fullPivHouseholderQr().solve(I);    // ldlt() can be replaced by other decomposition solvers
//	cout << "The matrix A is:\n" << A << endl;
//	cout << "The inversion of matrix A is:\n" << Ainv << endl;
//	cout << "The TEST of matrix A*Ainv is:\n" << A*Ainv << endl;
//	*/
//
//	/*
//	MatrixXd MT(4, 3), ABCT(4, 3);
//	ABCT << -48.3322, 68.7109, 461.3680,
//	-43.5817, 70.7652, 463.8943,
//	-53.9047, 64.6295, 463.9843,
//	-61.6298, 62.0430, 459.3559;
//	MT << 7.4100, 4.6600, 1,
//	12.5100, 2.5500, 1,
//	1.8900, 3.1400, 1,
//	-5.4300, 8.9600, 1;
//	x = MT.colPivHouseholderQr().solve(ABCT);
//	MatrixXd xT = x.transpose();
//	cout << "The solution using the QR decomposition is:\n" << x << endl;
//	cout << "ABC:\n" << ABCT << endl;
//	cout << "test : \n" << MT*x << endl;
//
//
//	Matrix4d T = clbrt.calculateT();
//	cout << "T" << endl;
//	cout << T << endl;
//	system("pause");
//	return 0;
//
//}