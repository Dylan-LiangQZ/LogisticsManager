#pragma once
#include "afxcmn.h"

#include <vector>
#include <string>

class CTableControl
{
public:
	CTableControl();
	~CTableControl();

	int CreateTable(const RECT& rect, CWnd* pParentWnd, UINT nID);
	int InsertTableColmuns(const std::vector<CString>& szTableColV);
	int AddRowData(const std::vector<CString>& szRawDataV);

protected:
	CListCtrl				m_ListCtrl;
	std::vector<CString>	m_szTableColV;
	bool					m_bCreated;
	
};

