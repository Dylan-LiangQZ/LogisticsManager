  #pragma once

#include <vector>
#include <set>
#include "afxdtctl.h"

// CQueryOrderPage dialog

class CQueryOrderPage : public CDialogEx
{
	DECLARE_DYNAMIC(CQueryOrderPage)

public:
	CQueryOrderPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQueryOrderPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_QUERYORDER };
	CRect		m_RectWorkingArea;
	CFont		m_FontStatic1;
	CFont		m_FontEdit1;
	LOGFONT		m_FontList1;

	CDateTimeCtrl m_DateTimeQuery;
	CListCtrl	m_TableShowCtrl;
	std::vector<CString>	m_szFileNameV;
	std::set<CString>	m_szFileNameSet;

	CEdit		m_Edit;
	int			m_nRow;
	int			m_nCol;

protected:
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void OnResizeControl(int CtrlID, double cx, double cy);
	void GetFiles(const std::string & path, std::vector<std::string> & files);
	void SetTable(std::vector<std::vector<CString>>& szTableData);

public:
	afx_msg void OnBnClickedQueryorder();

	void SetWorkingArea(CRect & rect);	
	afx_msg void OnNMDblclkListQueryorder(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSaveorder();
};
