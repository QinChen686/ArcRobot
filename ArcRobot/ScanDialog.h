#pragma once
#include "afxcmn.h"
#include "ABBSocketCommunication.h"


// ScanDialog 对话框

class ScanDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScanDialog)

public:
	ScanDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ScanDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl SeqList;
	afx_msg void OnBnClickedButton1();
	CListCtrl PosList2;
private:
	ABBSocket abbsoc;
public:
	afx_msg void OnBnClickedButton2();
};
