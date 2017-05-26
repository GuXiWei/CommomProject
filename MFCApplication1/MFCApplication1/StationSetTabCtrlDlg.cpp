// StationSetTabCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "StationSetTabCtrlDlg.h"
#include "afxdialogex.h"


// CStationSetTabCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CStationSetTabCtrlDlg, CDialogEx)

CStationSetTabCtrlDlg::CStationSetTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStationSetTabCtrlDlg::IDD, pParent)
{

}

CStationSetTabCtrlDlg::~CStationSetTabCtrlDlg()
{
}

void CStationSetTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STATIONNAME, m_stationName);
	DDX_Control(pDX, IDC_COMBO_TEMPTYPE, m_tempType);
	DDX_Control(pDX, IDC_EDIT_TEMPADDR, m_tempAddr);
	DDX_Control(pDX, IDC_COMBO_TEMPCOM, m_tempCom);
	//DDX_Control(pDX, IDC_EDIT_SWEEPSPACING, m_sweepSpacing);
	DDX_Control(pDX, IDC_EDIT_CHANNEL1, m_channel1);
	DDX_Control(pDX, IDC_EDIT_CHANNEL1NAME, m_channel1Name);
	DDX_Control(pDX, IDC_EDIT1_CHANNEL1SENSORTYPE, m_channel1SensorType);
	DDX_Control(pDX, IDC_EDIT_CHANNEL1SENSORSUBTYPE, m_channel1SensorSubType);
	DDX_Control(pDX, IDC_EDIT_CHANNEL2, m_channel2);
	DDX_Control(pDX, IDC_EDIT_CHANNEL2NAME, m_channel2Name);
	DDX_Control(pDX, IDC_EDIT_CHANNEL2SENSORTYPE, m_channel2SensorType);
	DDX_Control(pDX, IDC_EDIT_CHANNEL2SENSORSUBTYPE, m_channel2SensorSubType);
	DDX_Control(pDX, IDC_EDIT_CHANNEL3, m_channel3);
	DDX_Control(pDX, IDC_EDIT_CHANNEL3NAME, m_channel3Name);
	DDX_Control(pDX, IDC_EDIT_CHANNEL3SENSORTYPE, m_channel3SensorType);
	DDX_Control(pDX, IDC_EDIT_CHANNEL3SENSORSUBTYPE, m_channel3SensorSubType);
}


BEGIN_MESSAGE_MAP(CStationSetTabCtrlDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_TEMPTYPE, &CStationSetTabCtrlDlg::OnCbnSelchangeComboTemptype)
END_MESSAGE_MAP()


// CStationSetTabCtrlDlg 消息处理程序


BOOL CStationSetTabCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_COMBO_TEMPTYPE, _T("RS232"));
	SetDlgItemText(IDC_COMBO_TEMPCOM, _T("COM1"));
	SetDlgItemText(IDC_COMBO_SPEEDCOM, _T("COM1"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CStationSetTabCtrlDlg::OnCbnSelchangeComboTemptype()
{
	// TODO:  在此添加控件通知处理程序代码
	//UpdateWindow();

	//CString strTemp;
	//GetDlgItem(IDC_COMBO_TEMPTYPE)->GetWindowText(strTemp);
	int nSel = ((CComboBox *)GetDlgItem(IDC_COMBO_TEMPTYPE))->GetCurSel();
    if (nSel== 1)
    {
		GetDlgItem(IDC_EDIT_TEMPADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TEMPCOM)->EnableWindow(TRUE);
		//UpdateWindow();
    }
	else
	{
		GetDlgItem(IDC_EDIT_TEMPADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_TEMPCOM)->EnableWindow(FALSE);
		//UpdateWindow();
	}
}
