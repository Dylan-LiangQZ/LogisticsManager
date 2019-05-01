#pragma once

#include <vector>
#include <set>

// CQueryOrderPage dialog

class CQueryOrderPage : public CDialogEx
{
	DECLARE_DYNAMIC(CQueryOrderPage)

public:
	CQueryOrderPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQueryOrderPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_QUERYORDER };

	CListCtrl	m_TableShowCtrl;
	CComboBox	m_AllOrderCombo;
	std::vector<CString>	m_szFileNameV;
	std::set<CString>	m_szFileNameSet;

protected:
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void GetFiles(const std::string & path, std::vector<std::string> & files);

public:
	void AddOrderList();

	afx_msg void OnBnClickedQueryorder();
};
