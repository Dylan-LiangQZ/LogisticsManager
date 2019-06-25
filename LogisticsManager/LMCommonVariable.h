#pragma once

#include <map>
#include <string>
#include <vector>

#include "Tinyxml/XMLFile.h"

static const CString gOrderListCol[] =
{
	_T("订单号"),
	_T("收货日期"),
	_T("发货日期"),
	_T("承运商"),
	_T("客户代码"),
	_T("商品"),
	_T("数量"),
	_T("体积"),
	_T("包装方式"),
	_T("费用"),
	_T("支付方式"),
	_T("收货库房"),
	_T("当前状态"),
};

static const CString gPackingSize[] =
{
	_T("二合一"),
	_T("三合一"),
	_T("四合一"),
	_T("五合一"),
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