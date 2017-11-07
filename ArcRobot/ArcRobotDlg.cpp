
// ArcRobotDlg.cpp : 实现文件
//

#include <iostream>
#include "stdafx.h"
#include "ArcRobot.h"
#include "ArcRobotDlg.h"
#include "afxdialogex.h"

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

int CArcRobotDlg::addtext(int nID, CString str)
{
	CString strOrigin;
	GetDlgItem(nID)->GetWindowText(strOrigin);
	strOrigin += str;
	strOrigin += "\r\n";
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
	addtext(IDC_EDIT1,cpos);

}
