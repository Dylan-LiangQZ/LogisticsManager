#pragma once

#include <map>
#include <string>
#include <vector>

#include "Tinyxml/XMLFile.h"

static const CString gOrderListCol[] =
{
	_T("������"),
	_T("�ջ�����"),
	_T("��������"),
	_T("������"),
	_T("�ͻ�����"),
	_T("��Ʒ"),
	_T("����"),
	_T("���"),
	_T("��װ��ʽ"),
	_T("����"),
	_T("֧����ʽ"),
	_T("�ջ��ⷿ"),
	_T("��ǰ״̬"),
};

static const CString gPackingSize[] =
{
	_T("����һ"),
	_T("����һ"),
	_T("�ĺ�һ"),
	_T("���һ"),
};

class CLMCommonVariable
{
public:
	static CLMCommonVariable* Instance();

	void	LoadPackingWay(CXMLElementHandle& elementHandle);
	void	SavePackingWay(CXMLElementHandle& elementHandle);
	
	void	LoadPayWay(CXMLElementHandle& elementHandle);
	void	SavePayWay(CXMLElementHandle& elementHandle);

	void	LoadDeliveyFare(CXMLElementHandle& elementHandle);
	void	SetCusIDMap();
	BOOL	CheckCusIDMap(const CString szID, const CString szPhone);

	std::map<int, std::wstring>	m_PackingWayMap;
	std::map<int, std::wstring>	m_PayWayMap;

	std::map<CString, CString> m_CusIDnPhoneMap;

	double m_dWeightVolumeThres;
	double m_dWeightPrice;
	double m_dVolumePrice;

protected:
	CLMCommonVariable();
	~CLMCommonVariable();

};


inline std::string ws2s(std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";

	setlocale(LC_ALL, "chs");

	const wchar_t* _Source = ws.c_str();

	size_t _Dsize = 2 * ws.size() + 1;

	char *_Dest = new char[_Dsize];

	memset(_Dest, 0, _Dsize);

	wcstombs(_Dest, _Source, _Dsize);

	std::string result = _Dest;

	delete[]_Dest;

	setlocale(LC_ALL, curLocale.c_str());

	return result;
}