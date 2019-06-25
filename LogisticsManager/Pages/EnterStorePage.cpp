// EnterStorePage.cpp : 实现文件
//

#include "..\stdafx.h"
#include "..\LogisticsManager.h"
#include "EnterStorePage.h"
#include "afxdialogex.h"
#include "..\DBTables\EnterGoodsTable.h"
#include "..\LMCommonVariable.h"

// CEnterStorePage 对话框

IMPLEMENT_DYNAMIC(CEnterStorePage, CDialogEx)

CEnterStorePage::CEnterStorePage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ENTERSTORE, pParent)
{

}

CEnterStorePage::~CEnterStorePage()
{
}

void CEnterStorePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_E, m_TableEnterGoods);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_DateTimeQuery);
}


BEGIN_MESSAGE_MAP(CEnterStorePage, CDialogEx)
	ON_BN_CLICKED(ID_E_ENTER, &CEnterStorePage::OnBnClickedEEnter)
	ON_BN_CLICKED(ID_E_QUERY, &CEnterStorePage::OnBnClickedEQuery)
END_MESSAGE_MAP()


// CEnterStorePage 消息处理程序
BOOL CEnterStorePage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CEnterGoodsTable::Instance()->CreateTable();

	// 控件布局设计
	CRect rectDlg;
	GetClientRect(rectDlg);

	MoveWindow(m_RectWorkingArea);

	double cx = 1.0 * m_RectWorkingArea.Width() / rectDlg.Width();
	double cy = 1.0 * m_RectWorkingArea.Height() / rectDlg.Height();

	OnResizeControl(IDC_STATIC_E1, cx, cy);
	OnResizeControl(IDC_STATIC_E2, cx, cy);
	OnResizeControl(IDC_STATIC_E3, cx, cy);
	OnResizeControl(IDC_STATIC_E4, cx, cy);
	OnResizeControl(IDC_STATIC_E5, cx, cy);
	OnResizeControl(IDC_STATIC_E6, cx, cy);
	OnResizeControl(IDC_STATIC_E7, cx, cy);
	OnResizeControl(IDC_STATIC_E8, cx, cy);
	OnResizeControl(IDC_EDIT_E_CUSID, cx, cy);
	OnResizeControl(IDC_EDIT_E_GOODS, cx, cy);
	OnResizeControl(IDC_EDIT_E_NUMBER, cx, cy);
	OnResizeControl(IDC_EDIT_E_HONGHUO, cx, cy);
	OnResizeControl(IDC_EDIT_E_PHONE, cx, cy);
	OnResizeControl(IDC_EDIT_E_CUSID2, cx, cy);
	OnResizeControl(IDC_EDIT_E_HONGHUO2, cx, cy);
	OnResizeControl(IDC_DATETIMEPICKER3, cx, cy);
	OnResizeControl(ID_E_ENTER, cx, cy);
	OnResizeControl(ID_E_QUERY, cx, cy);
	OnResizeControl(IDC_LIST_E, cx, cy);
	OnResizeControl(IDC_STATIC_GE1, cx, cy);
	OnResizeControl(IDC_STATIC_GE2, cx, cy);

	m_FontStatic1.CreatePointFont((int)(65 * cx), _T("宋体"));
	m_FontEdit1.CreateFont(20 * cy, 0, 0, 0, 30,
		FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Arial");

	GetDlgItem(IDC_STATIC_E1)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E2)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E3)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E4)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E5)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E6)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E7)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_E8)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_EDIT_E_CUSID)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_E_GOODS)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_E_NUMBER)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_E_HONGHUO)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_E_PHONE)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_E_HONGHUO2)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_E_CUSID2)->SetFont(&m_FontEdit1);
	GetDlgItem(ID_E_ENTER)->SetFont(&m_FontStatic1);
	GetDlgItem(ID_E_QUERY)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_DATETIMEPICKER3)->SetFont(&m_FontStatic1);

	// Create Table
	m_TableEnterGoods.SetExtendedStyle(LVS_EX_GRIDLINES);
	CRect rectTab1;
	GetDlgItem(IDC_LIST_E)->GetWindowRect(&rectTab1);

	const int COLSIZE = sizeof(gEnterGoodsCol) / sizeof(gEnterGoodsCol[0]);
	for (int i = 0; i < COLSIZE; ++i)
	{
		m_TableEnterGoods.InsertColumn(i, gEnterGoodsCol[i], LVCFMT_LEFT, rectTab1.Width() / COLSIZE, 0);
	}

	CFont   *pfont1 = m_TableEnterGoods.GetFont();
	pfont1->GetLogFont(&m_FontList1);
	m_FontList1.lfWidth = m_FontList1.lfWidth * cx;
	m_FontList1.lfHeight = m_FontList1.lfHeight * cy;
	static   CFont   font1;
	font1.CreateFontIndirect(&m_FontList1);
	m_TableEnterGoods.SetFont(&font1);
	font1.Detach();

	COleDateTime oletimeTime = COleDateTime::GetCurrentTime();
	oletimeTime.SetStatus(COleDateTime::null);
	m_DateTimeQuery.SetTime(oletimeTime);

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CEnterStorePage::OnResizeControl(int CtrlID, double cx, double cy)
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


