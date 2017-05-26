
// MFCApplication1View.cpp : CMFCApplication1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, OnSelChangeTab)
	ON_COMMAND(ID_EXIT, &CMFCApplication1View::OnExit)
	ON_COMMAND(ID_STATIONSET, &CMFCApplication1View::OnStationset)
	ON_COMMAND(ID_PRINT, &CMFCApplication1View::OnPrint)
	ON_COMMAND(ID_QUERY, &CMFCApplication1View::OnQuery)
	ON_COMMAND(ID_ABOUT, &CMFCApplication1View::OnAbout)
	ON_COMMAND(ID_INITALIZE, &CMFCApplication1View::OnInitalize)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View()
	: CFormView(CMFCApplication1View::IDD)
{
	// TODO:  在此处添加构造代码

}

CMFCApplication1View::~CMFCApplication1View()
{
}

void CMFCApplication1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//获取系统路径
	//得到当前目录
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	g_strExePath = exeFullPath;
	int nPos = g_strExePath.ReverseFind('\\');
	g_strExePath = g_strExePath.Mid(0, nPos + 1);

	//工位参数设置清零
	memset(&g_Param, 0, sizeof(g_Param));
	memset(&g_SysParam, 0, sizeof(g_SysParam));

	//添加工位布局
	CRect rec;
	GetClientRect(&rec);
	//创建
	m_TabCtrl_Station.Create(TCS_TABS | WS_CHILD | WS_VISIBLE, rec, this, IDC_TABCTRL);
	
	//添加按钮名称
	m_TabCtrl_Station.InsertItem(0, _T("工位1"));
	m_TabCtrl_Station.InsertItem(1, _T("工位2"));
	m_TabCtrl_Station.InsertItem(2, _T("工位3"));
	m_TabCtrl_Station.MoveWindow(0, 0, rec.Width(), rec.Height());
	m_Station1.Create(IDD_DIALOG_STATIONVIEW, &m_TabCtrl_Station);
	m_Station2.Create(IDD_DIALOG_STATIONVIEW, &m_TabCtrl_Station);
	m_Station3.Create(IDD_DIALOG_STATIONVIEW, &m_TabCtrl_Station);
	//调整子对话框位置
	CRect rc;
	m_TabCtrl_Station.GetClientRect(&rc);
	CRect rcTabItem;
	m_TabCtrl_Station.GetItemRect(0, rcTabItem);
	rc.top += rcTabItem.Height() + 4;
	rc.left += 4;
	rc.bottom -= 4;
	rc.right -= 4;
	m_Station1.MoveWindow(&rc);
	m_Station2.MoveWindow(&rc);
	m_Station3.MoveWindow(&rc);
	m_Station1.ShowWindow(SW_SHOW);
	m_TabCtrl_Station.SetCurSel(0);

	//1号工位
	m_Station1.m_nType = 1;
	//2号工位
	m_Station2.m_nType = 2;
	//3号工位
	m_Station3.m_nType = 3;
	//加载系统配置
	loadSystemFile();
	//显示温度 转速

}


void CMFCApplication1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CRect rc;
	GetClientRect(&rc);
	m_TabCtrl_Station.MoveWindow(0, 0, rc.Width(), rc.Height());
}

void CMFCApplication1View::OnSelChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获取所选择的页面  
	int nCurSel = m_TabCtrl_Station.GetCurSel();
	if (nCurSel == 0)
	{  
		m_Station1.ShowWindow(SW_SHOW);
		m_Station2.ShowWindow(SW_HIDE);
		m_Station3.ShowWindow(SW_HIDE);
	}
	else if (nCurSel == 1)
	{  
		m_Station1.ShowWindow(SW_HIDE);
		m_Station2.ShowWindow(SW_SHOW);
		m_Station3.ShowWindow(SW_HIDE);
	}
	else if (nCurSel == 2)
	{
		m_Station1.ShowWindow(SW_HIDE);
		m_Station2.ShowWindow(SW_HIDE);
		m_Station3.ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}

void CMFCApplication1View::ReSize(void)
{

}

void CMFCApplication1View::loadSystemFile()
{
	// ! 判断配置文件是否存在
	USES_CONVERSION;
	FILE *file;
	CString strFilePath = g_strExePath + g_strSysFileName;
// 	int len = strFilePath.GetLength();
// 	char *pBuf = new char[len];
// 	for (int  i = 0; i < len; i++)
// 	{
// 		pBuf[i] = (char)strFilePath.GetAt(i);
// 	}
    fopen_s(&file, (strFilePath), "rb");
	// ! 首次设置配置项
	if (file == NULL)
	{
		// ! 设置工位参数
		OnStationset();
	}
	else
	{
		// ! 读取工位参数
		fread(&g_SysParam, sizeof(GlobalParam), 1, file);
		fclose(file);
	}
}

// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序

/**
   @ 退出程序 
   */
void CMFCApplication1View::OnExit()
{
	// TODO:  在此添加命令处理程序代码
	if (MessageBox(_T("确定要退出吗？"), _T("提示"), MB_YESNO | MB_DEFBUTTON2) == IDYES)
	{
		PostQuitMessage(0);
	}
}

/**
@ 工位设置
*/
void CMFCApplication1View::OnStationset()
{
	// TODO:  在此添加命令处理程序代码
	CStationSet StationSetDlg;
	StationSetDlg.DoModal();
	//第一次没有进行设置直接退出
	if (g_SysParam.nStation == 0)
	{
		PostQuitMessage(0);
	}
}

/**
   @ 打印
   */
void CMFCApplication1View::OnPrint()
{
	// TODO:  在此添加命令处理程序代码
}

/**
   @ 查询
   */
void CMFCApplication1View::OnQuery()
{
	// TODO:  在此添加命令处理程序代码
}


void CMFCApplication1View::OnAbout()
{
	// TODO:  在此添加命令处理程序代码
}


void CMFCApplication1View::OnInitalize()
{
	// TODO:  在此添加命令处理程序代码
	CInitializeDlg initalizeDlg;
	initalizeDlg.DoModal();
}
