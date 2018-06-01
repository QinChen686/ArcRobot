#pragma once
#include "glDisplay.h"
#include "afxwin.h"

// Simulation 对话框

class Simulation : public CDialogEx
{
	DECLARE_DYNAMIC(Simulation)

public:
	Simulation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Simulation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	bool InitGL();
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	void RenderScene();
	glDisplay gldisplay;
	HGLRC hrenderRC;
	HDC hrenderDC;
	int PixelFormat;    //像素格式
	CStatic m_staticpic;
	float m_yRotate;

	bool midButtonState;
	bool ctrlKeyState;

//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
