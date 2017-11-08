// PosSeqDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ArcRobot.h"
#include "PosSeqDialog.h"
#include "afxdialogex.h"


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
	PosList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 4, 0);
	PosList.InsertColumn(1, _T("空间坐标"), LVCFMT_CENTER, rect.Width() / 4, 1);
	PosList.InsertColumn(2, _T("四元数"), LVCFMT_CENTER, rect.Width() / 4, 2);
	PosList.InsertColumn(3, _T("关节状态"), LVCFMT_CENTER, rect.Width() / 4, 3);

	// 在列表视图控件中插入列表项，并设置列表子项文本   
	PosList.InsertItem(0, _T("Java"));
	PosList.SetItemText(0, 1, _T("1"));
	PosList.SetItemText(0, 2, _T("1"));
	PosList.SetItemText(0, 3, _T("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
