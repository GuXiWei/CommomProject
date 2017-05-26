// InitializeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "InitializeDlg.h"
#include "afxdialogex.h"


// CInitializeDlg 对话框

IMPLEMENT_DYNAMIC(CInitializeDlg, CDialogEx)

CInitializeDlg::CInitializeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitializeDlg::IDD, pParent)
{

}

CInitializeDlg::~CInitializeDlg()
{
}

void CInitializeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CURRENTSTATION, m_CurrentStation);
	DDX_Control(pDX, IDC_COMBO_PRODUCTNAME, m_ProductName);
	DDX_Control(pDX, IDC_EDIT_MODEL, m_Model);
	DDX_Control(pDX, IDC_EDIT_MANUFACTURER, m_Manufacturer);
}


BEGIN_MESSAGE_MAP(CInitializeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &CInitializeDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CInitializeDlg::OnBnClickedButtonNext)
	//ON_BN_CLICKED(IDC_BUTTON_JUMP, &CInitializeDlg::OnBnClickedButtonJump)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CInitializeDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CInitializeDlg 消息处理程序


void CInitializeDlg::OnBnClickedButtonPre()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strStation;
	m_CurrentStation.GetWindowText(strStation);
	int nStation = _ttoi(strStation);
	nStation--;
	if (!nStation)
	{
		m_CurrentStation.SetWindowText(_T("3"));
	}
	else
	{
		strStation.Format(TEXT("%d"), nStation);
		m_CurrentStation.SetWindowText(strStation);
	}
}


void CInitializeDlg::OnBnClickedButtonNext()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strStation;
	m_CurrentStation.GetWindowText(strStation);
	int nStation = _ttoi(strStation);
	nStation++;
	if (nStation == 4)
	{
		m_CurrentStation.SetWindowText(_T("1"));
	}
	else
	{
		strStation.Format(TEXT("%d"), nStation);
		m_CurrentStation.SetWindowText(strStation);
	}
}


void CInitializeDlg::OnBnClickedButtonJump()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CInitializeDlg::OnBnClickedButtonSave()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CInitializeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CurrentStation.SetWindowText(_T("1"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
