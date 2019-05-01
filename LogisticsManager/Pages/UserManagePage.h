#pragma once


// CUserManagePage dialog

class CUserManagePage : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManagePage)

public:
	CUserManagePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserManagePage();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddorder2();
	afx_msg void OnBnClickedButtonAddorder();
};
