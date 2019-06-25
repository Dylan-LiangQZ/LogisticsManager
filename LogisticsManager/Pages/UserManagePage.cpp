// UserManagePage.cpp : implementation file
//
#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "UserManagePage.h"
#include "afxdialogex.h"
#include "..\DBTables\CustomerTable.h"
#include "..\LMCommonVariable.h"
#include <set>

// CUserManagePage dialog

static const CString gCusAccount[] =
{
	_T("日期"),
	_T("入账"),
	_T("扣款"),
	_T("账户余额"),
};

IMPLEMENT_DYNAMIC(CUserManagePage, CDialogEx)

CUserManagePage::CUserManagePage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserManagePage::IDD, pParent)
{
}

CUserManagePage::~CUserManagePage()
{
	if (m_pDesEdits.GetCount() == 4 && m_pIDEdits.GetCount() == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			CEdit* pEdit = (CEdit*)m_pDesEdits.GetAt(i);
			if (pEdit != NULL)
				delete pEdit;
			m_pDesEdits[i] = NULL;

			pEdit = (CEdit*)m_pIDEdits.GetAt(i);
			if (pEdit != NULL)
				delete pEdit;
			m_pIDEdits[i] = NULL;
		}
	}
}

void CUserManagePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DESIDLIST, m_TableDesID);
	DDX_Control(pDX, IDC_LIST_ACCOUNT, m_TableCusAccount);
}


BEGIN_MESSAGE_MAP(CUserManagePage, CDialogEx)
	ON_BN_CLICKED(IDC_EDIT_SEARCH, &CUserManagePage::OnBnClickedEditSearch)
	ON_BN_CLICKED(IDC_EDIT_NEWCUS, &CUserManagePage::OnBnClickedEditNewcus)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CUserManagePage::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUserManagePage::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CUserManagePage::OnBnClickedButtonUpload)
END_MESSAGE_MAP()


// CUserManagePage message handlers

