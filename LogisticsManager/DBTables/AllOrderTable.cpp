#include "stdafx.h"
#include "AllOrderTable.h"

#include "DataBase/DBConn.h"

CAllOrderTable::CAllOrderTable()
{
	m_szTableName = "AllOrderList";

	m_szTableColumnV.clear();
	m_szTableColumnV.push_back("OrderID");
	m_szTableColumnV.push_back("ReceiveDate");
	m_szTableColumnV.push_back("DeliveryDate");
	m_szTableColumnV.push_back("Carrier");
	m_szTableColumnV.push_back("CustomerID");
	m_szTableColumnV.push_back("Goods");
	m_szTableColumnV.push_back("Quantity");
	m_szTableColumnV.push_back("Volume");
	m_szTableColumnV.push_back("PackingMethod");
	m_szTableColumnV.push_back("Fare");
	m_szTableColumnV.push_back("PayWay");
	m_szTableColumnV.push_back("StoreRoom");
	m_szTableColumnV.push_back("CurrentStatus");
}


CAllOrderTable::~CAllOrderTable()
{
}


CAllOrderTable* CAllOrderTable::Instance()
{
	static CAllOrderTable instance;

	return &instance;
}


BOOL CAllOrderTable::CreateTable()
{
	BOOL bReply = CDBConn::Instance()->CreateTable(m_szTableName, m_szTableColumnV);

	return bReply;
}


BOOL CAllOrderTable::AddOrder(const std::vector<CString>& szRowDataV)
{
	if (szRowDataV.size() != m_szTableColumnV.size())
	{
		return FALSE;
	}

	BOOL bReply = CDBConn::Instance()->AddTableRecord(m_szTableName, m_szTableColumnV, szRowDataV);

	return bReply;
}


BOOL CAllOrderTable::QueryOrderByOrderID(const CString szOrderID, std::vector<CString>& szOrderInfoV)
{
	BOOL bReply = FALSE;

	szOrderInfoV.clear();
	CString szSQLCmd;
	szSQLCmd.Format("SELECT * FROM [%s] WHERE OrderID = '%s'", m_szTableName, szOrderID);

	_RecordsetPtr pRecordset;
	bReply = CDBConn::Instance()->SQLCommandQuery(szSQLCmd, pRecordset);

	if (!bReply)
	{
		return bReply;
	}

	auto iterCol = m_szTableColumnV.begin();
	while (!pRecordset->adoEOF)
	{
		if (iterCol == m_szTableColumnV.end())
		{
			break;
		}

		szOrderInfoV.push_back(pRecordset->GetCollect(_variant_t(*iterCol++)));
	}
	pRecordset->Close();

	return bReply;
}


BOOL CAllOrderTable::QueryOrderByCustomerID(const CString szCustomerID, std::vector<std::vector<CString>>& szOrderInfoVV)
{
	BOOL bReply = FALSE;

	szOrderInfoVV.clear();
	CString szSQLCmd;
	szSQLCmd.Format("SELECT * FROM [%s] WHERE CustomerID = '%s'", m_szTableName, szCustomerID);

	_RecordsetPtr pRecordset;
	bReply = CDBConn::Instance()->SQLCommandQuery(szSQLCmd, pRecordset);

	if (!bReply)
	{
		return bReply;
	}

	while (!pRecordset->adoEOF)
	{
		std::vector<CString> szRowDaraV;
		auto iterCol = m_szTableColumnV.begin();
		for (; iterCol != m_szTableColumnV.end(); ++iterCol)
		{
			szRowDaraV.push_back(pRecordset->GetCollect(_variant_t(*iterCol)));
		}

		szOrderInfoVV.push_back(szRowDaraV);

		pRecordset->MoveNext();
	}
	pRecordset->Close();

	return bReply;
}


BOOL CAllOrderTable::QueryOrderByDay(const CString szDay, std::vector<std::vector<CString>>& szOrderInfoVV)
{
	BOOL bReply = FALSE;

	szOrderInfoVV.clear();
	CString szSQLCmd;
	szSQLCmd.Format("SELECT * FROM [%s] WHERE ReceiveDate = '%s'", m_szTableName, szDay);

	_RecordsetPtr pRecordset;
	bReply = CDBConn::Instance()->SQLCommandQuery(szSQLCmd, pRecordset);

	if (!bReply)
	{
		return bReply;
	}

	while (!pRecordset->adoEOF)
	{
		std::vector<CString> szRowDaraV;
		auto iterCol = m_szTableColumnV.begin();
		for (; iterCol != m_szTableColumnV.end(); ++iterCol)
		{
			szRowDaraV.push_back(pRecordset->GetCollect(_variant_t(*iterCol)));
		}

		szOrderInfoVV.push_back(szRowDaraV);

		pRecordset->MoveNext();
	}
	pRecordset->Close();

	return bReply;
}


BOOL CAllOrderTable::QueryOrderByCusIDNDay(const CString szCustomerID, const CString szDay, std::vector<std::vector<CString>>& szOrderInfoVV)
{
	BOOL bReply = FALSE;

	szOrderInfoVV.clear();
	CString szSQLCmd;
	szSQLCmd.Format("SELECT * FROM [%s] WHERE ReceiveDate = '%s' AND CustomerID = '%s'", m_szTableName, szDay, szCustomerID);

	_RecordsetPtr pRecordset;
	bReply = CDBConn::Instance()->SQLCommandQuery(szSQLCmd, pRecordset);

	if (!bReply)
	{
		return bReply;
	}

	while (!pRecordset->adoEOF)
	{
		std::vector<CString> szRowDaraV;
		auto iterCol = m_szTableColumnV.begin();
		for (; iterCol != m_szTableColumnV.end(); ++iterCol)
		{
			szRowDaraV.push_back(pRecordset->GetCollect(_variant_t(*iterCol)));
		}

		szOrderInfoVV.push_back(szRowDaraV);

		pRecordset->MoveNext();
	}
	pRecordset->Close();

	return bReply;
}
