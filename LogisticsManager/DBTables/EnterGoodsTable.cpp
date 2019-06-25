#include "stdafx.h"
#include "EnterGoodsTable.h"
#include "DataBase/DBConn.h"

CEnterGoodsTable::CEnterGoodsTable()
{
	m_szTableName = "EnterGoodsList";

	m_szTableColumnV.push_back(_T("DateTime"));
	m_szTableColumnV.push_back(_T("CustomerID"));
	m_szTableColumnV.push_back(_T("GoodsName"));
	m_szTableColumnV.push_back(_T("Number"));
	m_szTableColumnV.push_back(_T("Supplier"));
	m_szTableColumnV.push_back(_T("Phone"));
}


CEnterGoodsTable::~CEnterGoodsTable()
{
}


CEnterGoodsTable* CEnterGoodsTable::Instance()
{
	static CEnterGoodsTable instance;

	return &instance;
}


BOOL CEnterGoodsTable::CreateTable()
{
	BOOL bReply = CDBConn::Instance()->CreateTable(m_szTableName, m_szTableColumnV);
	CString szErrInfo = CDBConn::Instance()->GetLastErrInfo();

	return bReply;
}


BOOL CEnterGoodsTable::AddEnterGoodsInfo(const std::vector<CString>& szEnterGoodsInfoV)
{
	BOOL bReply = CDBConn::Instance()->AddTableRecord(m_szTableName, m_szTableColumnV, szEnterGoodsInfoV);
	CString szErrInfo = CDBConn::Instance()->GetLastErrInfo();

	return bReply;
}


BOOL CEnterGoodsTable::QueryEnterGoodsByCustomerID(const CString szCustomerID, const CString szSupplier,
	const CString szDateTime, std::vector<std::vector<CString>>& szEnterGoodsInfoVV)
{
	BOOL bReply = FALSE;

	szEnterGoodsInfoVV.clear();

	CString szSQLCmd;
	szSQLCmd.Format("SELECT * FROM [%s] WHERE ", m_szTableName);
	CString szCondition = "";
	if (!szCustomerID.IsEmpty())
	{
		szCondition.Format("CustomerID = '%s' ", szCustomerID);
		szSQLCmd += szCondition;
	}

	if (!szSupplier.IsEmpty())
	{
		if (!szCondition.IsEmpty())
		{
			szSQLCmd += "and ";
		}
		szCondition.Format("Supplier = '%s' ", szSupplier);
		szSQLCmd += szCondition;
	}

	if (!szDateTime.IsEmpty())
	{
		if (!szCondition.IsEmpty())
		{
			szSQLCmd += "and ";
		}
		CString szCurrDayS, szCurrDayE;
		szCurrDayS = szDateTime + " 00:00:00";
		szCurrDayE = szDateTime + " 23:59:59";
		szCondition.Format("CAST(DateTime AS DATETIME) >= '%s' AND CAST(DateTime AS DATETIME) <= '%s'", 
			szCurrDayS, szCurrDayE);
		szSQLCmd += szCondition;
	}

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

		szEnterGoodsInfoVV.push_back(szRowDaraV);

		pRecordset->MoveNext();
	}
	pRecordset->Close();

	return bReply;
}

