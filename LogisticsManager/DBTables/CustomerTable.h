#pragma once

#include <vector>

class CCustomerListTable
{
public:
	static CCustomerListTable* Instance();

	BOOL CreateTable();
	BOOL AddCustomerInfo(const std::vector<CString>& szCustomerInfoV);

	BOOL QueryCustomerInfoByCustomerID(const CString szCustomerID, std::vector<CString>& szCustomerInfoV);
	BOOL QueryCustomerInfoByCustomerName(const CString szCustomerName, std::vector<CString>& szCustomerInfoV);
	BOOL QueryCustomerInfoByPhone(const CString szPhoneNum, std::vector<CString>& szCustomerInfoV);

	BOOL AlterCustomerInfoByQueryPhone(const CString szPhoneNum, const std::vector<CString>& szCustomerInfoV);
	
protected:
	CCustomerListTable();
	~CCustomerListTable();

	CString					m_szTableName;
	std::vector<CString>	m_szTableColumnV;
};



class CustomerAccountTable
{
public:
	static CustomerAccountTable* Instance();

	BOOL CreateTable();

	BOOL AddCustomerAccountRecord(const CString szPhoneNumber, const std::vector<CString>& szAccountRecordV);

protected:
	CustomerAccountTable();
	~CustomerAccountTable();

	CString					m_szTableName;
	std::vector<CString>	m_szTableColumnV;
};