BOOL CUserManagePage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCustomerListTable::Instance()->CreateTable();
	CustomerAccountTable::Instance()->CreateTable();

	CLMCommonVariable::Instance()->SetCusIDMap();

	CRect rectDlg;
	GetClientRect(rectDlg);

	MoveWindow(m_RectWorkingArea);

	double cx = 1.0 * m_RectWorkingArea.Width() / rectDlg.Width();
	double cy = 1.0 * m_RectWorkingArea.Height() / rectDlg.Height();

	OnResizeControl(IDC_STATIC_CUSTOMER_SRH, cx, cy);
	OnResizeControl(IDC_STATIC_CUSTOMER_INFO, cx, cy);
	OnResizeControl(IDC_STATIC_ACCOUNT_MANAGE, cx, cy);
	OnResizeControl(IDC_STATIC_NAME, cx, cy);
	OnResizeControl(IDC_EDIT_NAME, cx, cy);
	OnResizeControl(IDC_EDIT_NAME1, cx, cy);
	OnResizeControl(IDC_STATIC_huo, cx, cy);
	OnResizeControl(IDC_STATIC_huo2, cx, cy);
	OnResizeControl(IDC_EDIT_CONTACT, cx, cy);
	OnResizeControl(IDC_EDIT_CONTACT1, cx, cy);
	OnResizeControl(IDC_STATIC_CONTACT2, cx, cy);
	OnResizeControl(IDC_STATIC_CONTACT4, cx, cy);
	OnResizeControl(IDC_EDIT_CUSID, cx, cy);
	OnResizeControl(IDC_EDIT_SEARCH, cx, cy);
	OnResizeControl(IDC_EDIT_NEWCUS, cx, cy);
	OnResizeControl(IDC_STATIC_NAME3, cx, cy);
	OnResizeControl(IDC_STATIC_CONTACT3, cx, cy);
	OnResizeControl(IDC_STATIC_EMAIL, cx, cy);
	OnResizeControl(IDC_EDIT_EMAIL, cx, cy);
	OnResizeControl(IDC_STATIC_ADDRESS, cx, cy);
	OnResizeControl(IDC_EDIT_ADDRESS, cx, cy);
	OnResizeControl(IDC_BUTTON_EDIT, cx, cy);
	OnResizeControl(IDC_BUTTON_SAVE, cx, cy);
	OnResizeControl(IDC_STATIC_ACCOUNT_AMOUNT, cx, cy);
	OnResizeControl(IDC_EDIT_ACCOUNT_AMOUNT, cx, cy);
	OnResizeControl(IDC_BUTTON_UPLOAD, cx, cy);
	OnResizeControl(IDC_LIST_ACCOUNT, cx, cy);
	OnResizeControl(IDC_LIST_DESIDLIST, cx, cy);

	m_FontStatic1.CreatePointFont((int)(65 * cx), _T("宋体"));
	m_FontEdit1.CreateFont(20 * cy, 0, 0, 0, 30,
		FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Arial");

	GetDlgItem(IDC_STATIC_NAME)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_huo)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_CONTACT2)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_huo2)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_CONTACT4)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_NAME3)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_CONTACT3)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_EMAIL)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetFont(&m_FontStatic1);
	GetDlgItem(IDC_STATIC_ACCOUNT_AMOUNT)->SetFont(&m_FontStatic1);

	GetDlgItem(IDC_EDIT_NAME)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_CONTACT)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_CUSID)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_NAME1)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_CONTACT1)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_EMAIL)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_ACCOUNT_AMOUNT)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_SEARCH)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_EDIT_NEWCUS)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_BUTTON_EDIT)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_BUTTON_SAVE)->SetFont(&m_FontEdit1);
	GetDlgItem(IDC_BUTTON_UPLOAD)->SetFont(&m_FontEdit1);

	CRect rectTab1;
	m_TableDesID.SetExtendedStyle(LVS_EX_GRIDLINES);
	GetDlgItem(IDC_LIST_DESIDLIST)->GetWindowRect(&rectTab1);
	CString szDesHeader;
	for (int i = 0; i < 4; ++i)
	{
		szDesHeader.Format("目的地%d", i+1);
		m_TableDesID.InsertColumn(i, szDesHeader, LVCFMT_LEFT, rectTab1.Width() / 4 - 1, 0);
	}

	CFont   *pfont1 = m_TableDesID.GetFont();
	pfont1->GetLogFont(&m_FontList1);
	m_FontList1.lfWidth = m_FontList1.lfWidth * cx;
	m_FontList1.lfHeight = m_FontList1.lfHeight * cy;
	static   CFont   font;
	font.CreateFontIndirect(&m_FontList1);
	m_TableDesID.SetFont(&font);
	font.Detach();

	m_TableCusAccount.SetExtendedStyle(LVS_EX_GRIDLINES);
	GetDlgItem(IDC_LIST_ACCOUNT)->GetWindowRect(&rectTab1);
	
	for (int i = 0; i < sizeof(gCusAccount)/sizeof(gCusAccount[0]); ++i)
	{
		m_TableCusAccount.InsertColumn(i, gCusAccount[i], LVCFMT_LEFT, rectTab1.Width() / 4 - 1, 0);
	}

	pfont1 = m_TableCusAccount.GetFont();
	pfont1->GetLogFont(&m_FontList1);
	m_FontList1.lfWidth = m_FontList1.lfWidth * cx;
	m_FontList1.lfHeight = m_FontList1.lfHeight * cy;
	static   CFont   font1;
	font.CreateFontIndirect(&m_FontList1);
	m_TableCusAccount.SetFont(&font1);
	font1.Detach();

	GetDlgItem(IDC_EDIT_NAME1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CONTACT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserManagePage::SetWorkingArea(CRect & rect)
{
	m_RectWorkingArea = rect;
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


void CUserManagePage::OnBnClickedEditSearch()
{
	std::vector<CString> szCusInfo;

	CString szCustomerID;
	GetDlgItem(IDC_EDIT_CUSID)->GetWindowText(szCustomerID);
	CString szCustomerName;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szCustomerName);
	CString szCustomerCon;
	GetDlgItem(IDC_EDIT_CONTACT)->GetWindowText(szCustomerCon);

	BOOL bReply = FALSE;
	if (!szCustomerCon.IsEmpty())
	{
		bReply = CCustomerListTable::Instance()->QueryCustomerInfoByPhone(szCustomerCon, szCusInfo);
	} 
	else if(!szCustomerID.IsEmpty())
	{
		bReply = CCustomerListTable::Instance()->QueryCustomerInfoByCustomerID(szCustomerID, szCusInfo);
	}
	else if (!szCustomerName.IsEmpty())
	{
		bReply = CCustomerListTable::Instance()->QueryCustomerInfoByCustomerName(szCustomerName, szCusInfo);
	}	

	if (!bReply || szCusInfo.empty())
	{
		AfxMessageBox("未找到客户！");

		return;
	}

	CString szCusName = szCusInfo[0];
	CString szPhoneNum = szCusInfo[1];
	CString szEmail = szCusInfo[2];
	CString szAddress = szCusInfo[3];
	std::vector<CString> szDesV;
	szDesV.push_back(szCusInfo[5]);
	szDesV.push_back(szCusInfo[7]);
	szDesV.push_back(szCusInfo[9]);
	szDesV.push_back(szCusInfo[11]);
	std::vector<CString> szIDV;
	szIDV.push_back(szCusInfo[6]);
	szIDV.push_back(szCusInfo[8]);
	szIDV.push_back(szCusInfo[10]);
	szIDV.push_back(szCusInfo[12]);

	GetDlgItem(IDC_EDIT_NAME1)->SetWindowText(szCusName);
	GetDlgItem(IDC_EDIT_CONTACT1)->SetWindowText(szPhoneNum);
	GetDlgItem(IDC_EDIT_EMAIL)->SetWindowText(szEmail);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(szAddress);
	GetDlgItem(IDC_EDIT_NAME1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CONTACT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(FALSE);

	m_TableDesID.DeleteAllItems();
	int nRow = m_TableDesID.InsertItem(0, "");
	for (int i = 0; i < 4; ++i)
	{
		m_TableDesID.SetItemText(nRow, i, szIDV[i]);
	}

	nRow = m_TableDesID.InsertItem(0, "");
	for (int i = 0; i < 4; ++i)
	{
		m_TableDesID.SetItemText(nRow, i, szDesV[i]);
	}

	m_CurrCusInfo.clear();
	m_CurrCusInfo = szCusInfo;

	m_TableCusAccount.DeleteAllItems();
	std::vector<std::vector<CString>> szAccountV;
	CustomerAccountTable::Instance()->QueryCustomerAccountRecord(szPhoneNum, szAccountV);
	for (auto iterRow = szAccountV.begin(); iterRow != szAccountV.end(); ++iterRow)
	{
		nRow = m_TableCusAccount.InsertItem(0, "");
		auto iterRowData = (*iterRow).begin() + 1;
		for (int i = 0; iterRowData != (*iterRow).end(); ++i, ++iterRowData)
		{
			m_TableCusAccount.SetItemText(nRow, i, *iterRowData);
		}
	}

	UpdateWindow();
}


void CUserManagePage::OnBnClickedEditNewcus()
{
	CUserManageCreatePage CreateCusPage;
	CreateCusPage.DoModal();
}


void CUserManagePage::OnBnClickedButtonEdit()
{
	if (m_CurrCusInfo.empty())
	{
		return;
	}

	GetDlgItem(IDC_EDIT_NAME1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_CONTACT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_EMAIL)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_CONTACT1)->GetWindowText(m_CurrCusInfo[1]);

	m_pDesEdits.RemoveAll();
	m_pIDEdits.RemoveAll();

	CRect rectTab1;
	GetDlgItem(IDC_LIST_DESIDLIST)->GetWindowRect(&rectTab1);
	int perWidth = rectTab1.Width() / 4 - 4;
	int perHeight = rectTab1.Height() / 3 - 6;
	CEdit* p_EditDes;
	CEdit* p_EditID;
	for (int nColIndex = 0; nColIndex < 4; ++nColIndex)
	{
		p_EditDes = new CEdit();
		p_EditDes->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_DESIDLIST), 11001 + nColIndex);
		p_EditDes->MoveWindow(3 + (perWidth + 6)*nColIndex, perHeight + 5, perWidth, perHeight);
		p_EditDes->SetWindowText(m_TableDesID.GetItemText(0, nColIndex));
		m_pDesEdits.Add((void*)p_EditDes);
		p_EditDes->SetFont(&m_FontEdit1);

		p_EditID = new CEdit();
		p_EditID->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(0, 0, 0, 0), GetDlgItem(IDC_LIST_DESIDLIST), 11001 + nColIndex);
		p_EditID->MoveWindow(3 + (perWidth + 6)*nColIndex, 2*perHeight + 10, perWidth, perHeight);
		p_EditID->SetWindowText(m_TableDesID.GetItemText(1, nColIndex));
		m_pIDEdits.Add((void*)p_EditID);
		p_EditID->SetFont(&m_FontEdit1);
	}

	m_TableDesID.DeleteAllItems();

	UpdateWindow();
}


