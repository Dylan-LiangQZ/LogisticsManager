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
