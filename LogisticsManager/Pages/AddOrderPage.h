#pragma once

#include "..\GUIElement\TableControl.h"
#include "afxdtctl.h"
#include "afxcmn.h"

// CAddOrderPage dialog

class CAddOrderPage : public CDialogEx
{
	DECLARE_DYNAMIC(CAddOrderPage)

public:
	CAddOrderPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddOrderPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CFont		m_FontStatic1;
	CFont		m_FontEdit1; 
	LOGFONT		m_FontList1;
	LOGFONT		m_FontList2;
	LOGFONT		m_FontList4;
	CListCtrl	m_TableCustInfo;
	CListCtrl	m_TableAddCtrl;
	CListCtrl	m_TableFareCtrl;
	CListCtrl	m_TableShowOrder;
	CPtrArray	m_pAddOrderEdits;
	CComboBox   m_PackingSizeCombo;
	CComboBox   m_PackingWayCombo;
	CComboBox   m_PayWayCombo;
	CDateTimeCtrl m_DateTimeRecive;
	CDateTimeCtrl m_DateTimeDelivey;

	CRect		m_RectWorkingArea;

	virtual BOOL OnInitDialog();

protected:
	double CalculatePackingFare();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonQuerycust();
	afx_msg void OnBnClickedButtonAddItem();
	afx_msg void OnBnClickedButtonCalfare();

	void OnResizeControl(int CtrlID, double cx, double cy);

public:
	void SetWorkingArea(CRect & rect);
	
};