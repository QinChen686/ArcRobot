#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "calibration.h"
#include "ABBSocketCommunication.h"
#include "mathClass.h"

// CalibrationDlg 对话框


class CalibrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalibrationDlg)

public:
	CalibrationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CalibrationDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();

	CListCtrl clbrtl;
	Calibration calibration;
	ABBSocket abbsoc;
	mathfun mathc;
	static Matrix4d T;//标定结果
	static bool CalibratedFlag;//是否标定的标志
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};


