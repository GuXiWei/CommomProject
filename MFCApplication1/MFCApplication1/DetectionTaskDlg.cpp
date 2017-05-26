// DetectionTaskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DetectionTaskDlg.h"
#include "afxdialogex.h"


// CDetectionTaskDlg 对话框

IMPLEMENT_DYNAMIC(CDetectionTaskDlg, CDialogEx)

CDetectionTaskDlg::CDetectionTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDetectionTaskDlg::IDD, pParent)
{

}

CDetectionTaskDlg::~CDetectionTaskDlg()
{
}

void CDetectionTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDetectionTaskDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDetectionTaskDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDetectionTaskDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CDetectionTaskDlg 消息处理程序


void CDetectionTaskDlg::OnBnClickedButtonSave()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDetectionTaskDlg::OnBnClickedButtonCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}
