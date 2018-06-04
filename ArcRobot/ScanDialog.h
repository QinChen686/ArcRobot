#pragma once
#pragma comment( lib,"winmm.lib" )
#include "afxcmn.h"
#include "CalPos.h"
#include "ABBSocketCommunication.h"
#include "SensorCommunicate.h"
#include "CalibrationDlg.h"
#include "Simulation.h"
#include <Windows.h>
#include <Mmsystem.h>

#define TARGET_RESOLUTION 1         // 1-millisecond target resolution  

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
	afx_msg void OnBnClickedButton1();
	CListCtrl SeqList;

private:
	static CListCtrl PosList2;
	static vector<vector<double>> res;
	static int numOfRes;
	static vector<vector<double>> ScanDialog::SensorData;//(1000, vector<double>(4, 0.0));
	static int numOfSensorData;
	static vector<vector<double>> RealPos;
	static ABBSocket abbsoc;
	static calWeldLine calwl;
	static UINT RecvAndDisplay(LPVOID lpParam);
	static DWORD ScanStartTime,GetWeldLineTime;
	static int SensorPosCount;
	SensorSocket sensorsocket;
public:
	afx_msg void OnBnClickedButton2();
	
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
