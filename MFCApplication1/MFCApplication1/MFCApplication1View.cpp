
// MFCApplication1View.cpp : CMFCApplication1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMFCApplication1View ����/����

CMFCApplication1View::CMFCApplication1View()
	: CFormView(CMFCApplication1View::IDD)
{
	// TODO:  �ڴ˴���ӹ������

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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//��ȡϵͳ·��
	//�õ���ǰĿ¼
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	g_strExePath = exeFullPath;
	int nPos = g_strExePath.ReverseFind('\\');
	g_strExePath = g_strExePath.Mid(0, nPos + 1);

	//��λ������������
	memset(&g_Param, 0, sizeof(g_Param));
	memset(&g_SysParam, 0, sizeof(g_SysParam));

	//��ӹ�λ����
	CRect rec;
	GetClientRect(&rec);
	//����
	m_TabCtrl_Station.Create(TCS_TABS | WS_CHILD | WS_VISIBLE, rec, this, IDC_TABCTRL);
	
	//��Ӱ�ť����
	m_TabCtrl_Station.InsertItem(0, _T("��λ1"));
	m_TabCtrl_Station.InsertItem(1, _T("��λ2"));
	m_TabCtrl_Station.InsertItem(2, _T("��λ3"));
	m_TabCtrl_Station.MoveWindow(0, 0, rec.Width(), rec.Height());
	m_Station1.Create(IDD_DIALOG_STATIONVIEW, &m_TabCtrl_Station);
	m_Station2.Create(IDD_DIALOG_STATIONVIEW, &m_TabCtrl_Station);
	m_Station3.Create(IDD_DIALOG_STATIONVIEW, &m_TabCtrl_Station);
	//�����ӶԻ���λ��
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

	//1�Ź�λ
	m_Station1.m_nType = 1;
	//2�Ź�λ
	m_Station2.m_nType = 2;
	//3�Ź�λ
	m_Station3.m_nType = 3;
	//����ϵͳ����
	loadSystemFile();
	//��ʾ�¶� ת��

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
	//��ȡ��ѡ���ҳ��  
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
	// ! �ж������ļ��Ƿ����
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
	// ! �״�����������
	if (file == NULL)
	{
		// ! ���ù�λ����
		OnStationset();
	}
	else
	{
		// ! ��ȡ��λ����
		fread(&g_SysParam, sizeof(GlobalParam), 1, file);
		fclose(file);
	}
}

// CMFCApplication1View ���

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View ��Ϣ�������

/**
   @ �˳����� 
   */
void CMFCApplication1View::OnExit()
{
	// TODO:  �ڴ���������������
	if (MessageBox(_T("ȷ��Ҫ�˳���"), _T("��ʾ"), MB_YESNO | MB_DEFBUTTON2) == IDYES)
	{
		PostQuitMessage(0);
	}
}

/**
@ ��λ����
*/
void CMFCApplication1View::OnStationset()
{
	// TODO:  �ڴ���������������
	CStationSet StationSetDlg;
	StationSetDlg.DoModal();
	//��һ��û�н�������ֱ���˳�
	if (g_SysParam.nStation == 0)
	{
		PostQuitMessage(0);
	}
}

/**
   @ ��ӡ
   */
void CMFCApplication1View::OnPrint()
{
	// TODO:  �ڴ���������������
}

/**
   @ ��ѯ
   */
void CMFCApplication1View::OnQuery()
{
	// TODO:  �ڴ���������������
}


void CMFCApplication1View::OnAbout()
{
	// TODO:  �ڴ���������������
}


void CMFCApplication1View::OnInitalize()
{
	// TODO:  �ڴ���������������
	CInitializeDlg initalizeDlg;
	initalizeDlg.DoModal();
}
