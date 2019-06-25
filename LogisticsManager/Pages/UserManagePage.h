#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "UserManageCreatePage.h"
#include <string>
#include <vector>
#include <map>

// CUserManagePage dialog

class CUserManagePage : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManagePage)

public:
	CUserManagePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserManagePage();

// Dialog Data
	enum {
		IDD = IDD_DIALOG_USERMANAGE
};

protected:
	// GUI
	CRect		m_RectWorkingArea;
	CFont		m_FontStatic1;
	CFont		m_FontEdit1;
	LOGFONT		m_FontList1;

	CListCtrl	m_TableDesID;
	CPtrArray   m_pDesEdits;
	CPtrArray   m_pIDEdits;

	CListCtrl	m_TableCusAccount;

	// member
	std::vector<CString> m_CurrCusInfo;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnResizeControl(int CtrlID, double cx, double cy);
	DECLARE_MESSAGE_MAP()

public:
	void SetWorkingArea(CRect & rect);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEditSearch();
	afx_msg void OnBnClickedEditNewcus();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonUpload();
};
