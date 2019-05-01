#pragma once

#include <string>
#include <vector>
#include <set>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF") rename("BOF", "adoBOF")

class CDBConn
{
public:
	static CDBConn* Instance();

	int CreateDataBase(const CString szDBName);

	int CreateTable(const CString szTableName, const std::vector<CString>& szColumnName);

	int AddTableRecord(const CString szTableName, const std::vector<CString>& szRowData);

	int QueryTablebyKey(const CString szTableName, const CString szKey, std::vector<CString>& szRowData);

private:
	CDBConn();
	~CDBConn();

	_ConnectionPtr		m_pConn;
	std::set<CString>	m_szTableNameSet;

};

