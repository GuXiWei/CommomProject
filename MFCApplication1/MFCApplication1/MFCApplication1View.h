
// MFCApplication1View.h : CMFCApplication1View 类的接口
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "DialogStationView.h"
#include "StationSet.h"
#include "InitializeDlg.h"

class CMFCApplication1View : public CFormView
{
protected: // 仅从序列化创建
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

public:
	enum{ IDD = IDD_MFCAPPLICATION1_FORM };

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	//消息 gxw
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelChangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	//暂定
	void ReSize(void);
	POINT m_oldPoint;
	//加载配置文件
	void loadSystemFile();
// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl_Station;
	//工位1检测视图
	CDialogStationView m_Station1;
	//工位2检测视图
	CDialogStationView m_Station2;
	//工位3检测视图
	CDialogStationView m_Station3;
	//退出
	afx_msg void OnExit();
	//工位参数设置
	afx_msg void OnStationset();
	//afx_msg void OnNameplateset();
	//打印
	afx_msg void OnPrint();
	//查询
	afx_msg void OnQuery();
	//关于
	afx_msg void OnAbout();
	//初始设定
	afx_msg void OnInitalize();
};

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

