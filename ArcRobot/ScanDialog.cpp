// ScanDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ArcRobot.h"
#include "ScanDialog.h"
#include "afxdialogex.h"


// ScanDialog 对话框

IMPLEMENT_DYNAMIC(ScanDialog, CDialogEx)

ScanDialog::ScanDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

ScanDialog::~ScanDialog()
{
}

void ScanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, SeqList);
	DDX_Control(pDX, IDC_LIST2, PosList2);
}


BEGIN_MESSAGE_MAP(ScanDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ScanDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ScanDialog::OnBnClickedButton2)
//	ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON3, &ScanDialog::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &ScanDialog::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &ScanDialog::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &ScanDialog::OnBnClickedButton6)
END_MESSAGE_MAP()


// ScanDialog 消息处理程序


BOOL ScanDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//类内数据集合维度初始化
	res.resize(1000);
	for (int i = 0; i != 1000; i++)
		res[i].resize(10);
	RealPos.resize(1000);
	for (int i = 0; i != 1000; i++)
		RealPos[i].resize(7);

	SensorData.resize(1000);
	for (int i = 0; i != 1000; i++)
		SensorData[i].resize(4);

	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	SeqList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	SeqList.SetExtendedStyle(SeqList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列 
	SeqList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 10, 0);
	SeqList.InsertColumn(1, _T("空间坐标"), LVCFMT_CENTER, rect.Width() / 5, 1);
	SeqList.InsertColumn(2, _T("四元数"), LVCFMT_CENTER, rect.Width() / 5 + rect.Width() / 10, 2);
	SeqList.InsertColumn(3, _T("关节状态"), LVCFMT_CENTER, rect.Width() / 5, 3);
	SeqList.InsertColumn(4, _T("第七轴"), LVCFMT_CENTER, rect.Width() / 5, 4);



	// 获取编程语言列表视图控件的位置和大小   
	PosList2.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	PosList2.SetExtendedStyle(PosList2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列 
	PosList2.InsertColumn(0, _T("时间戳"), LVCFMT_CENTER, rect.Width() / 8, 0);
	PosList2.InsertColumn(1, _T("空间坐标"), LVCFMT_CENTER, rect.Width() / 4, 1);
	PosList2.InsertColumn(2, _T("四元数"), LVCFMT_CENTER, rect.Width() / 4 + rect.Width() / 8, 2);
	PosList2.InsertColumn(3, _T("焊缝坐标"), LVCFMT_CENTER, rect.Width() / 4, 3);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ScanDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		//SetDlgItemText(IDC_EDIT13, strFilePath);
	}

	//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
	//char * pFileName = W2A(str); //也可实现转换
	USES_CONVERSION;
	char* filePath = T2A(strFilePath);;

	FILE* FileOut;
	if (fopen_s(&FileOut, filePath, "r") != 0)
		MessageBox(L"没有此文件", L"提示");
	char content[500];
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

		//std::cout << "data1:" << data1 << std::endl;
		//std::cout << "data2:" << data2 << std::endl;
		//std::cout << "data3:" << data3 << std::endl;
		//std::cout << std::endl;


		CString LineNumStr, posStr, qStr, StateStr, ExtraStr;
		int nHeadNum = SeqList.GetItemCount();

		LineNumStr.Format(_T("%d"), nHeadNum + 1);
		posStr.Format(_T("%s"), CStringW(data1));
		qStr.Format(_T("%s"), CStringW(data2));
		StateStr.Format(_T("%s"), CStringW(data3));
		ExtraStr.Format(_T("%s"), CStringW(data4));

		SeqList.InsertItem(nHeadNum, LineNumStr);
		SeqList.SetItemText(nHeadNum, 1, posStr);
		SeqList.SetItemText(nHeadNum, 2, qStr);
		SeqList.SetItemText(nHeadNum, 3, StateStr);
		SeqList.SetItemText(nHeadNum, 4, ExtraStr);
	}
}


void ScanDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nHeadNum = SeqList.GetItemCount();
	CString data1, data2, data3, data4;
	vector<vector<char *>> targetPos(nHeadNum, vector<char *>(4, nullptr));
	for (int i = 0; i != nHeadNum; i++)
	{
		data1 = SeqList.GetItemText(i, 1);
		data2 = SeqList.GetItemText(i, 2);
		data3 = SeqList.GetItemText(i, 3);
		data4 = SeqList.GetItemText(i, 4);
		USES_CONVERSION;
		targetPos[i][0] = T2A(data1);
		targetPos[i][1] = T2A(data2);
		targetPos[i][2] = T2A(data3);
		targetPos[i][3] = T2A(data4);
	}
	
	abbsoc.SocketScan(targetPos, &ScanStartTime);




	//开始读取传感器数据
	/*
	TIMECAPS   tc;
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
	{
		// Error; application can't continue.  
	}
	UINT wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	timeBeginPeriod(wTimerRes);

	
	MMRESULT timeSetEventRslt = timeSetEvent(
		100,               // delay  
		1,               // resolution (global variable)  
		OneShotTimer,    // callback function  
		wTimerRes,       // user data  
		TIME_PERIODIC | TIME_CALLBACK_FUNCTION | TIME_KILL_SYNCHRONOUS); // periodic call to callback func 
	

	if (timeSetEventRslt == NULL) MessageBox(_T("TimeSetEvent fail. Maybe delay is not in the range of the minimum and maximum "));
    */

	//创建新的进程来接受机器人控制器传过来的位置
	CWinThread* mythread = AfxBeginThread(RecvAndDisplay, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

	//timeEndPeriod(wTimerRes);         //对应timeBeginPeriod  
	//timeKillEvent(timeSetEventRslt);  //对应timeSetEventRslt  
	
}


//void ScanDialog::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	calwl.GetSensorPos(&res[SensorPosCount++][8], &res[SensorPosCount++][9], &GetWeldLineTime);//接收到传感器传回来的焊缝坐标的时间，可以认为是焊缝坐标采集时间戳
//	double sensorTime(GetWeldLineTime - ScanStartTime);
//	cout << "Sensor time:" << " " << sensorTime / 1000 << "		";
//	CDialogEx::OnTimer(nIDEvent);
//}

/*
void CALLBACK ScanDialog::OneShotTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//AfxMessageBox(_T("CALLBACK Success!"));  
	calwl.GetSensorPos(&res[SensorPosCount++][8], &res[SensorPosCount++][9], &GetWeldLineTime);//接收到传感器传回来的焊缝坐标的时间，可以认为是焊缝坐标采集时间戳
	double sensorTime(GetWeldLineTime - ScanStartTime);
	cout << "Sensor time:" << " " << sensorTime / 1000 << "		";
}
*/

UINT ScanDialog::RecvAndDisplay(LPVOID lpParam)
{
	char* pos;
	int rval;
	numOfRes = 0;
	pos = abbsoc.SocketPosRecv(&rval);

	while (rval != -1)
	{
		sscanf_s(pos, "%lf[%lf,%lf,%lf][%lf,%lf,%lf]", &res[numOfRes][0], &res[numOfRes][1], &res[numOfRes][2], &res[numOfRes][3], &res[numOfRes][4], &res[numOfRes][5], &res[numOfRes][6]);
		//cout << "controller time:" << res[numOfRes][0] << endl;
		//calwl.calWeldLinePos(res[numOfRes], RealPos[numOfRes]);

		CString TimeStr, posStr, qStr, SensorStr;
		int nHeadNum = PosList2.GetItemCount();
		TimeStr.Format(_T("%.4lf"), res[numOfRes][0]);
		posStr.Format(_T("[%.4lf, %.4lf, %.4lf]"), res[numOfRes][1], res[numOfRes][2], res[numOfRes][3]);
		qStr.Format(_T("[%.6lf, %.6lf, %.6lf, %.6lf]"), res[numOfRes][4], res[numOfRes][5], res[numOfRes][6], res[numOfRes][7]);
		SensorStr.Format(_T("[%.4lf, %.4lf]"), res[numOfRes][8], res[numOfRes][9]);

		PosList2.InsertItem(nHeadNum, TimeStr);
		PosList2.SetItemText(nHeadNum, 1, posStr);
		PosList2.SetItemText(nHeadNum, 2, qStr);
		PosList2.SetItemText(nHeadNum, 3, SensorStr);
		//UpdateWindow();
		PosList2.EnsureVisible(nHeadNum, false);

		numOfRes++;
		pos = abbsoc.SocketPosRecv(&rval);
	}
	return 0;
}


void ScanDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Simulation Sim;
	Sim.DoModal();
}


void ScanDialog::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	sensorsocket.SocketListen();
	sensorsocket.SocketAccept();
	sensorsocket.SocketStart("start");
	char recvbuf[100];
	int SubFrequency = 0;
	while (sensorsocket.RecvLine(recvbuf,100,0) != 0)
	{
		//cout << recvbuf;
		//ZeroMemory(recvbuf, 100);//清空内存recvbuf

		//转换收到的传感器数据，并存入vector中
		if (SubFrequency % 10 == 0)
		{			
			//cout << SubFrequency << endl;
			//sscanf_s 严格按照格式来即可
			sscanf_s(recvbuf, "(%lf)x:%lf, y:%lf, z:%lf", &SensorData[numOfSensorData][0], &SensorData[numOfSensorData][1], &SensorData[numOfSensorData][2], &SensorData[numOfSensorData][3]);
			numOfSensorData++;
		}
		SubFrequency++;
	}

	//for (int ii = 0; ii <= SubFrequency/10; ii++)
		//cout << "transformed:" << "x:" << SensorData[ii][0] << "y:" << SensorData[ii][1] << "z:" << SensorData[ii][2] << endl;
	
}

void ScanDialog::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	cout << "in ScanDLG:" << endl;
	cout << CalibrationDlg::T << endl;
}


