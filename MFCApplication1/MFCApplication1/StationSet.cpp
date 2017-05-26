// StationSet.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "StationSet.h"
#include "afxdialogex.h"


// CStationSet 对话框

IMPLEMENT_DYNAMIC(CStationSet, CDialogEx)

CStationSet::CStationSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStationSet::IDD, pParent)
{
	for (int i = 0; i < MAXSTATION; ++i)
	{
		m_pStationSetTabCtrlDlg[i] = NULL;
	}
}

CStationSet::~CStationSet()
{
}

void CStationSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_STATIONSET, m_tab_StationSet);
}


BEGIN_MESSAGE_MAP(CStationSet, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_STATIONNUM_OK, &CStationSet::OnBnClickedButtonStationnumOk)
	ON_BN_CLICKED(IDC_BUTTON_STATIONSET_OK, &CStationSet::OnBnClickedButtonStationsetOk)
	ON_BN_CLICKED(IDC_BUTTON_STATIONSET_CANCEL, &CStationSet::OnBnClickedButtonStationsetCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_STATIONSET, &CStationSet::OnTcnSelchangeTabStationset)
	ON_EN_CHANGE(IDC_EDIT_STATIONNUM, &CStationSet::OnEnChangeEditStationnum)
END_MESSAGE_MAP()


// CStationSet 消息处理程序

// /**
//    @ 确定工位数
//    */
// void CStationSet::OnBnClickedButtonStationnumOk()
// {
// 	// TODO:  在此添加控件通知处理程序代码
// 	//清楚所有tab页
// 	m_tab_StationSet.DeleteAllItems();
// 	//清除控件
// 	for (int i = 0; i < MAXSTATION; ++i)
// 	{
// 		if (m_pStationSetTabCtrlDlg[i] != NULL)
// 		{
// 			m_pStationSetTabCtrlDlg[i]->DestroyWindow();
// 			delete m_pStationSetTabCtrlDlg[i];
// 			m_pStationSetTabCtrlDlg[i] = NULL;
// 		}
// 	}
// 	CString str;
// 	GetDlgItem(IDC_EDIT_STATIONNUM)->GetWindowText(str);
// 	if (str != "1" && str != "2" && str != "3")
// 	{
// 		MessageBox(_T("请输入正确工位数 !"), _T("警告"), MB_OK | MB_DEFBUTTON2);
// 		return;
// 	}
// 	//工位数
// 	int nStationNum = _ttoi(str);
// 	for (int i = 0; i < nStationNum; ++i)
// 	{
// 		CString strTemp = _T("工位");
// 		CString temp;
// 		temp.Format(_T("%d"), i + 1);
// 		strTemp += temp;
// 		m_tab_StationSet.InsertItem(i, strTemp);
// // 		CStationSetTabCtrlDlg *pStationSetTabCtrlDlg = new CStationSetTabCtrlDlg;
// // 		pStationSetTabCtrlDlg->Create(IDD_DIALOG_STATIONSET_TABCTRL, &m_tab_StationSet);
// 		m_pStationSetTabCtrlDlg[i] = new CStationSetTabCtrlDlg;
// 		m_pStationSetTabCtrlDlg[i]->Create(IDD_DIALOG_STATIONSET_TABCTRL, &m_tab_StationSet);
// 
// 		CRect rc;
// 		m_tab_StationSet.GetClientRect(&rc);
// 		CRect rcTabItem;
// 		m_tab_StationSet.GetItemRect(0, rcTabItem);
// 		rc.top += rcTabItem.Height() + 4;
// 		rc.left += 4;
// 		rc.bottom -= 4;
// 		rc.right -= 4;
// 		m_pStationSetTabCtrlDlg[i]->MoveWindow(&rc);
// 		m_pStationSetTabCtrlDlg[i]->ShowWindow(SW_SHOW);
// 	}
// 	m_tab_StationSet.SetCurSel(0);
// }

