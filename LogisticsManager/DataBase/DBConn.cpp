#include "stdafx.h"
#include "DBConn.h"


CDBConn::CDBConn()
{
	m_pConn = NULL;

	::CoInitialize(NULL);
}


CDBConn::~CDBConn()
{
	if (m_pConn != NULL)
	{
		m_pConn->Close();
		m_pConn.Detach();
		m_pConn = NULL;
	}

	::CoUninitialize();
}


CDBConn* CDBConn::Instance()
{
	static CDBConn instance;

	return &instance;
}


int CDBConn::CreateDataBase(const CString szDBName)
{
	try
	{
		CString szSql;

		//HRESULT hRes = m_pConn.CreateInstance("ADODB.Connection");
		//if (SUCCEEDED(hRes))
		//{
		//	szSql.Format("                 ");
		//}
	}
	catch (...)
	{
	}

	return 0;
}