void CUserManagePage::OnBnClickedButtonSave()
{
	if (m_pDesEdits.GetCount() == 0 || m_pIDEdits.GetCount() == 0)
	{
		return;
	}

	std::set<CString> currIDSet;
	for (int i = 6; i <= 12;)
	{
		if (!m_CurrCusInfo[i].IsEmpty())
		{
			currIDSet.insert(m_CurrCusInfo[i]);
		}
		
		i += 2;
	}

	GetDlgItem(IDC_EDIT_NAME1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CONTACT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(FALSE);

	CString szNewPhone;
	GetDlgItem(IDC_EDIT_CONTACT1)->GetWindowText(szNewPhone);

	// change new phone number, check if exists.
	std::vector<CString> szCusInfo;
	CCustomerListTable::Instance()->QueryCustomerInfoByPhone(szNewPhone, szCusInfo);
	if (szNewPhone != m_CurrCusInfo[1])
	{
		if (!szCusInfo.empty())
		{
			AfxMessageBox("新的电话已存在！修改失败。");
		}
	}
	
	CString szNewName;
	GetDlgItem(IDC_EDIT_NAME1)->GetWindowText(szNewName);
	CString szNewMail;
	GetDlgItem(IDC_EDIT_EMAIL)->GetWindowText(szNewMail);
	CString szNewAdd;
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(szNewAdd);

	CString strDes1, strDes2, strDes3, strDes4;
	((CEdit*)m_pDesEdits.GetAt(0))->GetWindowText(strDes1);
	((CEdit*)m_pDesEdits.GetAt(1))->GetWindowText(strDes2);
	((CEdit*)m_pDesEdits.GetAt(2))->GetWindowText(strDes3);
	((CEdit*)m_pDesEdits.GetAt(3))->GetWindowText(strDes4);

	std::set<CString> NewIDSet;
	CString strID1, strID2, strID3, strID4;
	((CEdit*)m_pIDEdits.GetAt(0))->GetWindowText(strID1);
	if (!strID1.IsEmpty() && !CLMCommonVariable::Instance()->CheckCusIDMap(strID1, szNewPhone)
		&& currIDSet.find(strID1) == currIDSet.end())
	{
		AfxMessageBox("客户ID_1 已存在，请重新输入！");
		return;
	}
	NewIDSet.insert(strID1);

	((CEdit*)m_pIDEdits.GetAt(1))->GetWindowText(strID2);
	if (!strID2.IsEmpty() && ((!CLMCommonVariable::Instance()->CheckCusIDMap(strID2, szNewPhone)
		&& currIDSet.find(strID2) == currIDSet.end()) || NewIDSet.find(strID2) != NewIDSet.end()))
	{
		AfxMessageBox("客户ID_2 已存在，请重新输入！");
		return;
	}
	NewIDSet.insert(strID2);

	((CEdit*)m_pIDEdits.GetAt(2))->GetWindowText(strID3);
	if (!strID3.IsEmpty() && ((!CLMCommonVariable::Instance()->CheckCusIDMap(strID3, szNewPhone)
		&& currIDSet.find(strID3) == currIDSet.end()) || NewIDSet.find(strID3) != NewIDSet.end()))
	{
		AfxMessageBox("客户ID_3 已存在，请重新输入！");
		return;
	}
	NewIDSet.insert(strID3);

	((CEdit*)m_pIDEdits.GetAt(3))->GetWindowText(strID4);
	if (!strID4.IsEmpty() && ((!CLMCommonVariable::Instance()->CheckCusIDMap(strID4, szNewPhone)
		&& currIDSet.find(strID4) == currIDSet.end()) || NewIDSet.find(strID4) != NewIDSet.end()))
	{
		AfxMessageBox("客户ID_4 已存在，请重新输入！");
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		CEdit* pEdit = (CEdit*)m_pDesEdits.GetAt(i);
		if (pEdit != NULL)
			delete pEdit;
		m_pDesEdits[i] = NULL;

		pEdit = (CEdit*)m_pIDEdits.GetAt(i);
		if (pEdit != NULL)
			delete pEdit;
		m_pIDEdits[i] = NULL;
	}

	int nRow = m_TableDesID.InsertItem(0, "");
	m_TableDesID.SetItemText(nRow, 0, strID1);
	m_TableDesID.SetItemText(nRow, 1, strID2);
	m_TableDesID.SetItemText(nRow, 2, strID3);
	m_TableDesID.SetItemText(nRow, 3, strID4);

	nRow = m_TableDesID.InsertItem(0, "");
	m_TableDesID.SetItemText(nRow, 0, strDes1);
	m_TableDesID.SetItemText(nRow, 1, strDes2);
	m_TableDesID.SetItemText(nRow, 2, strDes3);
	m_TableDesID.SetItemText(nRow, 3, strDes4);

	CCustomerListTable::Instance()->QueryCustomerInfoByPhone(m_CurrCusInfo[1],szCusInfo);

	std::vector<CString> szCustomerInfoV;
	szCustomerInfoV.push_back(szNewName);
	szCustomerInfoV.push_back(szNewPhone);
	szCustomerInfoV.push_back(szNewMail);
	szCustomerInfoV.push_back(szNewAdd);
	szCustomerInfoV.push_back(szCusInfo[4]);
	szCustomerInfoV.push_back(strDes1);
	szCustomerInfoV.push_back(strID1);
	szCustomerInfoV.push_back(strDes2);
	szCustomerInfoV.push_back(strID2);
	szCustomerInfoV.push_back(strDes3);
	szCustomerInfoV.push_back(strID3);
	szCustomerInfoV.push_back(strDes4);
	szCustomerInfoV.push_back(strID4);
	CCustomerListTable::Instance()->AlterCustomerInfoByQueryPhone(szNewPhone, szCustomerInfoV);
}


void CUserManagePage::OnBnClickedButtonUpload()
{
	CString szPhone;
	GetDlgItem(IDC_EDIT_CONTACT1)->GetWindowText(szPhone);

	if (szPhone.IsEmpty())
	{
		AfxMessageBox("请先查找客户。");
		return;
	}

	CString szAmount;
	GetDlgItem(IDC_EDIT_ACCOUNT_AMOUNT)->GetWindowText(szAmount);
	if (szAmount.IsEmpty() || atoi(szAmount) <= 0)
	{
		AfxMessageBox("请输入正确金额。");
		return;
	}

	CString szNewPhone;
	GetDlgItem(IDC_EDIT_CONTACT1)->GetWindowText(szNewPhone);

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	CString szDay;
	szDay.Format("%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	std::vector<CString> szAccountDataV;
	szAccountDataV.push_back(szNewPhone);
	szAccountDataV.push_back(szDay);
	szAccountDataV.push_back(szAmount);
	szAccountDataV.push_back("0");
	CString szBalance;
	szBalance.Format("%d", atoi(m_CurrCusInfo[4]) + atoi(szAmount));
	szAccountDataV.push_back(szBalance);
	CustomerAccountTable::Instance()->AddCustomerAccountRecord(szPhone, szAccountDataV);

	int nRow = m_TableCusAccount.InsertItem(0, "");
	auto iterRowData = szAccountDataV.begin() + 1;
	for (int i = 0; iterRowData != szAccountDataV.end(); ++i, ++iterRowData)
	{
		m_TableCusAccount.SetItemText(nRow, i, *iterRowData);
	}

	CCustomerListTable::Instance()->AlterCustomerInfoItem(szPhone, "Balance", szBalance);
}
