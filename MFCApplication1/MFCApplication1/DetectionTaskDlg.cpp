// DetectionTaskDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DetectionTaskDlg.h"
#include "afxdialogex.h"


// CDetectionTaskDlg �Ի���

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


// CDetectionTaskDlg ��Ϣ�������


void CDetectionTaskDlg::OnBnClickedButtonSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDetectionTaskDlg::OnBnClickedButtonCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE);
}
