#pragma once

#include <vector>

class CAllOrderTable
{
public:
	static CAllOrderTable* Instance();

	BOOL CreateTable();
	BOOL AddOrder(const std::vector<CString>& szRowDataV);

	BOOL QueryOrderByOrderID(const CString szOrderID, std::vector<CString>& szOrderInfoV);
	BOOL QueryOrderByCustomerID(const CString szCustomerID, std::vector<std::vector<CString>>& szOrderInfoVV);
	BOOL QueryOrderByDay(const CString szDay, std::vector<std::vector<CString>>& szOrderInfoVV);
	BOOL QueryOrderByCusIDNDay(const CString szCustomerID, const CString szDay, std::vector<std::vector<CString>>& szOrderInfoVV);

	BOOL AlterOrderItem(const CString szOrderID, const CString szColName, const CString szValue);

protected:
	CAllOrderTable();
	~CAllOrderTable();

	CString					m_szTableName;
	std::vector<CString>	m_szTableColumnV;

};

