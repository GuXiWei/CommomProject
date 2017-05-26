#pragma once
#include "StationSetTabCtrlDlg.h"
#include "afxcmn.h"
#include "GlobalData.h"
/**
   @ brief : 工位设置Dialog
   */

// CStationSet 对话框

class CStationSet : public CDialogEx
{
	DECLARE_DYNAMIC(CStationSet)

public:
	CStationSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStationSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATIONSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStationnumOk();
	afx_msg void OnBnClickedButtonStationsetOk();
	afx_msg void OnBnClickedButtonStationsetCancel();
	virtual BOOL OnInitDialog();
	CTabCtrl m_tab_StationSet;
	CStationSetTabCtrlDlg *m_pStationSetTabCtrlDlg[MAXSTATION];
	afx_msg void OnTcnSelchangeTabStationset(NMHDR *pNMHDR, LRESULT *pResult);

private:
	/**
	   @ brief : 工位信息是否填写完整
	   @ return : true : 完整；false：不完整
	   */
	bool isInfoComplete();
public:
	afx_msg void OnEnChangeEditStationnum();
};
