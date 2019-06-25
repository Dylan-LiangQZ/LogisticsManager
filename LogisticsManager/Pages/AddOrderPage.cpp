// AddOrderPage.cpp : implementation file
//

#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "AddOrderPage.h"
#include "afxdialogex.h"
#include <fstream>
#include "..\DBTables\AllOrderTable.h"
#include "..\DBTables\CustomerTable.h"
#include "..\LMCommonVariable.h"

// CAddOrderPage dialog

#define SYN_TIMER_ID 1

static const CString gCustomerInfo[] =
{
	_T("客户姓名 :"),
	_T("联系方式 :"),
	_T("收货库房 :"),
	_T("账户余额 :"),
};

static const CString gAddListCol[] =
{
	_T("商品"),
	_T("件数"),
	_T("重量"),
	_T("长"),
	_T("宽"),
	_T("高"),
	_T("承运商"),
	_T("包装规格"),
	_T("包装方式"),
	_T("支付方式"),
};


static const CString gFareListCol[] =
{
	_T("密度"),
	_T("运费"),
	_T("包装费"),
	_T("保险费"),
	_T("总费用"),
};


IMPLEMENT_DYNAMIC(CAddOrderPage, CDialogEx)

CAddOrderPage::CAddOrderPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddOrderPage::IDD, pParent)
{

}

CAddOrderPage::~CAddOrderPage()
{
	for (int i = 0; i < sizeof(gAddListCol) / sizeof(gAddListCol[0]); i++)
	{
		CEdit* pEdit = (CEdit*)m_pAddOrderEdits.GetAt(i);
		if (pEdit != NULL)
			delete pEdit;
		m_pAddOrderEdits[i] = NULL;
	}
	m_pAddOrderEdits.RemoveAll();
}

void CAddOrderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_CUSTOMER, m_TableCustInfo);
	DDX_Control(pDX, IDC_LIST_ADDORDER, m_TableAddCtrl);
	DDX_Control(pDX, IDC_LIST_FARELIST, m_TableFareCtrl);
	DDX_Control(pDX, IDC_LIST_SHOWORDER, m_TableShowOrder);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateTimeRecive);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_DateTimeDelivey);
}


BEGIN_MESSAGE_MAP(CAddOrderPage, CDialogEx)
	ON_WM_PAINT()	
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADDITEM, &CAddOrderPage::OnBnClickedButtonAddItem)
	ON_BN_CLICKED(IDC_BUTTON_CALFARE, &CAddOrderPage::OnBnClickedButtonCalfare)
	ON_BN_CLICKED(IDC_BUTTON_QUERYCUST, &CAddOrderPage::OnBnClickedButtonQuerycust)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAddOrderPage message handlers
