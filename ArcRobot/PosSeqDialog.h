#pragma once
#include "afxcmn.h"


// PosSeqDialog 对话框

class PosSeqDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PosSeqDialog)

public:
	PosSeqDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PosSeqDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl PosList;
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton10();
};
