
// ArcRobotDlg.cpp : 实现文件
//

#include <iostream>
#include "stdafx.h"
#include "ArcRobot.h"
#include "ArcRobotDlg.h"
#include "afxdialogex.h"
#include "PosSeqDialog.h"
#include "ScanDialog.h"
#include "Resource.h"
#include "CalibrationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CArcRobotDlg 对话框



CArcRobotDlg::CArcRobotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARCROBOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CalibrationDlg::CalibratedFlag = false;
	res0.resize(1000);
	for (int i = 0; i != 1000; i++)
		res0[i].resize(10);
	SensorData0.resize(1000);
	for (int i = 0; i != 1000; i++)
		SensorData0[i].resize(4);
}

void CArcRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CArcRobotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CArcRobotDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CArcRobotDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CArcRobotDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CArcRobotDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CArcRobotDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &CArcRobotDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &CArcRobotDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CArcRobotDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CArcRobotDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CArcRobotDlg 消息处理程序

BOOL CArcRobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOWNORMAL);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CArcRobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CArcRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CArcRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CArcRobotDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CArcRobotDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//ABBSocket abbsoc;
	abbsoc.SocketListen();
	addtext(IDC_EDIT2, L"start Listen!");
	abbsoc.SocketAccept();
	addtext(IDC_EDIT2, L"aceepted a controller !");

	/*vector<vector<char *>> targetPos = {
		{ "[757.05,-839.97,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[757.05,-1010.73,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[363.58, -1074.88, 945.65]","[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, 0, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[363.58, -704.45, 934.48]", "[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]", "[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};
	abbsoc.SocketSendPos(targetPos);
	addtext(IDC_EDIT2, L"send over !");*/
	
}

int CArcRobotDlg::addtext(int nID, CString str, bool addition)
{
	CString strOrigin;
	if (addition)
	{
		GetDlgItem(nID)->GetWindowText(strOrigin);
		strOrigin += str;
		strOrigin += "\r\n";
	}
	else
		strOrigin += str;
	GetDlgItem(nID)->SetWindowText(strOrigin);
	CEdit*p = (CEdit*)GetDlgItem(nID); //定义一个指向编辑框的句柄的指针
	p->LineScroll(p->GetLineCount()); //滚动条置底
	return 0;
}

void CArcRobotDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	str += "test display";
	str += "\r\n";
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	CEdit*p = (CEdit*)GetDlgItem(IDC_EDIT2); //定义一个指向编辑框的句柄的指针
	p->LineScroll(p->GetLineCount()); //滚动条置底
}



void CArcRobotDlg::OnBnClickedButton3()
{

	// TODO: 在此添加控件通知处理程序代码

	char* pos;
	CString cpos;
	pos = abbsoc.GetCurPos();
	cout << pos << endl;
	cpos.Format(_T("%s"), CStringW(pos));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	cout << cpos << endl;	
	addtext(IDC_EDIT2,cpos);
	vector<double> posVec=mathc.str2vec(pos);
	//cout << posVec[0] << " " << posVec[1] << " " << posVec[2] << " " << posVec[3] << " " << posVec[4] << " " << posVec[5] << " "  << posVec[6] <<endl;	
	for (int i = 0; i != 7; i++)
	{
		cpos.Format(_T("%.5lf"), posVec[i]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
		//cout << cpos << endl;
		addtext(IDC_EDIT3+i,cpos,false);
	}



}


void CArcRobotDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	abbsoc.SetToZero();
}




void CArcRobotDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	PosSeqDialog PSDiolog;
	PSDiolog.DoModal();
}




void CArcRobotDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	ScanDialog ScanD;
	ScanD.DoModal();
}


void CArcRobotDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CalibrationDlg* pDlg = new CalibrationDlg(this);
	// 创建无模式对话框
	pDlg->Create(IDD_DIALOG3);
	// 移动窗口到主窗口的中央
	pDlg->CenterWindow();
	// 显示更新窗口
	pDlg->ShowWindow(SW_NORMAL);
	pDlg->UpdateWindow();
}


void CArcRobotDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	
//1. 连接机器人，连接传感器进程
	addtext(IDC_EDIT2, L"STEP1!");
	abbsoc.SocketListen();
	addtext(IDC_EDIT2, L"start Listen!");
	abbsoc.SocketAccept();
	addtext(IDC_EDIT2, L"aceepted a controller !");
	sensorsocket0.SocketListen();
	sensorsocket0.SocketAccept();
	//回到原点
	abbsoc.SetToZero();