BOOL CAddOrderPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CAllOrderTable::Instance()->CreateTable();

	// 控件布局设计
	CRect rectDlg;
	GetClientRect(rectDlg);

	MoveWindow(m_RectWorkingArea);
	
	double cx = 1.0 * m_RectWorkingArea.Width() / rectDlg.Width();
	double cy = 1.0 * m_RectWorkingArea.Height() / rectDlg.Height();

	OnResizeControl(IDC_STATIC_G1, cx, cy);
	OnResizeControl(IDC_EDIT_ORDERNAME, cx, cy);
	OnResizeControl(IDC_BUTTON_QUERYCUST, cx, cy);
	OnResizeControl(IDC_LIST_CUSTOMER, cx, cy);
	OnResizeControl(IDC_STATIC_G2, cx, cy);
	OnResizeControl(IDC_STATIC_T1, cx, cy);
	OnResizeControl(IDC_DATETIMEPICKER1, cx, cy);
	OnResizeControl(IDC_STATIC_T2, cx, cy);
	OnResizeControl(IDC_DATETIMEPICKER2, cx, cy);
	OnResizeControl(IDC_LIST_ADDORDER, cx, cy);
	OnResizeControl(IDC_BUTTON_CALFARE, cx, cy);
	OnResizeControl(IDC_LIST_FARELIST, cx, cy);
	OnResizeControl(IDC_BUTTON_ADDITEM, cx, cy);
	OnResizeControl(IDC_LIST_SHOWORDER, cx, cy);

	m_FontStatic1.CreatePointFont((int)(65 * cx), _T("宋体"));
	m_FontEdit1.CreateFont(20 * cy, 0, 0, 0, 30,
		FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Arial");

	GetDlgItem(IDC_EDIT_ORDERNAME)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_BUTTON_QUERYCUST)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_BUTTON_CALFARE)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_BUTTON_ADDITEM)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_DATETIMEPICKER1)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_DATETIMEPICKER2)->SetFont(&m_FontStatic1);

	// Create Table

	// 1. Customers Information
	m_TableCustInfo.SetExtendedStyle(LVS_EX_GRIDLINES);
	CRect rectTab1;
	GetDlgItem(IDC_LIST_CUSTOMER)->GetWindowRect(&rectTab1);
	m_TableCustInfo.InsertColumn(0, "", LVCFMT_LEFT, rectTab1.Width()*0.3, 0);
	m_TableCustInfo.InsertColumn(1, "", LVCFMT_LEFT, rectTab1.Width()*0.69, 0);
	
	CFont   *pfont1 = m_TableCustInfo.GetFont();
	pfont1->GetLogFont(&m_FontList1);
	m_FontList1.lfWidth = m_FontList1.lfWidth * cx;
	m_FontList1.lfHeight = m_FontList1.lfHeight * cy;
	static   CFont   font1;
	font1.CreateFontIndirect(&m_FontList1);
	m_TableCustInfo.SetFont(&font1);
	font1.Detach();

	for (int i = 0; i < sizeof(gCustomerInfo) / sizeof(gCustomerInfo[0]); ++i)
	{
		int nRow = m_TableCustInfo.InsertItem(i, "");
		m_TableCustInfo.SetItemText(nRow, 0, gCustomerInfo[i]);
	}

	// 2. Add item table
	m_TableAddCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	GetDlgItem(IDC_LIST_ADDORDER)->GetWindowRect(&rectTab1);
	int nEditColSize = sizeof(gAddListCol) / sizeof(gAddListCol[0]);
	for (int i = 0; i < nEditColSize; ++i)
	{
		m_TableAddCtrl.InsertColumn(i, gAddListCol[i], LVCFMT_LEFT, rectTab1.Width() / nEditColSize - 1, 0);
	}

	pfont1 = m_TableAddCtrl.GetFont();
	pfont1->GetLogFont(&m_FontList2);
	m_FontList2.lfWidth = m_FontList2.lfWidth * cx;
	m_FontList2.lfHeight = m_FontList2.lfHeight * cy;
	static   CFont   font2;
	font2.CreateFontIndirect(&m_FontList2);
	m_TableAddCtrl.SetFont(&font2);
	font1.Detach();

	int perWidth = rectTab1.Width() / nEditColSize - 8;
	int perHeight = rectTab1.Height() * 0.5;
	CEdit *p_Edit;
	for (int nColIndex = 0; nColIndex < 7; ++nColIndex)
	{
		p_Edit = new CEdit();
		p_Edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(0,0,0,0), GetDlgItem(IDC_LIST_ADDORDER), 20001 + nColIndex);
		p_Edit->MoveWindow(3 + (perWidth+6)*nColIndex, rectTab1.Height()*0.4 + 5, perWidth, perHeight);
		p_Edit->SetWindowText("");
		m_pAddOrderEdits.Add((void*)p_Edit);
		p_Edit->SetFont(&m_FontEdit1);
	}
	m_PackingSizeCombo.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_ADDORDER), 20001 + 7);
	m_PackingSizeCombo.MoveWindow(3 + (perWidth + 6) * 7, rectTab1.Height()*0.4 + 5, perWidth + 5, perHeight + 200);
	for (int i=0; i < sizeof(gPackingSize)/sizeof(gPackingSize[0]); ++i)
	{
		m_PackingSizeCombo.AddString(gPackingSize[i]);
	}
	m_PackingSizeCombo.SetCurSel(0);
	m_PackingSizeCombo.SetFont(&m_FontEdit1);
	
	m_PackingWayCombo.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN  | WS_VSCROLL, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_ADDORDER), 20001 + 8);
	m_PackingWayCombo.MoveWindow(3 + (perWidth + 6)*8, rectTab1.Height()*0.4 + 5, perWidth + 5, perHeight + 200);
	auto iterPack = CLMCommonVariable::Instance()->m_PackingWayMap.begin();
	for (; iterPack != CLMCommonVariable::Instance()->m_PackingWayMap.end(); ++iterPack)
	{
		m_PackingWayCombo.AddString(CW2A((*iterPack).second.c_str()));
	}
	m_PackingWayCombo.SetCurSel(0);
	m_PackingWayCombo.SetFont(&m_FontEdit1);

	m_PayWayCombo.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_ADDORDER), 20001 + 9);
	m_PayWayCombo.MoveWindow(3 + (perWidth + 6) * 9, rectTab1.Height()*0.4 + 5, perWidth + 10, perHeight + 200);
	auto iterPay = CLMCommonVariable::Instance()->m_PayWayMap.begin();
	for (; iterPay != CLMCommonVariable::Instance()->m_PayWayMap.end(); ++iterPay)
	{
		m_PayWayCombo.AddString(CW2A((*iterPay).second.c_str()));
	}
	m_PayWayCombo.SetCurSel(0);
	m_PayWayCombo.SetFont(&m_FontEdit1);

	// 3. Fare table
	m_TableFareCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	GetDlgItem(IDC_LIST_FARELIST)->GetWindowRect(&rectTab1);
	nEditColSize = sizeof(gFareListCol) / sizeof(gFareListCol[0]);
	for (int i = 0; i < nEditColSize; ++i)
	{
		m_TableFareCtrl.InsertColumn(i, gFareListCol[i], LVCFMT_LEFT, rectTab1.Width() / nEditColSize - 1, 0);
	}

	static   CFont   font3;
	font3.CreateFontIndirect(&m_FontList2);
	m_TableFareCtrl.SetFont(&font3);

	int nRow = m_TableFareCtrl.InsertItem(0, "");
	for (int i = 0; i < nEditColSize; ++i)
	{
		m_TableFareCtrl.SetItemText(nRow, i, "0");
	}
	
	// 4. Show Order
	m_TableShowOrder.SetExtendedStyle(LVS_EX_GRIDLINES);
	GetDlgItem(IDC_LIST_SHOWORDER)->GetWindowRect(&rectTab1);
	nEditColSize = sizeof(gOrderListCol) / sizeof(gOrderListCol[0]);
	for (int i = 0; i < nEditColSize; ++i)
	{
		m_TableShowOrder.InsertColumn(i, gOrderListCol[i], LVCFMT_LEFT, rectTab1.Width() / nEditColSize - 1, 0);
	}

	pfont1 = m_TableShowOrder.GetFont();
	pfont1->GetLogFont(&m_FontList4);
	m_FontList4.lfWidth = m_FontList4.lfWidth * cx;
	m_FontList4.lfHeight = m_FontList4.lfHeight * cy;
	static   CFont   font4;
	font4.CreateFontIndirect(&m_FontList4);
	m_TableShowOrder.SetFont(&font4);
	font1.Detach();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CAddOrderPage::SetWorkingArea(CRect & rect)
{
	m_RectWorkingArea = rect;
}


