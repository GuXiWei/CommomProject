#pragma once
#include "afxcmn.h"
#include "PrintFrame.h"

// CPrintDlg 对话框

class CPrintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrintDlg)

public:
	CPrintDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrintDlg();
	//void	GetWindowGraph();
// 对话框数据
	enum { IDD = IDD_DIALOG_PRINT };

	CPrintFrame* m_pPrintFrame;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonPrintview();
	afx_msg void	OnPaint();
	afx_msg HCURSOR	OnQueryDragIcon();
	afx_msg LRESULT OnBeginPrinting(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrintWindow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndPrinting(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	
	UINT         m_cxWidth;
	UINT         m_cxOffset;
	UINT         m_nLinesPerPage;
	UINT         m_cyPrinter;
	CFont		m_ListFont;
	CFont		m_fontPrinter;

	void PrintPageHeader(CDC* pDC, UINT nPageNumber, CPrintInfo* pInfo);
};
