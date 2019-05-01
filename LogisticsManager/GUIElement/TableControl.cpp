#pragma once

#include "stdafx.h"
#include "TableControl.h"


CTableControl::CTableControl()
{
	m_szTableColV.clear();
	m_bCreated = false;
}


CTableControl::~CTableControl()
{
}


int CTableControl::CreateTable(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_ListCtrl.Create(LVS_REPORT, rect, pParentWnd, nID);

	m_bCreated = true;

	return 0;
}


int CTableControl::InsertTableColmuns(const std::vector<CString>& szTableColV)
{
	if (!m_bCreated)
	{
		return -1;
	}

	m_szTableColV = szTableColV;

	int nColIndex = 0;
	for (auto iter = szTableColV.begin(); iter != szTableColV.end(); ++iter)
	{
		m_ListCtrl.InsertColumn(nColIndex, *iter, LVCFMT_LEFT);

		++nColIndex;
	}

	return 0;
}


int CTableControl::AddRowData(const std::vector<CString>& szRawDataV)
{
	if (!m_bCreated || m_szTableColV.empty() || szRawDataV.size() != m_szTableColV.size())
	{
		return -1;
	}

	int nRowIndex = m_ListCtrl.InsertItem(0, "");
	int nSubIndex = 0;
	for (auto iter = szRawDataV.begin(); iter != szRawDataV.end(); ++iter)
	{
		m_ListCtrl.SetItemText(nRowIndex, nSubIndex, *iter);

		++nSubIndex;
	}

	return 0;
}