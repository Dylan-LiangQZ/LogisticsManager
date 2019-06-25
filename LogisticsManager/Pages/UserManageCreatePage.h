#pragma once

// CUserManageCreatePage dialog

class CUserManageCreatePage : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManageCreatePage)

public:
	CUserManageCreatePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserManageCreatePage();

// Dialog Data
	enum {
		IDD = IDD_DIALOG_USERMANAGE_CREATE
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton_Create();
	afx_msg void OnBnClickedButtonCanclecreate();
};
