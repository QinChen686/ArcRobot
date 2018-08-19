
// ArcRobotDlg.h : 头文件
//

#pragma once

#include "ABBSocketCommunication.h"
#include "mathClass.h"
#include "SensorCommunicate.h"//one key start include
#include <map>



// CArcRobotDlg 对话框
class CArcRobotDlg : public CDialogEx
{
// 构造
public:
	CArcRobotDlg(CWnd* pParent = NULL);	// 标准构造函数
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARCROBOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	int addtext(int nID, CString str, bool addition=true);
	mathfun mathc;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();

//one key start resouces;
public:
	SensorSocket sensorsocket0;
	static ABBSocket abbsoc;
	static vector<vector<vector<double>>> res0;
	static int numOfRes0[3];
	static vector<vector<vector<double>>> SensorData0;//(1000, vector<double>(4, 0.0));
	static vector<vector<double>> SensorData1;//(1000, vector<double>(4, 0.0));
	static vector<vector<double>> SensorData2;//(1000, vector<double>(4, 0.0));
	static int numOfSensorData0[3];

	static DWORD ScanStartTime0, GetWeldLineTime0;
	static int SensorPosCount0;

private:
	bool charEqual(char* recLine, char* split);
	static const int segCount = 3;
	static const int scanCount = 3;
	std::map<int, int> match = { {0,0},{1,1},{2,2} };
};
