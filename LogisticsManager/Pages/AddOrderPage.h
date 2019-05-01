#pragma once

#include "..\GUIElement\TableControl.h"

// CAddOrderPage dialog

class CAddOrderPage : public CDialogEx
{
	DECLARE_DYNAMIC(CAddOrderPage)

public:
	CAddOrderPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddOrderPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_USERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CListCtrl	m_TableAddCtrl;
	CListCtrl	m_TableShowCtrl;
	CPtrArray	p_mAddOrderEdits;

	virtual BOOL OnInitDialog();

protected:
	static void RegisterConfig();

	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonAddItem();
	afx_msg void OnBnClickedButtonAddorder();

	void SaveData();

};
