// CalibrationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ArcRobot.h"
#include "CalibrationDlg.h"
#include "afxdialogex.h"


// CalibrationDlg 对话框

IMPLEMENT_DYNAMIC(CalibrationDlg, CDialogEx)

CalibrationDlg::CalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CalibrationDlg::~CalibrationDlg()
{
}

void CalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, clbrtl);
}


BEGIN_MESSAGE_MAP(CalibrationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CalibrationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON12, &CalibrationDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CalibrationDlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CalibrationDlg 消息处理程序


BOOL CalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CFont * f;
	f = new CFont;
	f->CreateFont(36, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		TRUE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("Arial")); // lpszFac 

	GetDlgItem(IDC_STATICEdit)->SetFont(f);

	
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	clbrtl.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	clbrtl.SetExtendedStyle(clbrtl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列 
	clbrtl.InsertColumn(0, _T("标定点位置"), LVCFMT_CENTER, rect.Width() / 4, 0);
	clbrtl.InsertColumn(1, _T("机器人末端位姿"), LVCFMT_CENTER, rect.Width() / 2, 1);
	clbrtl.InsertColumn(2, _T("焊缝位置"), LVCFMT_CENTER, rect.Width() / 4, 2);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CalibrationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CalibrationDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	// 从表格中获取数据，然后调用标定算法标定

	int nHeadNum = clbrtl.GetItemCount();
	CString data1, data2, data3;
	char *dataChar1, *dataChar2, *dataChar3;
	vector<vector<char *>> clbrtDataChar(nHeadNum, vector<char *>(3, nullptr));
	for (int i = 0; i != nHeadNum; i++)
	{
		data1 = clbrtl.GetItemText(i, 0);
		data2 = clbrtl.GetItemText(i, 1);
		data3 = clbrtl.GetItemText(i, 2);
		USES_CONVERSION;
		clbrtDataChar[i][0] = T2A(data1);
		clbrtDataChar[i][1] = T2A(data2);
		clbrtDataChar[i][2] = T2A(data3);
	}

	vector<CaliStruct> cst(nHeadNum,CaliStruct());

	//clbrtDataChar[0][0];
	for (int i = 0; i != nHeadNum; i++)
	{
		sscanf_s(clbrtDataChar[i][0], "[%lf,%lf,%lf]", &cst[i].pointPos[0], &cst[i].pointPos[1], &cst[i].pointPos[2]);
		sscanf_s(clbrtDataChar[i][1], "[%lf,%lf,%lf,%lf,%lf,%lf]", &cst[i].EndPos[0], &cst[i].EndPos[1], &cst[i].EndPos[2], &cst[i].rpy[0], &cst[i].rpy[1], &cst[i].rpy[2]);
		sscanf_s(clbrtDataChar[i][2], "[%lf,%lf]", &cst[i].delta[0], &cst[i].delta[1]);
		calibration.AddCaliData(cst[i]);
	}
	Matrix4d T = calibration.calculateT();
	CString TCstring;
	TCstring.Format(_T("%.5lf"), T(0, 0));
	GetDlgItem(IDC_EDIT2)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(0, 1));
	GetDlgItem(IDC_EDIT3)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(0, 2));
	GetDlgItem(IDC_EDIT4)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(0, 3));
	GetDlgItem(IDC_EDIT5)->SetWindowText(TCstring);

	TCstring.Format(_T("%.5lf"), T(1, 0));
	GetDlgItem(IDC_EDIT6)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(1, 1));
	GetDlgItem(IDC_EDIT7)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(1, 2));
	GetDlgItem(IDC_EDIT8)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(1, 3));
	GetDlgItem(IDC_EDIT9)->SetWindowText(TCstring);

	TCstring.Format(_T("%.5lf"), T(2, 0));
	GetDlgItem(IDC_EDIT10)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(2, 1));
	GetDlgItem(IDC_EDIT21)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(2, 2));
	GetDlgItem(IDC_EDIT22)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(2, 3));
	GetDlgItem(IDC_EDIT23)->SetWindowText(TCstring);

	TCstring.Format(_T("%.5lf"), T(3, 0));
	GetDlgItem(IDC_EDIT24)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(3, 1));
	GetDlgItem(IDC_EDIT25)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(3, 2));
	GetDlgItem(IDC_EDIT26)->SetWindowText(TCstring);
	TCstring.Format(_T("%.5lf"), T(3, 3));
	GetDlgItem(IDC_EDIT27)->SetWindowText(TCstring);




	//	cst[0].delta[0] = 7.41; cst[0].delta[1] = 4.66;
	//	cst[0].EndPos[0] = 557.99; cst[0].EndPos[1] = -465.86; cst[0].EndPos[2] = 636.39;
	//	cst[0].pointPos[0] = 773.2; cst[0].pointPos[1] = -457.9; cst[0].pointPos[2] = 219.81;
	//	cst[0].rpy[0] = 117.28 / 180 * 3.1415926; cst[0].rpy[1] = 5.89 / 180 * 3.1415926; cst[0].rpy[2] = 163.77 / 180 * 3.1415926;
	//	clbrt.AddCaliData(cst[0]);

}


void CalibrationDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
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
	char* filePath = T2A(strFilePath);

	FILE* FileOut;
	if (fopen_s(&FileOut, filePath, "r") != 0)
		MessageBox(L"没有此文件", L"提示");
	char content[500];
	while (!feof(FileOut))                                   //循环读取每一行，直到文件尾  
	{
		fgets(content, 1024, FileOut);                     //将fp所指向的文件一行内容读到strLine缓冲区 
														   //std::cout << content << std::endl;


														   //char* data1,data2,data3;
		char data1[100] = { 0 }, data2[100] = { 0 }, data3[100] = { 0 };
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

		//std::cout << "data1:" << data1 << std::endl;
		//std::cout << "data2:" << data2 << std::endl;
		//std::cout << "data3:" << data3 << std::endl;
		//std::cout << std::endl;


		CString  posStr, EndStr, SensorStr;
		int nHeadNum = clbrtl.GetItemCount();

		posStr.Format(_T("%s"), CStringW(data1));
		EndStr.Format(_T("%s"), CStringW(data2));
		SensorStr.Format(_T("%s"), CStringW(data3));

		clbrtl.InsertItem(nHeadNum, posStr);
		clbrtl.SetItemText(nHeadNum, 1, EndStr);
		clbrtl.SetItemText(nHeadNum, 2, SensorStr);
		UpdateWindow();
		clbrtl.EnsureVisible(nHeadNum, false);
	}
}
