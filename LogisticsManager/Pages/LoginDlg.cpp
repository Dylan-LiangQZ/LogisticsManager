// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_szUname = _T("");
	m_szUpasswd = _T("");
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_szUname);
	DDX_Text(pDX, IDC_EDIT_USERPASSWORD, m_szUpasswd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(ID_ON_LOGIN, &CLoginDlg::OnBnClickedOnLogin)
	ON_BN_CLICKED(ID_ON_CANCELLOGIN, &CLoginDlg::OnBnClickedOnCancellogin)
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnBnClickedOnLogin()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!m_szUname.IsEmpty() && !m_szUpasswd.IsEmpty() || true)
	{
		if (m_szUname == "zeyu" && m_szUpasswd == "zeyu")
		{
			CDialog::OnOK();
			return;
		}
		else
		{
			AfxMessageBox("用户名/密码 错误！");
			CDialog::OnCancel();
			return;
		}
	}
	else
	{
		AfxMessageBox("用户名密码不能为空");
		CDialog::OnCancel();
		return;
	}
}


void CLoginDlg::OnBnClickedOnCancellogin()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
