#pragma once

#include <vector>

class CCustomerListTable
{
public:
	static CCustomerListTable* Instance();

	BOOL CreateTable();
	BOOL AddCustomerInfo(const std::vector<CString>& szCustomerInfoV);

	BOOL QueryCustomerInfoByCustomerID(const CString szCustomerID, std::vector<CString>& szCustomerInfoV);

protected:
	CCustomerListTable();
	~CCustomerListTable();

	CString					m_szTableName;
	std::vector<CString>	m_szTableColumnV;
};


