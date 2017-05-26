
// MFCApplication1View.h : CMFCApplication1View ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "DialogStationView.h"
#include "StationSet.h"
#include "InitializeDlg.h"

class CMFCApplication1View : public CFormView
{
protected: // �������л�����
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

public:
	enum{ IDD = IDD_MFCAPPLICATION1_FORM };

// ����
public:
	CMFCApplication1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���
	//��Ϣ gxw
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelChangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	//�ݶ�
	void ReSize(void);
	POINT m_oldPoint;
	//���������ļ�
	void loadSystemFile();
// ʵ��
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl_Station;
	//��λ1�����ͼ
	CDialogStationView m_Station1;
	//��λ2�����ͼ
	CDialogStationView m_Station2;
	//��λ3�����ͼ
	CDialogStationView m_Station3;
	//�˳�
	afx_msg void OnExit();
	//��λ��������
	afx_msg void OnStationset();
	//afx_msg void OnNameplateset();
	//��ӡ
	afx_msg void OnPrint();
	//��ѯ
	afx_msg void OnQuery();
	//����
	afx_msg void OnAbout();
	//��ʼ�趨
	afx_msg void OnInitalize();
};

#ifndef _DEBUG  // MFCApplication1View.cpp �еĵ��԰汾
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