void CAddOrderPage::OnResizeControl(int CtrlID, double cx, double cy)
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

HBRUSH CAddOrderPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	
	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC )
	{		
		pDC->SelectObject(&m_FontStatic1);

		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	if (nCtlColor == CTLCOLOR_BTN)
	{
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


double CAddOrderPage::CalculatePackingFare()
{
	int nPackSize = m_PackingSizeCombo.GetCurSel();
	int nPackWay = m_PackingWayCombo.GetCurSel();

	if (nPackWay == 3)
	{
		return 10;
	}

	double dStartF = 20 - 5 * nPackWay;
	double dFinal = dStartF + 5 * nPackSize;
	
	return dFinal;
}


void CAddOrderPage::UpdateDayOrderTable()
{
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	CString szDay;
	szDay.Format("%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);

	std::vector<std::vector<CString>> szTableDataVV;
	BOOL bReply = CAllOrderTable::Instance()->QueryOrderByDay(szDay, szTableDataVV);
	
	if (bReply)
	{
		m_TableCS.Lock();
		m_TableShowOrder.DeleteAllItems();
		for (auto iterData = szTableDataVV.begin(); iterData != szTableDataVV.end(); ++iterData)
		{
			int nRow = m_TableShowOrder.InsertItem(0, "");
			auto iterRowData = (*iterData).begin();
			for (int i = 0; i < (*iterData).size(); ++i, ++iterRowData)
			{
				m_TableShowOrder.SetItemText(nRow, i, *iterRowData);
			}
		}
		m_TableCS.Unlock();
	}

}


void CAddOrderPage::OnBnClickedButtonQuerycust()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szCustomerID;
	GetDlgItem(IDC_EDIT_ORDERNAME)->GetWindowText(szCustomerID);

	std::vector<CString> szCusInfo;
	BOOL bReply = CCustomerListTable::Instance()->QueryCustomerInfoByCustomerID(szCustomerID, szCusInfo);

	if (!bReply || szCusInfo.size() == 0)
	{
		AfxMessageBox("未找到客户代码！");

		return;
	}

	CString szCusName = szCusInfo[0];
	CString szPhoneNum = szCusInfo[1];
	CString szBalance = szCusInfo[4];

	CString szStore;
	for (auto iter = szCusInfo.begin(); iter != szCusInfo.end(); ++iter)
	{
		if (szCustomerID == *iter)
		{
			szStore = *(iter - 1);
		}
	}

	m_TableCustInfo.SetItemText(0, 1, szCusName);
	m_TableCustInfo.SetItemText(1, 1, szPhoneNum);
	m_TableCustInfo.SetItemText(2, 1, szStore);
	m_TableCustInfo.SetItemText(3, 1, szBalance);

	m_szCurrInfo = szCusInfo;
}

void CAddOrderPage::OnBnClickedButtonCalfare()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pEdit;
	CString str;

	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(0);
	pEdit->GetWindowText(str);
	CString szGoods = str;

	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(1);
	pEdit->GetWindowText(str);
	int nQuantity = atoi(str);

	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(2);
	pEdit->GetWindowText(str);
	double dWeight = atof(str);

	CString szLen, szWidth, szHeight;
	((CEdit*)m_pAddOrderEdits.GetAt(3))->GetWindowText(szLen);
	((CEdit*)m_pAddOrderEdits.GetAt(4))->GetWindowText(szWidth);
	((CEdit*)m_pAddOrderEdits.GetAt(5))->GetWindowText(szHeight);
	double dVolume = atof(szLen) * atof(szWidth) * atof(szHeight);

	int nPackWay = m_PackingWayCombo.GetCurSel();

	double dDensity = dWeight / dVolume;

	// Calculate Delivery Fare
	double dDeliveryFare;
	if (dDensity > CLMCommonVariable::Instance()->m_dWeightVolumeThres)
	{
		dDeliveryFare = dWeight * CLMCommonVariable::Instance()->m_dWeightPrice;
	}
	else
	{
		dDeliveryFare = dVolume * CLMCommonVariable::Instance()->m_dVolumePrice;
	}

	double dPackingFare = CalculatePackingFare();
	double dInsuranceFare = 0;
	double dTotalFare = dDeliveryFare + dPackingFare + dInsuranceFare;

	m_TableFareCtrl.SetItemText(0, 0, std::to_string(dDensity).c_str());
	m_TableFareCtrl.SetItemText(0, 1, std::to_string(dDeliveryFare).c_str());
	m_TableFareCtrl.SetItemText(0, 2, std::to_string(dPackingFare).c_str());
	m_TableFareCtrl.SetItemText(0, 3, std::to_string(dInsuranceFare).c_str());
	m_TableFareCtrl.SetItemText(0, 4, std::to_string(dTotalFare).c_str());

	UpdateWindow();
}


void CAddOrderPage::OnBnClickedButtonAddItem()
{
	// TODO: Add your control notification handler code here
	if (m_szCurrInfo.empty())
	{
		return;
	}

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	CString szDay;
	szDay.Format("%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	CEdit* pEdit;
	CString str;

	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(0);
	pEdit->GetWindowText(str);
	CString szGoods = str;

	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(1);
	pEdit->GetWindowText(str);
	int nQuantity = atoi(str);

	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(2);
	pEdit->GetWindowText(str);
	double dWeight = atof(str);

	CString szLen, szWidth, szHeight;
	((CEdit*)m_pAddOrderEdits.GetAt(3))->GetWindowText(szLen);
	((CEdit*)m_pAddOrderEdits.GetAt(4))->GetWindowText(szWidth);
	((CEdit*)m_pAddOrderEdits.GetAt(5))->GetWindowText(szHeight);
	double dVolume = atof(szLen) * atof(szWidth) * atof(szHeight);

	int nPackWay = m_PackingWayCombo.GetCurSel();
	std::wstring szPackWay = CLMCommonVariable::Instance()->m_PackingWayMap[nPackWay];

	int nPayWay = m_PayWayCombo.GetCurSel();
	std::wstring szPayWay = CLMCommonVariable::Instance()->m_PayWayMap[nPayWay];

	double dDensity = atof(m_TableFareCtrl.GetItemText(0, 0));
	double dDeliveryFare = atof(m_TableFareCtrl.GetItemText(0, 1));
	double dPackingFare = atof(m_TableFareCtrl.GetItemText(0, 2));
	double dInsuranceFare = atof(m_TableFareCtrl.GetItemText(0, 3));
	double dTotalFare = atof(m_TableFareCtrl.GetItemText(0, 4));

	str.ReleaseBuffer();

	CString szCusID;
	GetDlgItem(IDC_EDIT_ORDERNAME)->GetWindowText(szCusID);

	CString szOrderID = szDay + szCusID;

	CTime time;
	m_DateTimeRecive.GetTime(time);
	CString szDayRecive = time.Format("%Y-%m-%d");

	m_DateTimeDelivey.GetTime(time);
	CString szDayDelivey = time.Format("%Y-%m-%d");

	CString szCarrier;
	pEdit = (CEdit*)m_pAddOrderEdits.GetAt(4);
	pEdit->GetWindowText(szCarrier);
	
	std::vector<CString> szOrderDataV;
	szOrderDataV.push_back(szOrderID);
	szOrderDataV.push_back(szDayRecive);
	szOrderDataV.push_back(szDayDelivey);
	szOrderDataV.push_back(szCarrier);
	szOrderDataV.push_back(szCusID);
	szOrderDataV.push_back(szGoods);
	szOrderDataV.push_back(std::to_string(nQuantity).c_str());
	szOrderDataV.push_back(std::to_string(dVolume).c_str());
	szOrderDataV.push_back(ws2s(szPackWay).c_str());
	CString szTotalFare;
	szTotalFare.Format("%.1f", dTotalFare);
	szOrderDataV.push_back(szTotalFare);
	szOrderDataV.push_back(ws2s(szPayWay).c_str());
	szOrderDataV.push_back(m_TableCustInfo.GetItemText(2, 1));
	szOrderDataV.push_back("订单生成");

	m_TableCS.Lock();
	int nTotalItem = m_TableShowOrder.GetItemCount();
	int nRow = m_TableShowOrder.InsertItem(nTotalItem, "");
	auto iterRowData = szOrderDataV.begin();
	for (int i = 0; i < sizeof(gOrderListCol) / sizeof(gOrderListCol[0]); ++i)
	{
		m_TableShowOrder.SetItemText(nRow, i, *iterRowData);
		++iterRowData;
	}
	m_TableCS.Unlock();

	CAllOrderTable::Instance()->AddOrder(szOrderDataV);

	std::vector<CString> szAccountDataV;
	szAccountDataV.push_back(m_szCurrInfo[1]);
	szAccountDataV.push_back(szDay);
	szAccountDataV.push_back("0");
	szAccountDataV.push_back(std::to_string(dTotalFare).c_str());
	CString szBalance;
	szBalance.Format("%f", atof(m_szCurrInfo[4]) - dTotalFare);
	szAccountDataV.push_back(szBalance);
	CustomerAccountTable::Instance()->AddCustomerAccountRecord(m_szCurrInfo[1], szAccountDataV);

	CCustomerListTable::Instance()->AlterCustomerInfoItem(m_szCurrInfo[1], "Balance", szBalance);
	m_TableCustInfo.SetItemText(3, 1, szBalance);

	UpdateWindow();
}


void CAddOrderPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (bShow)
	{
		SetTimer(SYN_TIMER_ID, 5000, NULL);
	} 
	else
	{
		KillTimer(SYN_TIMER_ID);
	}

}


void CAddOrderPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);

	switch (nIDEvent)
	{
	case SYN_TIMER_ID:
	{
		UpdateDayOrderTable();
	}
	break;
	default:
		break;
	}
		

}