/**
   @ 获取工位参数
   */
void CStationSet::OnBnClickedButtonStationsetOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strTemp;
	GetDlgItem(IDC_EDIT_STATIONNUM)->GetWindowText(strTemp);
	if (strTemp == "")
	{
		MessageBox(_T("请输入正确工位数!"), _T("警告"), MB_OK | MB_DEFBUTTON2);
		return;
	}

	//检测信息是否填写完整
	if (!isInfoComplete())
	{
		return;
	}

	//清空上一次记录
	memset(&g_Param, 0, sizeof(g_Param));
	//设置参数
	CString str;
	GetDlgItem(IDC_EDIT_STATIONNUM)->GetWindowText(str);
	g_Param.nStation = _ttoi(str);
	memset(g_Param.resvered, 0, 100);
	for (int i = 0; i < g_Param.nStation; ++i)
	{
		//工位号
		g_Param.station[i].stationNo = i + 1;
		//工位名
		m_pStationSetTabCtrlDlg[i]->m_stationName.GetWindowText(str);
		memcpy(g_Param.station[i].stationName, str.GetBuffer(str.GetLength()), str.GetLength());

		//控制类型 地址 端口
		int nSel = m_pStationSetTabCtrlDlg[i]->m_tempType.GetCurSel();
		// ! GPIB
		if (nSel == 0)
		{
			g_Param.station[i].tempControlMode = 0;
			g_Param.station[i].port = 0;
			m_pStationSetTabCtrlDlg[i]->m_tempAddr.GetWindowText(str);
			g_Param.station[i].addr = _ttoi(str);
		}
		// ! RS232
		else if (nSel == 1)
		{
			g_Param.station[i].tempControlMode = 1;
			g_Param.station[i].addr = 0;
			int nSelTempCom = m_pStationSetTabCtrlDlg[i]->m_tempCom.GetCurSel();
			//m_pStationSetTabCtrlDlg[i]->m_tempCom.GetLBText(nSelTempCom, str);
			g_Param.station[i].port = nSelTempCom + 1;
		}

		//扫描间隔
		m_pStationSetTabCtrlDlg[i]->m_sweepSpacing.GetWindowText(str);
		g_Param.station[i].nScanInterval = _ttoi(str);

		//三通道参数
		// 1
		m_pStationSetTabCtrlDlg[i]->m_channel1.GetWindowText(str);
		g_Param.station[i].channel1No = _ttoi(str);
		m_pStationSetTabCtrlDlg[i]->m_channel1Name.GetWindowText(str);
		memcpy(g_Param.station[i].channel1Name, str.GetBuffer(str.GetLength()), str.GetLength());
		m_pStationSetTabCtrlDlg[i]->m_channel1SensorType.GetWindowText(str);
		g_Param.station[i].channel1TempType = _ttoi(str);
		m_pStationSetTabCtrlDlg[i]->m_channel1SensorSubType.GetWindowText(str);
		g_Param.station[i].channel1TempSubmode = _ttoi(str);
		// 2
		m_pStationSetTabCtrlDlg[i]->m_channel2.GetWindowText(str);
		g_Param.station[i].channel2No = _ttoi(str);
		m_pStationSetTabCtrlDlg[i]->m_channel2Name.GetWindowText(str);
		memcpy(g_Param.station[i].channel2Name, str.GetBuffer(str.GetLength()), str.GetLength());
		m_pStationSetTabCtrlDlg[i]->m_channel2SensorType.GetWindowText(str);
		g_Param.station[i].channel2TempType = _ttoi(str);
		m_pStationSetTabCtrlDlg[i]->m_channel2SensorSubType.GetWindowText(str);
		g_Param.station[i].channel2TempSubmode = _ttoi(str);
		// 3
		m_pStationSetTabCtrlDlg[i]->m_channel3.GetWindowText(str);
		g_Param.station[i].channel3No = _ttoi(str);
		m_pStationSetTabCtrlDlg[i]->m_channel3Name.GetWindowText(str);
		memcpy(g_Param.station[i].channel3Name, str.GetBuffer(str.GetLength()), str.GetLength());
		m_pStationSetTabCtrlDlg[i]->m_channel3SensorType.GetWindowText(str);
		g_Param.station[i].channel3TempType = _ttoi(str);
		m_pStationSetTabCtrlDlg[i]->m_channel3SensorSubType.GetWindowText(str);
		g_Param.station[i].channel3TempSubmode = _ttoi(str);

		//保留字段
		memset(g_Param.station[i].resverd, 0, 100);
	}

	//将参数写入配置文件
	USES_CONVERSION;
	CString strFilePath = g_strExePath + g_strSysFileName;