//2.机器人运动到扫描起点
	addtext(IDC_EDIT2, L"STEP2!");
	FILE* FileOut;
	if (fopen_s(&FileOut, "MoveToStartPos.txt", "r") != 0)
		MessageBox(L"没有此文件", L"提示");
	char content[500];
	vector<vector<char *>> targetPos(100, vector<char *>(6, nullptr));
	int targetNum = 0;
	while (!feof(FileOut))                                   //循环读取每一行，直到文件尾  
	{
		fgets(content, 1024, FileOut);                     //将fp所指向的文件一行内容读到strLine缓冲区 
														   //std::cout << content << std::endl;


														   //char* data1,data2,data3;
		char data1[100] = { 0 }, data2[100] = { 0 }, data3[100] = { 0 }, data4[100] = { 0 };
		char* dataChar = content;
		int i = 0;
		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data1[i] = *dataChar;
		data1[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data2[i] = *dataChar;
		data2[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data3[i] = *dataChar;
		data3[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data4[i] = *dataChar;
		data4[i] = *dataChar;
		targetPos[targetNum][0] = data1;
		targetPos[targetNum][1] = data2;
		targetPos[targetNum][2] = data3;
		targetPos[targetNum][3] = data4;
		targetPos[targetNum][4] = "MoveL";
		targetPos[targetNum][5] = "v50";
		targetNum++;
	}

	abbsoc.SocketSendPos(targetPos,targetNum);
	addtext(IDC_EDIT2, L"Have Moved To Scan Start Position!");


//3.开始扫描，通知机器人控制器与传感器进程开始计时。并获取机器人扫描过程位置数据
	addtext(IDC_EDIT2, L"STEP3!");
	FILE* FileOut0;
	if (fopen_s(&FileOut0, "ScanPosVec.txt", "r") != 0)
		MessageBox(L"没有此文件", L"提示");
	
	targetNum = 0;
	char content0[500];
	vector<vector<char *>> targetPos0(100, vector<char *>(4, nullptr));
	while (!feof(FileOut0))                                   //循环读取每一行，直到文件尾  
	{
		fgets(content0, 1024, FileOut0);                     //将fp所指向的文件一行内容读到strLine缓冲区 
														   //std::cout << content << std::endl;


														   //char* data1,data2,data3;
		char data1[100] = { 0 }, data2[100] = { 0 }, data3[100] = { 0 }, data4[100] = { 0 };
		char* dataChar = content0;
		int i = 0;
		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data1[i] = *dataChar;
		data1[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data2[i] = *dataChar;
		data2[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data3[i] = *dataChar;
		data3[i] = *dataChar;
		dataChar += 2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
			data4[i] = *dataChar;
		data4[i] = *dataChar;
		//std::cout << "data1:" << data1 << std::endl;
		//std::cout << "data2:" << data2 << std::endl;
		//std::cout << "data3:" << data3 << std::endl;
		//std::cout << std::endl;

		targetPos0[targetNum][0] = data1;
		targetPos0[targetNum][1] = data2;
		targetPos0[targetNum][2] = data3;
		targetPos0[targetNum][3] = data4;
		targetNum++;
	}
	fclose(FileOut0);
	sensorsocket0.SocketStart("start");//给传感器进程发送开始命令
	recv(sensorsocket0.sClient, sensorsocket0.read_buf, sizeof(sensorsocket0.read_buf), 0);//给传感器进程发送开始命令
	abbsoc.SocketScan(targetPos0, &ScanStartTime0, targetNum);//位置发送完成立即开始计时
	addtext(IDC_EDIT2, L"Start Scanning!");
	//开始读取机器人位置数据
	CWinThread* mythread = AfxBeginThread(RecvRobotPos, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	
//4.传感器处理得到焊缝位置，发送焊缝相对于传感器位置数据到主控制进程
	addtext(IDC_EDIT2, L"STEP4!");
	addtext(IDC_EDIT2, L"Waitting for Sensor Data Comming!");
	char recvbuf[100];
	int SubFrequency = 0;
	numOfSensorData0 = 0;
	while (sensorsocket0.RecvLine(recvbuf, 100, 0) != 0)
	{
		cout << recvbuf;
		//ZeroMemory(recvbuf, 100);//清空内存recvbuf

		//转换收到的传感器数据，并存入vector中
		if (SubFrequency % 10 == 0)
		{
			//cout << SubFrequency << endl;
			//sscanf_s 严格按照格式来即可
			sscanf_s(recvbuf, "(%lf)x:%lf, y:%lf, z:%lf", &SensorData0[numOfSensorData0][0], &SensorData0[numOfSensorData0][1], &SensorData0[numOfSensorData0][2], &SensorData0[numOfSensorData0][3]);
			numOfSensorData0++;
		}
		SubFrequency++;
	}
	sensorsocket0.closeSocket();
	addtext(IDC_EDIT2, L"SensorData Received!");
	//for (int ii = 0; ii <= SubFrequency/10; ii++)
	//cout << "transformed:" << "x:" << SensorData[ii][0] << "y:" << SensorData[ii][1] << "z:" << SensorData[ii][2] << endl;


//5.通过传感器数据和机器人位置数据计算得到焊缝相对于世界坐标系位置，以及焊接姿态
	//如果本次运行之前未标定传感器，采用上一次标定的结果
	//bool  CalibrationDlg::CalibratedFlag = false;//是否标定的标志
	addtext(IDC_EDIT2, L"STEP5!");
	if (CalibrationDlg::CalibratedFlag == false)
	{
		FILE* FileOut;
		if (fopen_s(&FileOut, "CalibrationResult.txt", "r") != 0)
			MessageBox(L"没有此文件", L"提示");
		char TStr[200];
		for (int Trow = 0; Trow != 4; Trow++)
		{
			fgets(TStr, 200, FileOut);
			sscanf_s(TStr, "%lf %lf %lf %lf", &CalibrationDlg::T(Trow, 0), &CalibrationDlg::T(Trow, 1), &CalibrationDlg::T(Trow, 2), &CalibrationDlg::T(Trow, 3));
		}
		fclose(FileOut);
	}
	cout << "旋转矩阵" << endl;
	cout << CalibrationDlg::T << endl;
	cout << "机器人位置数据：" << endl;
	for (int i = 0; i < numOfRes0; i++)
		cout << "time: " << res0[i][0] << "s  " << res0[i][1] << " " << res0[i][2] << " " << res0[i][3] << " " << res0[i][4] << " " << res0[i][5] << " " << res0[i][6] << " " << res0[i][7] << endl;
	cout << "传感器数据：" << endl;
	for (int i = 0; i < numOfSensorData0; i++)
		cout << "time: " << SensorData0[i][1] << "s  " << SensorData0[i][2] << " " << SensorData0[i][3] << endl;

	//找到焊缝对应时刻机器人位姿，采用线性拟合得到
	vector<vector<double>> fitPos(numOfSensorData0, vector<double>(8, 0.0));
	int numOfFitPos = 0, j = 1;
	double timeStart = res0[0][0];
	for (int i = 0; i != numOfSensorData0; i++)
	{//numOfSensorData0 - i - 1
		fitPos[numOfFitPos][0] = SensorData0[i][1];//发送过来的传感器位置值的时间是逆序的
		while (fitPos[numOfFitPos][0] > timeStart && j < numOfRes0)
		{
			timeStart = res0[j++][0];
		}
		if (fitPos[numOfFitPos][0]<res0[0][0])
			continue;
		if (fitPos[numOfFitPos][0] >= res0[numOfRes0 - 1][0])
			break;
		vector<double> TemRes(6, 0.0);
		for (int ind = 0; ind != 6; ind++)
			TemRes[ind] = (fitPos[numOfFitPos][0] - res0[j - 2][0]) / (res0[j - 1][0] - res0[j - 2][0])*(res0[j - 1][ind + 1] - res0[j - 2][ind + 1]) + res0[j - 2][ind + 1];

		//坐标变换得到焊缝位置值
		Matrix4d EndP;
		//1.将xyzabc转换成T矩阵形式
		double alfa = TemRes[3] / 180 * 3.1415926;
		double beta = TemRes[4] / 180 * 3.1415926;
		double gama = TemRes[5] / 180 * 3.1415926;
		vector<double> temR{ cos(alfa)*cos(beta), cos(alfa)*sin(beta)*sin(gama) - sin(alfa)*cos(gama), cos(alfa)*sin(beta)*cos(gama) + sin(alfa)*sin(gama),
			sin(alfa)*cos(beta), sin(alfa)*sin(beta)*sin(gama) + cos(alfa)*cos(gama), sin(alfa)*sin(beta)*cos(gama) - cos(alfa)*sin(gama),
			-sin(beta), cos(beta)*sin(gama), cos(beta)*cos(gama) };
		for (int Trow = 0; Trow != 3; Trow++)
			for (int Tcol = 0; Tcol != 3; Tcol++)
				EndP(Trow, Tcol) = temR[Trow * 3 + Tcol];
		EndP(0, 3) = TemRes[0]; EndP(1, 3) = TemRes[1]; EndP(2, 3) = TemRes[2];
		EndP(3, 0) = 0; EndP(3, 1) = 0; EndP(3, 2) = 0; EndP(3, 2) = 1;

		//2.利用矩阵相乘得到位置和姿态
		Matrix4d TemRot(EndP*CalibrationDlg::T);
		Vector4d SensorDelta;
		SensorDelta << 0, SensorData0[i][2], SensorData0[i][3], 1;
		Vector4d TemPos(EndP*CalibrationDlg::T*SensorDelta);
		//3.T矩阵转换成xyzabc形式并赋值到fitPos
		fitPos[numOfFitPos][1] = TemPos(0);
		fitPos[numOfFitPos][2] = TemPos(1);
		fitPos[numOfFitPos][3] = TemPos(2);

		Matrix3d t_R;
		t_R(0, 0) = EndP(0, 0); t_R(0, 1) = EndP(0, 1); t_R(0, 2) = EndP(0, 2);
		t_R(1, 0) = EndP(1, 0); t_R(1, 1) = EndP(1, 1); t_R(1, 2) = EndP(1, 2);
		t_R(2, 0) = EndP(2, 0); t_R(2, 1) = EndP(2, 1); t_R(2, 2) = EndP(2, 2);
		Quaterniond Q3(t_R);
		//fitPos[numOfFitPos][4] = Q3.coeffs()(0);
		//fitPos[numOfFitPos][5] = Q3.coeffs()(1);
		//fitPos[numOfFitPos][6] = Q3.coeffs()(2);
		//fitPos[numOfFitPos][7] = Q3.coeffs()(3);
		//目前没有计算焊接姿态，先采用固定姿态 quat=[0.01074,-0.36312,0.80240,-0.47348]
		fitPos[numOfFitPos][4] = 0.01074;
		fitPos[numOfFitPos][5] = 0.36312;
		fitPos[numOfFitPos][6] = 0.80240;
		fitPos[numOfFitPos][7] = -0.47348;
		//cout << "t_R: " << t_R << endl;
		//cout << "Quaternion3: " << endl << Q3.coeffs() << endl;

		//计算下一个焊缝点
		numOfFitPos++;

	}
	addtext(IDC_EDIT2, L"Finished caculating real position!");
	for (int i = 0; i < numOfFitPos; i++)
		//cout << "time: " << fitPos[i][0] << "s  " << fitPos[i][1] << " " << fitPos[i][2] << " " << fitPos[i][3] << " " << fitPos[i][4] << " " << fitPos[i][5] << " " << fitPos[i][6] << " " << fitPos[i][6]<< endl;
		cout << "[" << fitPos[i][1] << ", " << fitPos[i][2] << " " << fitPos[i][3] << "]" << " [" << fitPos[i][4] << " " << fitPos[i][5] << " " << fitPos[i][6] << " " << fitPos[i][7] << "]" << "[0, 0, 0, 0] [9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" << endl;


	//6.发送位置使机器人运动
	addtext(IDC_EDIT2, L"STEP6!");
	vector<vector<char *>> targetPos1(numOfFitPos/5 + 2, vector<char *>(6, nullptr));
	for (int i = 0; i != numOfFitPos / 5 + 2; i++)
	{
		for(int j=0;j!=6;j++)
		{	
			char *fitStr=new char[200];
			targetPos1[i][j] = fitStr;
		}
	
	}
	//[731.5, 650.5, 533.4][0.00640, -0.13130, 0.98885, 0.06989]
	sprintf_s(targetPos1[0][0],200, "[343.32,-632.11,828.00]");
	sprintf_s(targetPos1[0][1], 200, "[0.01074,0.36312,0.80240,-0.47348]");
	sprintf_s(targetPos1[0][2], 200, "[-1,-1,0,0]");
	sprintf_s(targetPos1[0][3], 200, "[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]");
	sprintf_s(targetPos1[0][4], 200, "MoveL");
	sprintf_s(targetPos1[0][5], 200, "v50");
	//-0.5422    0.5927 - 0.5956
	//0.8333    0.2886 - 0.4715
	//- 0.1076 - 0.7520 - 0.6503
	// -10 * [-0.5956, -0.4715, -0.6503]
	//ans =
	//5.9560    4.7150    6.5030
	for (int i = 1; i < numOfFitPos/5 + 1; i++)
	{
		sprintf_s(targetPos1[i][0], 200, "[%lf, %lf, %lf]", fitPos[i * 5-1][1]+ 6, fitPos[i * 5 - 1][2]-1, fitPos[i * 5 - 1][3]+ 6.503);
		sprintf_s(targetPos1[i][1], 200, "[%lf, %lf, %lf, %lf]",fitPos[i*5 - 1][4],fitPos[i*5 - 1][5],fitPos[i*5 - 1][6],fitPos[i*5 - 1][7]);
		sprintf_s(targetPos1[i][2], 200, "[-1, -1, 0, 0]");
		sprintf_s(targetPos1[i][3], 200, "[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]");
		sprintf_s(targetPos1[i][4], 200, "ArcL");
		sprintf_s(targetPos1[i][5], 200, "v50");
	}
	sprintf_s(targetPos1[numOfFitPos / 5 + 1][0], 200, "[%lf, %lf, %lf]", fitPos[numOfFitPos - 1][1] + 6, fitPos[numOfFitPos - 1][2]-1, fitPos[numOfFitPos - 1][3] + 6.503);
	sprintf_s(targetPos1[numOfFitPos / 5 + 1][1], 200, "[%lf, %lf, %lf, %lf]", fitPos[numOfFitPos - 1][4], fitPos[numOfFitPos - 1][5], fitPos[numOfFitPos - 1][6], fitPos[numOfFitPos - 1][7]);
	sprintf_s(targetPos1[numOfFitPos / 5 + 1][2], 200, "[-1, -1, 0, 0]");
	sprintf_s(targetPos1[numOfFitPos / 5 + 1][3], 200, "[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]");
	sprintf_s(targetPos1[numOfFitPos / 5 + 1][4], 200, "ArcLEnd");
	sprintf_s(targetPos1[numOfFitPos / 5 + 1][5], 200, "v50");

	sprintf_s(targetPos1[1][4], 200, "MoveL");
	sprintf_s(targetPos1[2][4], 200, "ArcLStart");

	addtext(IDC_EDIT2, L"LET US MOVE!");
	abbsoc.SocketSendPos(targetPos1, numOfFitPos/5 + 2,false);
	
}

UINT CArcRobotDlg::RecvRobotPos(LPVOID lpParam)
{
	char* pos;
	int rval;
	numOfRes0 = 0;
	pos = abbsoc.SocketPosRecv(&rval);

	while (rval != -1)
	{
		sscanf_s(pos, "%lf[%lf,%lf,%lf][%lf,%lf,%lf]", &res0[numOfRes0][0], &res0[numOfRes0][1], &res0[numOfRes0][2], &res0[numOfRes0][3], &res0[numOfRes0][4], &res0[numOfRes0][5], &res0[numOfRes0][6]);
		//cout << "controller time:" << res[numOfRes][0] << endl;
		//calwl.calWeldLinePos(res[numOfRes], RealPos[numOfRes]);
		numOfRes0++;
		pos = abbsoc.SocketPosRecv(&rval);
	}

	return 0;
}


vector<vector<double>> CArcRobotDlg::res0;//机器人位置带时间戳
int CArcRobotDlg::numOfRes0;//机器人位置计数

vector<vector<double>> CArcRobotDlg::SensorData0;//传感器焊缝位置
int CArcRobotDlg::numOfSensorData0;//传感器焊缝计数

//vector<vector<double>> CArcRobotDlg::RealPos;
ABBSocket CArcRobotDlg::abbsoc;
DWORD CArcRobotDlg::ScanStartTime0;
DWORD CArcRobotDlg::GetWeldLineTime0;
int CArcRobotDlg::SensorPosCount0;
bool  CalibrationDlg::CalibratedFlag = false;//是否标定的标志
