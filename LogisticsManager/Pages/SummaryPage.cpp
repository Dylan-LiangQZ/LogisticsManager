// SummaryPage.cpp : implementation file
//
#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "SummaryPage.h"
#include "afxdialogex.h"


// CSummaryPage dialog

IMPLEMENT_DYNAMIC(CSummaryPage, CDialogEx)

CSummaryPage::CSummaryPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSummaryPage::IDD, pParent)
{

}

CSummaryPage::~CSummaryPage()
{
}

void CSummaryPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSummaryPage, CDialogEx)
END_MESSAGE_MAP()


// CSummaryPage message handlers
BOOL CSummaryPage::OnInitDialog()
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

	//OnResizeControl(IDC_STATIC_Q1, cx, cy);
	//OnResizeControl(IDC_STATIC_Q2, cx, cy);
	//OnResizeControl(IDC_STATIC_Q3, cx, cy);
	//OnResizeControl(IDC_EDIT_ORDERID, cx, cy);
	//OnResizeControl(IDC_EDIT_CUSTOMERID, cx, cy);
	//OnResizeControl(IDC_DATETIMEPICKER3, cx, cy);
	//OnResizeControl(ID_QueryOrder, cx, cy);
	//OnResizeControl(ID_SaveOrder, cx, cy);
	//OnResizeControl(IDC_LIST_QUERYORDER, cx, cy);

	//m_FontStatic1.CreatePointFont((int)(65 * cx), _T("宋体"));
	//m_FontEdit1.CreateFont(20 * cy, 0, 0, 0, 25,
	//	FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	//	OUT_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Arial");

	//GetDlgItem(IDC_STATIC_Q1)->SetFont(&m_FontStatic1);
	//GetDlgItem(IDC_STATIC_Q2)->SetFont(&m_FontStatic1);
	//GetDlgItem(IDC_STATIC_Q3)->SetFont(&m_FontStatic1);
	//GetDlgItem(IDC_EDIT_ORDERID)->SetFont(&m_FontEdit1);
	//GetDlgItem(IDC_EDIT_CUSTOMERID)->SetFont(&m_FontEdit1);
	//GetDlgItem(IDC_DATETIMEPICKER3)->SetFont(&m_FontStatic1);
	//GetDlgItem(ID_QueryOrder)->SetFont(&m_FontStatic1);
	//GetDlgItem(ID_SaveOrder)->SetFont(&m_FontStatic1);

	//CRect rectTab1;
	//m_TableShowCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE
	//	| LVS_EX_UNDERLINEHOT | LVS_EX_FULLROWSELECT);
	//GetDlgItem(IDC_LIST_QUERYORDER)->GetWindowRect(&rectTab1);
	//int nEditColSize = sizeof(gOrderListCol) / sizeof(gOrderListCol[0]);
	//for (int i = 0; i < nEditColSize; ++i)
	//{
	//	m_TableShowCtrl.InsertColumn(i, gOrderListCol[i], LVCFMT_LEFT, rectTab1.Width() / nEditColSize - 1, 0);
	//}

	//CFont   *pfont1 = m_TableShowCtrl.GetFont();
	//pfont1->GetLogFont(&m_FontList1);
	//m_FontList1.lfWidth = m_FontList1.lfWidth * cx;
	//m_FontList1.lfHeight = m_FontList1.lfHeight * cy;
	//static   CFont   font;
	//font.CreateFontIndirect(&m_FontList1);
	//m_TableShowCtrl.SetFont(&font);
	//font.Detach();

	//m_Edit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_QUERYORDER), 30001);
	//m_Edit.SetFont(&m_FontEdit1);
	//m_Edit.ShowWindow(SW_HIDE);

	//COleDateTime oletimeTime = COleDateTime::GetCurrentTime();
	//oletimeTime.SetStatus(COleDateTime::null);
	//m_DateTimeQuery.SetTime(oletimeTime);

	return FALSE;
}


void CSummaryPage::OnResizeControl(int CtrlID, double cx, double cy)
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

void CSummaryPage::SetWorkingArea(CRect & rect)
{
	m_RectWorkingArea = rect;
}