// 	int len = strFilePath.GetLength();
// 	char *pBuf = new char[len];
// 	for (int i = 0; i < len; i++)
// 	{
// 		pBuf[i] = (char)strFilePath.GetAt(i);
// 	}
	FILE *file;
	fopen_s(&file, (strFilePath), "rb");
	if (file == NULL)
	{
		//不存在配置文件 创建
		fopen_s(&file, (strFilePath), "wb");
		fwrite(&g_Param, sizeof(GlobalParam), 1, file);
	}
	else 
	{
		//配置文件存在 删除
		fclose(file);
		if (remove((strFilePath)) == 0)
		{
			fopen_s(&file, (strFilePath), "wb");
			fwrite(&g_Param, sizeof(GlobalParam), 1, file);
		}
		else
		{
			fclose(file);
			return;
		}
	}
	fclose(file);
	memset(&g_SysParam, 0, sizeof(g_SysParam));
	memcpy(&g_SysParam, &g_Param, sizeof(g_Param));

	MessageBox(_T("参数设置成功， 程序重新启动!"), _T("提示"), MB_OK | MB_DEFBUTTON2);
	SendMessage(WM_CLOSE);
	PostQuitMessage(0);
}

/**
   @ 取消工位设置退出
   */
void CStationSet::OnBnClickedButtonStationsetCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//清楚所有tab页
	m_tab_StationSet.DeleteAllItems();
	//清除控件
	for (int i = 0; i < MAXSTATION; ++i)
	{
		if (m_pStationSetTabCtrlDlg[i] != NULL)
		{
			m_pStationSetTabCtrlDlg[i]->DestroyWindow();
			delete m_pStationSetTabCtrlDlg[i];
			m_pStationSetTabCtrlDlg[i] = NULL;
		}
	}
	SendMessage(WM_CLOSE);
}


