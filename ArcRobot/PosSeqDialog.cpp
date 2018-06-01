// PosSeqDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include "stdlib.h"
#include "ArcRobot.h"
#include "PosSeqDialog.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;


// PosSeqDialog 对话框

IMPLEMENT_DYNAMIC(PosSeqDialog, CDialogEx)

PosSeqDialog::PosSeqDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

PosSeqDialog::~PosSeqDialog()
{
}

void PosSeqDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, PosList);
}


BEGIN_MESSAGE_MAP(PosSeqDialog, CDialogEx)
//	ON_WM_ACTIVATE()
//	ON_WM_CREATE()
ON_BN_CLICKED(IDC_BUTTON1, &PosSeqDialog::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &PosSeqDialog::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON12, &PosSeqDialog::OnBnClickedButton12)
ON_BN_CLICKED(IDC_BUTTON10, &PosSeqDialog::OnBnClickedButton10)
ON_BN_CLICKED(IDC_BUTTON3, &PosSeqDialog::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON11, &PosSeqDialog::OnBnClickedButton11)
END_MESSAGE_MAP()


// PosSeqDialog 消息处理程序

BOOL PosSeqDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	PosList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	PosList.SetExtendedStyle(PosList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列 
	PosList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 10, 0);
	PosList.InsertColumn(1, _T("空间坐标"), LVCFMT_CENTER, rect.Width() / 5, 1);
	PosList.InsertColumn(2, _T("四元数"), LVCFMT_CENTER, rect.Width() / 5+rect.Width() / 10, 2);
	PosList.InsertColumn(3, _T("关节状态"), LVCFMT_CENTER, rect.Width() / 5, 3);
	PosList.InsertColumn(4, _T("第七轴"), LVCFMT_CENTER, rect.Width() / 5, 4);

	// 在列表视图控件中插入列表项，并设置列表子项文本   
	//PosList.InsertItem(0, _T("Java"));
	//PosList.SetItemText(0, 1, _T("1"));
	//PosList.SetItemText(0, 2, _T("1"));
	//PosList.SetItemText(0, 3, _T("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void PosSeqDialog::OnBnClickedButton1()
{
	CString LineNumStr,posStr,qStr,StateStr,extra;
	// TODO: 在此添加控件通知处理程序代码

	//判断输入是否有效


	GetDlgItem(IDC_EDIT1)->GetWindowText(posStr);
	GetDlgItem(IDC_EDIT11)->GetWindowText(qStr);
	GetDlgItem(IDC_EDIT12)->GetWindowText(StateStr);
	GetDlgItem(IDC_EDIT28)->GetWindowText(extra);

	int nHeadNum =PosList.GetItemCount();

	LineNumStr.Format(_T("%d"),nHeadNum+1 );
	PosList.InsertItem(nHeadNum, LineNumStr);
	PosList.SetItemText(nHeadNum, 1, posStr);
	PosList.SetItemText(nHeadNum, 2, qStr);
	PosList.SetItemText(nHeadNum, 3, StateStr);
	PosList.SetItemText(nHeadNum, 4, extra);
}


void PosSeqDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int column=PosList.GetSelectionMark();        //选择一行
	if (column == -1 || PosList.GetItemState(column, LVIS_SELECTED) != LVIS_SELECTED)
	{
		MessageBox(L"请选择一行，再进行删除", L"尚未选择要删除的行");
		column = -1;
	}
	//bool selected = PosList.GetItemState(column, LVIS_SELECTED) != LVIS_SELECTED;
	PosList.DeleteItem(column);
	CString LineNumStr;
	int nHeadNum = PosList.GetItemCount();
	for (int i = column; i != nHeadNum; i++)
	{
		LineNumStr.Format(_T("%d"), i+1);
		PosList.SetItemText(i, 0, LineNumStr);
	}
}


void PosSeqDialog::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT11)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT12)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT28)->SetWindowText(_T(""));
}


void PosSeqDialog::OnBnClickedButton10()
{
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
		SetDlgItemText(IDC_EDIT13, strFilePath);
	}

	//调用函数，T2A和W2A均支持ATL和MFC中的字符转换
	//char * pFileName = W2A(str); //也可实现转换
	USES_CONVERSION;
	char* filePath= T2A(strFilePath);;

	FILE* FileOut;
	if(fopen_s(&FileOut, filePath, "r")!=0)
		MessageBox(L"没有此文件", L"提示");
	char content[500];
	while (!feof(FileOut))                                   //循环读取每一行，直到文件尾  
	{
		fgets(content, 1024, FileOut);                     //将fp所指向的文件一行内容读到strLine缓冲区 
		//std::cout << content << std::endl;


		//char* data1,data2,data3;
		char data1[100] = {0}, data2[100]= {0}, data3[100]= {0}, data4[100]= {0};
		char* dataChar=content;
		int i = 0;
		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data1[i] = *dataChar;
		data1[i] = *dataChar;
		dataChar+=2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data2[i] = *dataChar;
		data2[i] = *dataChar;
		dataChar+=2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data3[i] = *dataChar;
		data3[i] = *dataChar;
		dataChar+=2;

		for (i = 0; *dataChar != ']'; i++, dataChar++)
				data4[i] = *dataChar;
		data4[i] = *dataChar;

		//std::cout << "data1:" << data1 << std::endl;
		//std::cout << "data2:" << data2 << std::endl;
		//std::cout << "data3:" << data3 << std::endl;
		//std::cout << std::endl;


		CString LineNumStr, posStr, qStr, StateStr,ExtraStr;
		int nHeadNum = PosList.GetItemCount();

		LineNumStr.Format(_T("%d"), nHeadNum + 1);
		posStr.Format(_T("%s"), CStringW(data1));
		qStr.Format(_T("%s"), CStringW(data2));
		StateStr.Format(_T("%s"), CStringW(data3));
		ExtraStr.Format(_T("%s"), CStringW(data4));

		PosList.InsertItem(nHeadNum, LineNumStr);
		PosList.SetItemText(nHeadNum, 1, posStr);
		PosList.SetItemText(nHeadNum, 2, qStr);
		PosList.SetItemText(nHeadNum, 3, StateStr);
		PosList.SetItemText(nHeadNum, 4, ExtraStr);

	}
}


void PosSeqDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int nHeadNum = PosList.GetItemCount();
	CString data1, data2, data3, data4;
	//添加焊接，直线圆弧，速度等选项到target中
	vector<vector<char *>> targetPos(nHeadNum, vector<char *>(6, nullptr));
	for (int i = 0; i != nHeadNum; i++)
	{
		data1 = PosList.GetItemText(i, 1);
		data2 = PosList.GetItemText(i, 2);
		data3 = PosList.GetItemText(i, 3);
		data4 = PosList.GetItemText(i, 4);
		USES_CONVERSION;
		targetPos[i][0] = T2A(data1);
		targetPos[i][1] = T2A(data2);
		targetPos[i][2] = T2A(data3);
		targetPos[i][3] = T2A(data4);
		targetPos[i][4] = "ArcL";
		targetPos[i][5] = "v10";
	}

	abbsoc.SocketSendPos(targetPos,targetPos.size());
}


void PosSeqDialog::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
}
