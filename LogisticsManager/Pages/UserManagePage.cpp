// UserManagePage.cpp : implementation file
//
#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "UserManagePage.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CUserManagePage, CDialogEx)
END_MESSAGE_MAP()


// CUserManagePage message handlers
