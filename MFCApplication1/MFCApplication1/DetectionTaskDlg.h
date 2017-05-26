#pragma once


// CDetectionTaskDlg 对话框

class CDetectionTaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDetectionTaskDlg)

public:
	CDetectionTaskDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDetectionTaskDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DETECTIONTASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//保存任务选项
	afx_msg void OnBnClickedButtonSave();
	//取消
	afx_msg void OnBnClickedButtonCancel();
};
