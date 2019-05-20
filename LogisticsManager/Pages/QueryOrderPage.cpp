// QueryOrder.cpp : implementation file
//

#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "QueryOrderPage.h"
#include "afxdialogex.h"
#include <io.h>  

#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>
#include "..\DBTables\AllOrderTable.h"
#include "..\LMCommonVariable.h"

using namespace std;
// CQueryOrderPage dialog

IMPLEMENT_DYNAMIC(CQueryOrderPage, CDialogEx)

CQueryOrderPage::CQueryOrderPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQueryOrderPage::IDD, pParent)
{

}

CQueryOrderPage::~CQueryOrderPage()
{
}

void CQueryOrderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_QUERYORDER, m_TableShowCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_DateTimeQuery);
}


BEGIN_MESSAGE_MAP(CQueryOrderPage, CDialogEx)
	
	ON_BN_CLICKED(ID_QueryOrder, &CQueryOrderPage::OnBnClickedQueryorder)
END_MESSAGE_MAP()


// CQueryOrderPage message handlers
BOOL CQueryOrderPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CRect rectDlg;
	GetClientRect(rectDlg);

	MoveWindow(m_RectWorkingArea);

	double cx = 1.0 * m_RectWorkingArea.Width() / rectDlg.Width();
	double cy = 1.0 * m_RectWorkingArea.Height() / rectDlg.Height();

	OnResizeControl(IDC_STATIC_Q1, cx, cy);
	OnResizeControl(IDC_STATIC_Q2, cx, cy);
	OnResizeControl(IDC_STATIC_Q3, cx, cy);
	OnResizeControl(IDC_EDIT_ORDERID, cx, cy);
	OnResizeControl(IDC_EDIT_CUSTOMERID, cx, cy);
	OnResizeControl(IDC_DATETIMEPICKER3, cx, cy);
	OnResizeControl(ID_QueryOrder, cx, cy);
	OnResizeControl(ID_SaveOrder, cx, cy);
	OnResizeControl(IDC_LIST_QUERYORDER, cx, cy);
	
	m_FontStatic1.CreatePointFont((int)(65 * cx), _T("宋体"));
	m_FontEdit1.CreateFont(22 * cy, 0, 0, 0, 35,
		FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Arial");

	GetDlgItem(IDC_STATIC_Q1)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_Q2)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_Q3)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_EDIT_ORDERID)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_CUSTOMERID)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_DATETIMEPICKER3)->SetFont(&m_FontStatic1);
	GetDlgItem(ID_QueryOrder)->SetFont(&m_FontStatic1);
	GetDlgItem(ID_SaveOrder)->SetFont(&m_FontStatic1);

	CRect rectTab1;
	m_TableShowCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	GetDlgItem(IDC_LIST_QUERYORDER)->GetWindowRect(&rectTab1);
	int nEditColSize = sizeof(gOrderListCol) / sizeof(gOrderListCol[0]);
	for (int i = 0; i < nEditColSize; ++i)
	{
		m_TableShowCtrl.InsertColumn(i, gOrderListCol[i], LVCFMT_LEFT, rectTab1.Width() / nEditColSize - 1, 0);
	}

	CFont   *pfont1 = m_TableShowCtrl.GetFont();
	pfont1->GetLogFont(&m_FontList1);
	m_FontList1.lfWidth = m_FontList1.lfWidth * cx;
	m_FontList1.lfHeight = m_FontList1.lfHeight * cy;
	static   CFont   font;
	font.CreateFontIndirect(&m_FontList1);
	m_TableShowCtrl.SetFont(&font);
	font.Detach();

	COleDateTime oletimeTime = COleDateTime::GetCurrentTime();
	oletimeTime.SetStatus(COleDateTime::null);
	m_DateTimeQuery.SetTime(oletimeTime);

	return FALSE;
}


void CQueryOrderPage::GetFiles(const std::string & path, std::vector<std::string> & files)
{
	m_szFileNameV.clear();

	
	long hFile = 0;
	struct  _finddata_t fileinfo;
	std::string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(fileinfo.name);
			}

		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


void CQueryOrderPage::SetTable(std::vector<std::vector<CString>>& szTableData)
{
	m_TableShowCtrl.DeleteAllItems();

	auto iterRow = szTableData.begin();
	for (; iterRow != szTableData.end(); ++iterRow)
	{
		int nRow = m_TableShowCtrl.InsertItem(0, "");
		auto iterRowData = (*iterRow).begin();
		for (int i = 0; i < (*iterRow).size(); ++i, ++iterRowData)
		{
			m_TableShowCtrl.SetItemText(nRow, i, *iterRowData);
		}
	}
}


void CQueryOrderPage::SetWorkingArea(CRect & rect)
{
	m_RectWorkingArea = rect;
}


void CQueryOrderPage::OnResizeControl(int CtrlID, double cx, double cy)
{
	CWnd * pWnd;
	pWnd = GetDlgItem(CtrlID);
	if (pWnd != NULL)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.left = (int)(rect.left * cx);
		rect.right = (int)(rect.right * cx);
		rect.top = (int)(rect.top * cy);
		rect.bottom = (int)(rect.bottom * cy);
		pWnd->MoveWindow(rect);
	}
}


void CQueryOrderPage::OnBnClickedQueryorder()
{
	// TODO: Add your control notification handler code here
	CString szOrderID;
	GetDlgItem(IDC_EDIT_ORDERID)->GetWindowText(szOrderID);

	CString szCusID;
	GetDlgItem(IDC_EDIT_CUSTOMERID)->GetWindowText(szCusID);

	CTime time;
	DWORD dwResult = m_DateTimeQuery.GetTime(time);
	CString szDayQuery = time.Format("%Y-%m-%d");

	
	BOOL bReply;

	std::vector<std::vector<CString>> szTableDataVV;

	if (szOrderID != "")
	{
		std::vector<CString> szOrderInfoV;
		bReply =  CAllOrderTable::Instance()->QueryOrderByOrderID(szOrderID, szOrderInfoV);

		if (bReply)
		{
			szTableDataVV.push_back(szOrderInfoV);
			SetTable(szTableDataVV);
			return;
		}		
	}

	if (szCusID != "")
	{
		if (dwResult != GDT_VALID)
		{
			bReply = CAllOrderTable::Instance()->QueryOrderByCustomerID(szCusID, szTableDataVV);

			if (bReply)
			{
				SetTable(szTableDataVV);
				return;
			}
		}
		else
		{
			bReply = CAllOrderTable::Instance()->QueryOrderByCusIDNDay(szCusID, szDayQuery, szTableDataVV);

			if (bReply)
			{
				SetTable(szTableDataVV);
				return;
			}
		}
	}
	else
	{
		bReply = CAllOrderTable::Instance()->QueryOrderByDay(szDayQuery, szTableDataVV);

		if (bReply)
		{
			SetTable(szTableDataVV);
			return;
		}
	}
}
