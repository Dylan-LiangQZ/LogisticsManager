#pragma once

#include <vector>

enum EnterGoodsTableItem
{
	EGT_DateTime = 0,
	EGT_CustomerID,
	EGT_GoodsName,
	EGT_Number,
	EGT_Supplier,
	EGT_Phone,

	EGT_MaxItem
};

static const CString gEnterGoodsCol[] =
{
	_T("����"),
	_T("�ͻ����"),
	_T("Ʒ��"),
	_T("����"),
	_T("��Ӧ��"),
	_T("�绰"),
};

class CEnterGoodsTable
{
public:
	static CEnterGoodsTable* Instance();

	BOOL CreateTable();
	BOOL AddEnterGoodsInfo(const std::vector<CString>& szEnterGoodsInfoV);

	BOOL QueryEnterGoodsByCustomerID(const CString szCustomerID, const CString szSupplier, 
		const CString szDateTime, std::vector<std::vector<CString>>& szEnterGoodsInfoVV);
	
private:
	CEnterGoodsTable();
	~CEnterGoodsTable();

	CString					m_szTableName;
	std::vector<CString>	m_szTableColumnV;
};

