// DialogStationView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DialogStationView.h"
#include "afxdialogex.h"


// CDialogStationView 对话框

IMPLEMENT_DYNAMIC(CDialogStationView, CDialogEx)

CDialogStationView::CDialogStationView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogStationView::IDD, pParent)
{

}

CDialogStationView::~CDialogStationView()
{
}

void CDialogStationView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_BtnOk);
}


BEGIN_MESSAGE_MAP(CDialogStationView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDialogStationView::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDialogStationView::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PRINTCURVE, &CDialogStationView::OnBnClickedButtonPrintcurve)
END_MESSAGE_MAP()


// CDialogStationView 消息处理程序


void CDialogStationView::OnBnClickedButtonStart()
{
	// TODO:  在此添加控件通知处理程序代码
	CDetectionTaskDlg detectionTaskDlg;
	detectionTaskDlg.DoModal();
}


BOOL CDialogStationView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_PRINTCURVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REALTIMEDATA)->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialogStationView::OnBnClickedButtonStop()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogStationView::OnBnClickedButtonPrintcurve()
{
	// TODO:  在此添加控件通知处理程序代码
	CPrintDlg printDlg;
	printDlg.DoModal();
}
