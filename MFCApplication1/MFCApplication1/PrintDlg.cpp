// PrintDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "PrintDlg.h"
#include "afxdialogex.h"


// CPrintDlg 对话框

IMPLEMENT_DYNAMIC(CPrintDlg, CDialogEx)

CPrintDlg::CPrintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrintDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pPrintFrame = NULL;
}

CPrintDlg::~CPrintDlg()
{
}

void CPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW, m_List);
}


BEGIN_MESSAGE_MAP(CPrintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PRINTVIEW, &CPrintDlg::OnBnClickedButtonPrintview)
	ON_MESSAGE(WM_MAINFRAME_PRINT, OnPrintWindow)
	ON_MESSAGE(WM_MAINFRAME_BEGIN_PRINTING, OnBeginPrinting)
	ON_MESSAGE(WM_MAINFRAME_END_PRINTING, OnEndPrinting)
END_MESSAGE_MAP()


// CPrintDlg 消息处理程序


void CPrintDlg::OnBnClickedButtonPrintview()
{
	// TODO:  在此添加控件通知处理程序代码
	m_pPrintFrame = new CPrintFrame(this);

	//GetWindowGraph();
	m_pPrintFrame->DoPrintView();
}


BOOL CPrintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_ListFont.CreatePointFont(100, "Times New Roman");

	DWORD dwExStyle = m_List.GetExStyle();
	dwExStyle &= ~LVS_EX_CHECKBOXES;

	m_List.SetFont(&m_ListFont);
	m_List.SetExtendedStyle(dwExStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	m_List.InsertColumn(0, "时间", LVCFMT_LEFT, 70, -1);
	m_List.InsertColumn(1, "通道1温度", LVCFMT_LEFT, 70, -1);
	m_List.InsertColumn(2, "通道2温度", LVCFMT_LEFT, 70, -1);
	m_List.InsertColumn(3, "通道3温度", LVCFMT_LEFT, 70, -1);

	m_List.InsertColumn(4, "转速", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(5, "数值5", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(6, "数值6", LVCFMT_LEFT, 80, -1);

	int i;
	for (i = 0; i < 151; i++)
	{
		CString str[7];

		str[0].Format("%.3f", (double)(i + 1));
		str[1].Format("%.3f", 1 + sin((double)i));
		str[2].Format("%.3f", 1 + cos((double)i));
		str[3].Format("%.3f", 1 + sin((double)0.5*i));

		str[4].Format("%.3f", 1 + cos((double)0.5*i));
		str[5].Format("%.3f", 1 + sin((double)0.1*i));
		str[6].Format("%.3f", 1 + cos((double)0.1*i));
		m_List.InsertItem(i, str[0], -1);
		for (int j = 1; j <= 6; j++)
			m_List.SetItemText(i, j, str[j]);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPrintDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CPrintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPrintDlg::PrintPageHeader(CDC* pDC, UINT nPageNumber, CPrintInfo* pInfo)
{
	CFont *pOldFont;
	CFont fontHeader;
	fontHeader.CreatePointFont(100, "FixedSys", pDC);
	pOldFont = (CFont *)(pDC->SelectObject(&fontHeader));
	int nPosY, nPosX;
	nPosY = 3 * m_cyPrinter;
	nPosX = m_cxOffset;
	pDC->TextOut(nPosX, nPosY, CString("南京航空航天大学"));
	CString str;
	str.Format("第 %d 页 / 共 %d 页", nPageNumber, pInfo->GetMaxPage());
	CSize size = pDC->GetTextExtent(str);
	nPosX = m_cxOffset + m_cxWidth - size.cx;
	pDC->TextOut(nPosX, nPosY, str);
	pDC->MoveTo(m_cxOffset, 4 * m_cyPrinter);
	pDC->LineTo(m_cxOffset + m_cxWidth, 4 * m_cyPrinter);
	pDC->SelectObject(pOldFont);
	fontHeader.DeleteObject();
}

LRESULT CPrintDlg::OnBeginPrinting(WPARAM wParam, LPARAM lParam)
{
	CDC* pDC = (CDC*)wParam;
	CPrintInfo* pInfo = (CPrintInfo *)lParam;

	if (m_fontPrinter.m_hObject == NULL)
		m_fontPrinter.CreatePointFont(120, "FixedSys", pDC);

	TEXTMETRIC tm;
	CFont* pOldFont = pDC->SelectObject(&m_fontPrinter);
	pDC->GetTextMetrics(&tm);
	m_cyPrinter = tm.tmHeight + tm.tmExternalLeading;//每行高度

	CSize size = pDC->GetTextExtent(_T("---------1---------2---------" \
		"3---------4---------5---------6---------7---------8---"), 81);
	pDC->SelectObject(pOldFont);
	m_cxWidth = size.cx;     //打印宽带

	m_nLinesPerPage = (pDC->GetDeviceCaps(VERTRES) -
		(m_cyPrinter * (3 + (2 * PRINTMARGIN)))) / m_cyPrinter;//每页行数

	int nMax = (151 + m_nLinesPerPage - 1) / m_nLinesPerPage;
	pInfo->SetMaxPage(nMax);

	m_cxOffset = (pDC->GetDeviceCaps(HORZRES) - size.cx) / 2;
	return TRUE;
}

LRESULT CPrintDlg::OnEndPrinting(WPARAM wParam, LPARAM lParam)
{
	if (m_fontPrinter.m_hObject != NULL)
		m_fontPrinter.DeleteObject();
	return TRUE;
}



LRESULT CPrintDlg::OnPrintWindow(WPARAM wParam, LPARAM lParam)
{
	UINT gl_uNumOfPoints = 151;

	CDC* pDC = (CDC*)wParam;
	CPrintInfo* pInfo = (CPrintInfo *)lParam;
	int nPageNumber = pInfo->m_nCurPage;
	int i, j;
	CFont *pOldFont;
	CFont DataFont;
	DataFont.CreatePointFont(120, "宋体", pDC);

	TCHAR *pszTitle[7] = { "Time", "数值1", "数值2", "数值3", "数值4", "数值5", "数值6" };
	pOldFont = pDC->SelectObject(&DataFont);
	pDC->Rectangle(m_cxOffset, (int)((2.5 + PRINTMARGIN)*m_cyPrinter), m_cxOffset + m_cxWidth, (m_nLinesPerPage + 3 + PRINTMARGIN)*m_cyPrinter + 20);
	for (i = 1; i < 7; i++)
	{
		pDC->MoveTo(m_cxOffset + i*m_cxWidth / 7, (int)((2.5 + PRINTMARGIN)*m_cyPrinter));
		pDC->LineTo(m_cxOffset + i*m_cxWidth / 7, (3 + m_nLinesPerPage + PRINTMARGIN)*m_cyPrinter + 20);
	}
	pDC->MoveTo(m_cxOffset, (4 + PRINTMARGIN)*m_cyPrinter);
	pDC->LineTo(m_cxOffset + m_cxWidth, (4 + PRINTMARGIN)*m_cyPrinter);
	for (i = 0; i < 7; i++)
	{
		pDC->TextOut(m_cxOffset + 50 + i*m_cxWidth / 7, (int)((2.8 + PRINTMARGIN)*m_cyPrinter), CString(pszTitle[i]));
	}
	for (i = 0; i < (int)m_nLinesPerPage - 1; i++)
	{
		CString str[7];
		int nIndex = (nPageNumber - 1)*(m_nLinesPerPage - 1) + i;
		if (nIndex < (int)gl_uNumOfPoints)
		{

			str[0].Format("%.3f", (double)(nIndex + 1));
			str[1].Format("%.3f", 1 + sin((double)i));
			str[2].Format("%.3f", 1 + cos((double)i));
			str[3].Format("%.3f", 1 + sin((double)0.5*i));

			str[4].Format("%.3f", 1 + cos((double)0.5*i));
			str[5].Format("%.3f", 1 + sin((double)0.1*i));
			str[6].Format("%.3f", 1 + cos((double)0.1*i));


			for (j = 0; j < 7; j++)
			{
				pDC->TextOut(m_cxOffset + 50 + j*m_cxWidth / 7, (4 + PRINTMARGIN + i)*m_cyPrinter + 5, str[j]);
			}
		}
	}
	pDC->SelectObject(pOldFont);
	PrintPageHeader(pDC, pInfo->m_nCurPage, pInfo);
	return TRUE;
}