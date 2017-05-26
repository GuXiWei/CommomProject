// PrintView.cpp : 实现文件
//

#include "stdafx.h"
//#include "PrintDemo.h"
#include "PrintView.h"
#include "PrintFrame.h"
#include "PreviewPrint.h"

// CPrintView

IMPLEMENT_DYNCREATE(CPrintView, CScrollView)

CPrintView::CPrintView()
{
	m_nMapMode	= MM_TEXT;
}

CPrintView::~CPrintView()
{
}

BOOL CALLBACK CPrintView::ProcClosePrintPreview(CFrameWnd* pFrameWnd)
{
	ASSERT_VALID(pFrameWnd);

	CPreviewPrint* pPreview	= (CPreviewPrint*)pFrameWnd->GetDlgItem(AFX_IDW_PANE_FIRST);

	ASSERT_KINDOF(CPreviewView, pPreview);
	pPreview->m_bIsCloseFrame	= TRUE;
	pPreview->OnPreviewClose();

	return FALSE;

}

BEGIN_MESSAGE_MAP(CPrintView, CScrollView)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
END_MESSAGE_MAP()


// CPrintView 绘图

void CPrintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}


// CPrintView 诊断

#ifdef _DEBUG
void CPrintView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CPrintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


BOOL CPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPrintView::OnFilePrintPreview()
{
	CPrintPreviewState*	pState	= new CPrintPreviewState;

	pState->lpfnCloseProc	= ProcClosePrintPreview;
	if(!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this, RUNTIME_CLASS(CPreviewPrint), pState))
	{
		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete	pState;
	}
}

void CPrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnBeginPrinting(pDC, pInfo);

	CPrintFrame*	pPrintFrame = (CPrintFrame*)GetParent();
	::SendMessage(pPrintFrame->m_pMainDlg->GetSafeHwnd(), WM_MAINFRAME_BEGIN_PRINTING, (WPARAM)pDC, (LPARAM)pInfo);
}

void CPrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CPrintFrame*	pPrintFrame	= (CPrintFrame*)GetParent();

	::SendMessage(pPrintFrame->m_pMainDlg->GetSafeHwnd(), WM_MAINFRAME_PRINT, (WPARAM)pDC, (LPARAM)pInfo);
}

void CPrintView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnEndPrinting(pDC, pInfo);

	CPrintFrame*	pPrintFrame = (CPrintFrame*)GetParent();
	::SendMessage(pPrintFrame->m_pMainDlg->GetSafeHwnd(), WM_MAINFRAME_END_PRINTING, (WPARAM)pDC, (LPARAM)pInfo);
}