void CEnterStorePage::SetWorkingArea(CRect & rect)
{
	m_RectWorkingArea = rect;
}


void CEnterStorePage::OnBnClickedEEnter()
{
	CString szCustomerID, szGoodsName, szNumber, szSuppler, szPhone;
	GetDlgItem(IDC_EDIT_E_CUSID)->GetWindowText(szCustomerID);
	GetDlgItem(IDC_EDIT_E_GOODS)->GetWindowText(szGoodsName);
	GetDlgItem(IDC_EDIT_E_NUMBER)->GetWindowText(szNumber);
	GetDlgItem(IDC_EDIT_E_HONGHUO)->GetWindowText(szSuppler);
	GetDlgItem(IDC_EDIT_E_PHONE)->GetWindowText(szPhone);

	if (CLMCommonVariable::Instance()->m_CusIDnPhoneMap.find(szCustomerID) == 
		CLMCommonVariable::Instance()->m_CusIDnPhoneMap.end())
	{
		AfxMessageBox("客户代码不存在，请重新输入！");
		return;
	}
	
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	CString szDay;
	szDay.Format("%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	std::vector<CString> szEnterGoodsInfoV;
	szEnterGoodsInfoV.push_back(szDay);
	szEnterGoodsInfoV.push_back(szCustomerID);
	szEnterGoodsInfoV.push_back(szGoodsName);
	szEnterGoodsInfoV.push_back(szNumber);
	szEnterGoodsInfoV.push_back(szSuppler);
	szEnterGoodsInfoV.push_back(szPhone);
	CEnterGoodsTable::Instance()->AddEnterGoodsInfo(szEnterGoodsInfoV);

	int nTotalItem = m_TableEnterGoods.GetItemCount();
	int nRow = m_TableEnterGoods.InsertItem(nTotalItem, "");
	auto iterRowData = szEnterGoodsInfoV.begin();
	for (int i = 0; i < sizeof(gEnterGoodsCol) / sizeof(gEnterGoodsCol[0]); ++i)
	{
		m_TableEnterGoods.SetItemText(nRow, i, *iterRowData);
		++iterRowData;
	}

	UpdateWindow();
}


void CEnterStorePage::OnBnClickedEQuery()
{
	CString szCustomerID, szSuppler;
	GetDlgItem(IDC_EDIT_E_CUSID2)->GetWindowText(szCustomerID);
	GetDlgItem(IDC_EDIT_E_HONGHUO2)->GetWindowText(szSuppler);

	CString szDayQuery = "";
	CTime time;
	DWORD dwResult = m_DateTimeQuery.GetTime(time);
	if (dwResult == GDT_VALID)
	{
		szDayQuery = time.Format("%Y-%m-%d");
	}
	
	std::vector<std::vector<CString>> szEnterGoodsInfoVV;
	BOOL bReply = CEnterGoodsTable::Instance()->QueryEnterGoodsByCustomerID(szCustomerID,
		szSuppler, szDayQuery, szEnterGoodsInfoVV);
	if (!bReply || szEnterGoodsInfoVV.empty())
	{
		AfxMessageBox("未找到入库单信息。");
		return;
	}

	m_TableEnterGoods.DeleteAllItems();

	auto iterRow = szEnterGoodsInfoVV.begin();
	for (; iterRow != szEnterGoodsInfoVV.end(); ++iterRow)
	{
		int nRow = m_TableEnterGoods.InsertItem(0, "");
		auto iterRowData = (*iterRow).begin();
		for (int i = 0; i < (*iterRow).size(); ++i, ++iterRowData)
		{
			m_TableEnterGoods.SetItemText(nRow, i, *iterRowData);
		}
	}
}
