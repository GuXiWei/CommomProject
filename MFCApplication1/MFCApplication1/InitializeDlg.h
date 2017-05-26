#pragma once
#include "afxwin.h"

/************************************************************************/
/* 
  @ brief ：初始设定 gxw 2017-5-23 
*/
/************************************************************************/

// CInitializeDlg 对话框  

class CInitializeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitializeDlg)

public:
	CInitializeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInitializeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_INITIALIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//前一个工位
	afx_msg void OnBnClickedButtonPre();
	//下一个工位
	afx_msg void OnBnClickedButtonNext();
	//跳转
	afx_msg void OnBnClickedButtonJump();
	//保存设置
	afx_msg void OnBnClickedButtonSave();
	CEdit m_CurrentStation;
	CComboBox m_ProductName;
	CEdit m_Model;
	CEdit m_Manufacturer;
	virtual BOOL OnInitDialog();
};
