#pragma once
#include "afxwin.h"
#include <iostream>
#include "DetectionTaskDlg.h"
#include "PrintDlg.h"
using namespace std;

// CDialogStationView 对话框

class CDialogStationView : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogStationView)

public:
	CDialogStationView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogStationView();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATIONVIEW };

	//标志位 1/2/3工位
	int m_nType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_BtnOk;
	//开始检测
	afx_msg void OnBnClickedButtonStart();
	//进行布局
	virtual BOOL OnInitDialog();
	//暂停检测
	afx_msg void OnBnClickedButtonStop();
	//打印实时曲线
	afx_msg void OnBnClickedButtonPrintcurve();
};