BOOL CStationSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFont font;
	font.CreatePointFont(120, _T("楷体"));
	GetDlgItem(IDC_STATIC_STATIONNUM)->SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CStationSet::OnTcnSelchangeTabStationset(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	//获取所选择的页面  
	int nCurSel = m_tab_StationSet.GetCurSel();
	if (nCurSel == 0)
	{
		//页面一显示，页面二隐藏  
		m_pStationSetTabCtrlDlg[0]->ShowWindow(SW_SHOW);
		for (int i = 1; i < g_Param.nStation; ++i)
		{
			m_pStationSetTabCtrlDlg[i]->ShowWindow(SW_HIDE);
		}
	}
	else if (nCurSel == 1)
	{
		////页面二显示，页面一隐藏  
		m_pStationSetTabCtrlDlg[0]->ShowWindow(SW_HIDE);
		m_pStationSetTabCtrlDlg[1]->ShowWindow(SW_SHOW);
		if (g_Param.nStation > 2)
		{
			m_pStationSetTabCtrlDlg[2]->ShowWindow(SW_HIDE);
		}
	}
	else if (nCurSel == 2)
	{
		m_pStationSetTabCtrlDlg[0]->ShowWindow(SW_HIDE);
		m_pStationSetTabCtrlDlg[1]->ShowWindow(SW_HIDE);
		m_pStationSetTabCtrlDlg[2]->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}

bool CStationSet::isInfoComplete()
{
	for (int i = 0; i < MAXSTATION; i++)
	{
		if (m_pStationSetTabCtrlDlg[i] != NULL)
		{
			CString strTemp1;
			//！检测工位名称目前在1-3之间
			m_pStationSetTabCtrlDlg[i]->m_stationName.GetWindowText(strTemp1);
			if (strTemp1 == "")
			{
				MessageBox(_T("工位名非法 !"), _T("警告"), MB_OK | MB_DEFBUTTON2);
				return FALSE;
			}
			 
			//！检查控制类型 地址 端口
			int nSel = m_pStationSetTabCtrlDlg[i]->m_tempType.GetCurSel();
			if (nSel == 0)
			{
				m_pStationSetTabCtrlDlg[i]->m_tempAddr.GetWindowText(strTemp1);
				if (strTemp1 == "")
				{
					MessageBox(_T("GPIB地址不合法 !"), _T("警告"), MB_OK | MB_DEFBUTTON2);
					return FALSE;
				}
			}

			// ! 检查扫描间隔
			m_pStationSetTabCtrlDlg[i]->m_sweepSpacing.GetWindowText(strTemp1);
			if (strTemp1 == "")
			{
				MessageBox(_T("请输入正确时间间隔!"), _T("警告"), MB_OK | MB_DEFBUTTON2);
				return FALSE;
			}

			//三通道参数检查
			// 待定
		}
	}
	return true;
}


void CStationSet::OnEnChangeEditStationnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//清楚所有tab页
	m_tab_StationSet.DeleteAllItems();
	//清除控件
	for (int i = 0; i < MAXSTATION; ++i)
	{
		if (m_pStationSetTabCtrlDlg[i] != NULL)
		{
			m_pStationSetTabCtrlDlg[i]->DestroyWindow();
			delete m_pStationSetTabCtrlDlg[i];
			m_pStationSetTabCtrlDlg[i] = NULL;
		}
	}
	CString str;
	GetDlgItem(IDC_EDIT_STATIONNUM)->GetWindowText(str);
	if (str != "1" && str != "2" && str != "3")
	{
		MessageBox(_T("请输入正确工位数 !"), _T("警告"), MB_OK | MB_DEFBUTTON2);
		GetDlgItem(IDC_EDIT_STATIONNUM)->SetWindowText(_T("3"));
		return;
	}
	//工位数
	int nStationNum = _ttoi(str);
	for (int i = 0; i < nStationNum; ++i)
	{
		CString strTemp = _T("工位");
		CString temp;
		temp.Format(_T("%d"), i + 1);
		strTemp += temp;
		m_tab_StationSet.InsertItem(i, strTemp);
		// 		CStationSetTabCtrlDlg *pStationSetTabCtrlDlg = new CStationSetTabCtrlDlg;
		// 		pStationSetTabCtrlDlg->Create(IDD_DIALOG_STATIONSET_TABCTRL, &m_tab_StationSet);
		m_pStationSetTabCtrlDlg[i] = new CStationSetTabCtrlDlg;
		m_pStationSetTabCtrlDlg[i]->Create(IDD_DIALOG_STATIONSET_TABCTRL, &m_tab_StationSet);
		m_pStationSetTabCtrlDlg[i]->m_tempAddr.EnableWindow(FALSE);
		CRect rc;
		m_tab_StationSet.GetClientRect(&rc);
		CRect rcTabItem;
		m_tab_StationSet.GetItemRect(0, rcTabItem);
		rc.top += rcTabItem.Height() + 4;
		rc.left += 4;
		rc.bottom -= 4;
		rc.right -= 4;
		m_pStationSetTabCtrlDlg[i]->MoveWindow(&rc);
		m_pStationSetTabCtrlDlg[i]->ShowWindow(SW_SHOW);
	}
	m_tab_StationSet.SetCurSel(0);
}
