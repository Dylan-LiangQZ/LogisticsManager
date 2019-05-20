#include "stdafx.h"
#include "CustomerTable.h"

#include "DataBase/DBConn.h"

CCustomerListTable::CCustomerListTable()
{
	m_szTableName = "CustomerList";

	m_szTableColumnV.clear();
	m_szTableColumnV.push_back("CustomerName");
	m_szTableColumnV.push_back("PhoneNumber1");
	m_szTableColumnV.push_back("PhoneNumber2");
	m_szTableColumnV.push_back("Email");
	m_szTableColumnV.push_back("Address");
	m_szTableColumnV.push_back("Balance");
	m_szTableColumnV.push_back("Destination1");
	m_szTableColumnV.push_back("CustomerID1");
	m_szTableColumnV.push_back("Destination2");
	m_szTableColumnV.push_back("CustomerID2");
	m_szTableColumnV.push_back("Destination3");
	m_szTableColumnV.push_back("CustomerID3");
	m_szTableColumnV.push_back("Destination4");
	m_szTableColumnV.push_back("CustomerID4");
}


CCustomerListTable::~CCustomerListTable()
{
}


CCustomerListTable* CCustomerListTable::Instance()
{
	static CCustomerListTable instance;

	return &instance;
}


BOOL CCustomerListTable::CreateTable()
{
	BOOL bReply = CDBConn::Instance()->CreateTable(m_szTableName, m_szTableColumnV);
	CString szErrInfo = CDBConn::Instance()->GetLastErrInfo();

	return bReply;
}


BOOL CCustomerListTable::AddCustomerInfo(const std::vector<CString>& szCustomerInfoV)
{
	BOOL bReply = CDBConn::Instance()->AddTableRecord(m_szTableName, m_szTableColumnV, szCustomerInfoV);
	CString szErrInfo = CDBConn::Instance()->GetLastErrInfo();

	return bReply;
}


BOOL CCustomerListTable::QueryCustomerInfoByCustomerID(const CString szCustomerID, std::vector<CString>& szCustomerInfoV)
{
	BOOL bReply = FALSE;

	szCustomerInfoV.clear();
	CString szSQLCmd;
	szSQLCmd.Format("SELECT * FROM [%s] WHERE CustomerID1 = '%s' or CustomerID2 = '%s' or CustomerID3 = '%s' or CustomerID4 = '%s'", m_szTableName, szCustomerID, szCustomerID, szCustomerID, szCustomerID);
	
	_RecordsetPtr pRecordset;
	bReply = CDBConn::Instance()->SQLCommandQuery(m_szTableName, szSQLCmd, pRecordset);

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

		szCustomerInfoV.push_back(pRecordset->GetCollect(_variant_t(*iterCol++)));
	}
	pRecordset->Close();

	return bReply;
}