void ScanDialog::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果本次运行之前未标定传感器，采用上一次标定的结果
	//bool  CalibrationDlg::CalibratedFlag = false;//是否标定的标志
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
	for (int i = 0; i < numOfRes; i++)
		cout << "time: " << res[i][0] << "s  " << res[i][1] << " " << res[i][2] << " " << res[i][3] << " " << res[i][4] << " " << res[i][5] << " " << res[i][6] << " " << res[i][7] << endl;
	cout << "传感器数据：" << endl;
	for (int i = 0; i < numOfSensorData; i++)
		cout << "time: " << SensorData[i][1] << "s  " << SensorData[i][2] << " " << SensorData[i][3] << endl;
	
	//找到焊缝对应时刻机器人位姿，采用线性拟合得到
	vector<vector<double>> fitPos(numOfSensorData ,vector<double> (8,0.0));
	int numOfFitPos = 0, j = 1;
	double timeStart = res[0][0];
	for (int i = 0; i != numOfSensorData; i++)
	{
		fitPos[numOfFitPos][0] = SensorData[numOfSensorData - i - 1][1];//发送过来的传感器位置值的时间是逆序的
		while (fitPos[numOfFitPos][0] > timeStart)
		{
			timeStart = res[j++][0];
		}
		if (fitPos[numOfFitPos][0]<res[0][0])
			continue;
		if(fitPos[numOfFitPos][0] >= res[numOfRes-1][0])
			break;
		vector<double> TemRes(6, 0.0);
		for (int ind = 0; ind != 6; ind++)
			TemRes[ind] = (fitPos[numOfFitPos][0] - res[j - 2][0]) / (res[j-1][0] - res[j - 2][0])*(res[j-1][ind + 1]-res[j-2][ind + 1])+res[j-2][ind + 1];
		
		//坐标变换得到焊缝位置值
		Matrix4d EndP;
		//1.将xyzabc转换成T矩阵形式
		double alfa = TemRes[3];
		double beta = TemRes[4];
		double gama = TemRes[5];
		vector<double> temR{ cos(alfa)*cos(beta), cos(alfa)*sin(beta)*sin(gama) - sin(alfa)*cos(gama), cos(alfa)*sin(beta)*cos(gama) + sin(alfa)*sin(gama),
			sin(alfa)*cos(beta), sin(alfa)*sin(beta)*sin(gama) + cos(alfa)*cos(gama), sin(alfa)*sin(beta)*cos(gama) - cos(alfa)*sin(gama),
			-sin(beta), cos(beta)*sin(gama), cos(beta)*cos(gama) };
		for (int Trow = 0; Trow != 3; Trow++)
			for (int Tcol = 0; Tcol != 3; Tcol++)
				EndP(Trow,Tcol) = temR[Trow * 3 + Tcol];
		EndP(0, 3) = TemRes[0]; EndP(1, 3) = TemRes[1]; EndP(2, 3) = TemRes[2];
		EndP(3, 0) = 0; EndP(3, 1) = 0; EndP(3, 2) = 0; EndP(3, 2) = 1;

		//2.利用矩阵相乘得到位置和姿态
		Matrix4d TemPos(EndP*CalibrationDlg::T);		
		
		//3.T矩阵转换成xyzabc形式并赋值到fitPos
		fitPos[numOfFitPos][1] = TemPos(0, 3);
		fitPos[numOfFitPos][2] = TemPos(1, 3);
		fitPos[numOfFitPos][3] = TemPos(2, 3);

		Matrix3d t_R;
		t_R(0, 0) = EndP(0, 0); t_R(0, 1) = EndP(0, 1); t_R(0, 2) = EndP(0, 2);
		t_R(1, 0) = EndP(1, 0); t_R(1, 1) = EndP(1, 1); t_R(1, 2) = EndP(1, 2);
		t_R(2, 0) = EndP(2, 0); t_R(2, 1) = EndP(2, 1); t_R(2, 2) = EndP(2, 2);
		Quaterniond Q3(t_R);
		fitPos[numOfFitPos][4] = Q3.coeffs()(0);
		fitPos[numOfFitPos][5] = Q3.coeffs()(1);
		fitPos[numOfFitPos][6] = Q3.coeffs()(2);
		fitPos[numOfFitPos][7] = Q3.coeffs()(3);
		//cout << "t_R: " << t_R << endl;
		//cout << "Quaternion3: " << endl << Q3.coeffs() << endl;

		//计算下一个焊缝点
		numOfFitPos++;
		
	}
	for (int i = 0; i < numOfFitPos; i++)
		cout << "time: " << fitPos[i][0] << "s  " << fitPos[i][1] << " " << fitPos[i][2] << " " << fitPos[i][3] << " " << fitPos[i][4] << " " << fitPos[i][5] << " " << fitPos[i][6] << " " << fitPos[i][6]<< endl;
}

CListCtrl ScanDialog::PosList2;
vector<vector<double>> ScanDialog::res;//机器人位置带时间戳
int ScanDialog::numOfRes;//机器人位置计数
vector<vector<double>> ScanDialog::SensorData;//传感器焊缝位置
int ScanDialog::numOfSensorData;//传感器焊缝计数
vector<vector<double>> ScanDialog::RealPos;
ABBSocket ScanDialog::abbsoc;
calWeldLine ScanDialog::calwl;
DWORD ScanDialog::ScanStartTime;
DWORD ScanDialog::GetWeldLineTime;
int ScanDialog::SensorPosCount;
bool  CalibrationDlg::CalibratedFlag = false;//是否标定的标志