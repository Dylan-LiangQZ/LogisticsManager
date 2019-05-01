// AddOrderPage.cpp : implementation file
//

#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "AddOrderPage.h"
#include "afxdialogex.h"
#include "..\LMConstant.h"
#include <fstream>

// CAddOrderPage dialog

IMPLEMENT_DYNAMIC(CAddOrderPage, CDialogEx)

CAddOrderPage::CAddOrderPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddOrderPage::IDD, pParent)
{

}

CAddOrderPage::~CAddOrderPage()
{
	for (int i = 0; i < sizeof(gszOrderTableColumnV) / sizeof(gszOrderTableColumnV[0]); i++)
	{
		CEdit* pEdit = (CEdit*)p_mAddOrderEdits.GetAt(i);
		if (pEdit != NULL)
			delete pEdit;
		p_mAddOrderEdits[i] = NULL;
	}
	p_mAddOrderEdits.RemoveAll();
}

void CAddOrderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_ADDORDER, m_TableShowCtrl);
	DDX_Control(pDX, IDC_LIST_ADDORDER0, m_TableAddCtrl);
}


BEGIN_MESSAGE_MAP(CAddOrderPage, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ADDITEM, &CAddOrderPage::OnBnClickedButtonAddItem)
	ON_BN_CLICKED(IDC_BUTTON_ADDORDER, &CAddOrderPage::OnBnClickedButtonAddorder)
END_MESSAGE_MAP()


// CAddOrderPage message handlers
BOOL CAddOrderPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//
	/*GetDlgItem(IDC_STATIC_AO1)->MoveWindow(10, 10, 100, 30);
	GetDlgItem(IDC_EDIT_ORDERNAME)->MoveWindow(100, 10, 200, 30);
	GetDlgItem(IDC_BUTTON_ADDITEM)->MoveWindow(320, 10, 200, 30);
	GetDlgItem(IDC_BUTTON_ADDORDER)->MoveWindow(520, 10, 200, 30);*/

	// Create Table
	m_TableAddCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_TableAddCtrl.MoveWindow(0, 50, (long)WINDOWWIDTH - 20, 30);

	m_TableShowCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_TableShowCtrl.MoveWindow(0, 130, (long)WINDOWWIDTH - 20, WINDOWHEIGHT - MENUHEIGHT - STATUSHEIGHT);
	
	int nColSize = sizeof(gszOrderTableColumnV) / sizeof(gszOrderTableColumnV[0]);
	for (int nColIndex = 0; nColIndex < nColSize; ++nColIndex)
	{
		m_TableShowCtrl.InsertColumn(nColIndex, gszOrderTableColumnV[nColIndex], LVCFMT_LEFT, 100);
		m_TableAddCtrl.InsertColumn(nColIndex, gszOrderTableColumnV[nColIndex], LVCFMT_LEFT, 100);
	}
	int perWidth = WINDOWWIDTH / nColSize - 4;
	int perHeight = 30;
	CEdit *p_Edit;
	for (int nColIndex = 0; nColIndex < nColSize; ++nColIndex)
	{
		p_Edit = new CEdit();
		p_Edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(2 + (perWidth + 4)*nColIndex, 80, 2 + (perWidth + 4)*nColIndex + perWidth, 75 + perHeight), this, 20001 + nColIndex);
		p_Edit->SetWindowText(gszOrderTableRawDefaultV[nColIndex]);
		p_mAddOrderEdits.Add((void*)p_Edit);
	}

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CAddOrderPage::OnPaint()
{

}


void CAddOrderPage::OnBnClickedButtonAddItem()
{
	// TODO: Add your control notification handler code here
	int nCols = (int)p_mAddOrderEdits.GetCount();

	int nRow = m_TableShowCtrl.InsertItem(0, "");
	for (int nColIndex = 0; nColIndex < nCols; ++nColIndex)
	{
		CEdit* pEdit = (CEdit*)p_mAddOrderEdits.GetAt(nColIndex);
		CString str;
		pEdit->GetWindowText(str);

		m_TableShowCtrl.SetItemText(nRow, nColIndex, str);

		str.ReleaseBuffer();
	}

	UpdateWindow();
}


void CAddOrderPage::OnBnClickedButtonAddorder()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDIT_ORDERNAME)->GetWindowText(str);

	if (str.IsEmpty())
	{
		AfxMessageBox("请输入订单名。。");

		return;
	}

	if (m_TableShowCtrl.GetItemCount() == 0)
	{
		AfxMessageBox("该订单为空， 不能创建");

		return;
	}

	SaveData();

	//AfxMessageBox("订单已创建成功。");
}


void CAddOrderPage::SaveData()
{
	CString str;
	GetDlgItem(IDC_EDIT_ORDERNAME)->GetWindowText(str);

	::CreateDirectory("OrderTable", 0);

	CString szFileName;
	szFileName.Format(".\\OrderTable\\%s.txt", str);
	std::ofstream outFile;
	outFile.open(szFileName);

	int nRows = m_TableShowCtrl.GetItemCount();
	int nCols = sizeof(gszOrderTableColumnV) / sizeof(gszOrderTableColumnV[0]);
	for (int i = 0; i < nRows;  i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			outFile << m_TableShowCtrl.GetItemText(i, j) << "\t";
		}
		outFile << std::endl;
	}
	outFile.close();
}