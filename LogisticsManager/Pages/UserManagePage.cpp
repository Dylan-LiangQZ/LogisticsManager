// UserManagePage.cpp : implementation file
//
#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "UserManagePage.h"
#include "afxdialogex.h"
#include "..\DBTables\CustomerTable.h"

// CUserManagePage dialog

IMPLEMENT_DYNAMIC(CUserManagePage, CDialogEx)

CUserManagePage::CUserManagePage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserManagePage::IDD, pParent)
{

}

CUserManagePage::~CUserManagePage()
{
}

void CUserManagePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CUserManagePage, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CUserManagePage::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CUserManagePage message handlers

BOOL CUserManagePage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCustomerListTable::Instance()->CreateTable();
	CustomerAccountTable::Instance()->CreateTable();

	std::vector<CString> szV;
	szV.push_back("12345");
	szV.push_back("2019-06-02");
	szV.push_back("+1000");
	szV.push_back("0");
	szV.push_back("1000");
	CustomerAccountTable::Instance()->AddCustomerAccountRecord("12345", szV);

	CRect rectDlg;
	GetClientRect(rectDlg);

	MoveWindow(m_RectWorkingArea);

	double cx = 1.0 * m_RectWorkingArea.Width() / rectDlg.Width();
	double cy = 1.0 * m_RectWorkingArea.Height() / rectDlg.Height();
	OnResizeControl(IDC_TAB1, cx, cy);

	//为Tab Control增加两个页面
	m_tab.InsertItem(0,"创建");
	m_tab.InsertItem(1,"查询与修改");

	//创建两个对话框
	m_tab_edit.SetWorkingArea(m_RectWorkingArea);
	m_tab_create.Create(IDD_DIALOG_USERMANAGE_CREATE, &m_tab);
	m_tab_edit.Create(IDD_DIALOG_USERMANAGE_EDIT, &m_tab);
	
	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_tab_create.MoveWindow(&rc);
	m_tab_edit.MoveWindow(&rc);

	//把对话框对象指针保存起来

	pDialog[0] = &m_tab_create;
	pDialog[1] = &m_tab_edit;
	
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	
	//保存当前选择
	m_CurSelTab = 0;


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CUserManagePage::SetWorkingArea(CRect & rect)
{
	m_RectWorkingArea = rect;
}


void CUserManagePage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 
}


void CUserManagePage::OnResizeControl(int CtrlID, double cx, double cy)
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

HBRUSH CUserManagePage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
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


void CUserManagePage::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: 在此添加控件通知处理程序代码

	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tab.GetCurSel();
	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}
