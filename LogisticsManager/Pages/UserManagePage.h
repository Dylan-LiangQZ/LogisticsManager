#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "UserManageCreatePage.h"
#include "UserManageEditPage.h"


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
	CRect		m_RectWorkingArea;

	CFont		m_FontStatic1;

	

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnResizeControl(int CtrlID, double cx, double cy);
	DECLARE_MESSAGE_MAP()
public:
	void SetWorkingArea(CRect & rect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	
	int m_CurSelTab;
	CTabCtrl m_tab;
	CUserManageCreatePage m_tab_create;
	CUserManageEditPage	  m_tab_edit;
	CDialog* pDialog[2];				//用来保存对话框对象指针
};
