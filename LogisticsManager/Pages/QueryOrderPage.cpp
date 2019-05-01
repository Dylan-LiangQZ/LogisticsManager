// QueryOrder.cpp : implementation file
//

#include "stdafx.h"
#include "..\LogisticsManager.h"
#include "QueryOrderPage.h"
#include "afxdialogex.h"
#include <io.h>  

#include "..\LMConstant.h"
#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>
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
	DDX_Control(pDX, IDC_COMBO_ORDER, m_AllOrderCombo);
}


BEGIN_MESSAGE_MAP(CQueryOrderPage, CDialogEx)
	
	ON_BN_CLICKED(ID_QueryOrder, &CQueryOrderPage::OnBnClickedQueryorder)
END_MESSAGE_MAP()


// CQueryOrderPage message handlers
BOOL CQueryOrderPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_szFileNameSet.clear();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	GetDlgItem(IDC_COMBO_ORDER)->MoveWindow(10, 10, 200, 50);
	GetDlgItem(ID_QueryOrder)->MoveWindow(230, 10, 200, 30);
	m_AllOrderCombo.SetWindowPos(NULL, 0, 0, 200, 200, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);

	m_TableShowCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_TableShowCtrl.MoveWindow(0, 60, (long)WINDOWWIDTH - 20, WINDOWHEIGHT - MENUHEIGHT - STATUSHEIGHT);

	int nColSize = sizeof(gszOrderTableColumnV) / sizeof(gszOrderTableColumnV[0]);
	for (int nColIndex = 0; nColIndex < nColSize; ++nColIndex)
	{
		m_TableShowCtrl.InsertColumn(nColIndex, gszOrderTableColumnV[nColIndex], LVCFMT_LEFT, 100);
	}

	AddOrderList();

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


void CQueryOrderPage::AddOrderList()
{
	std::vector<std::string> szFileNameV;
	std::string  szpath = ".\\OrderTable";
	GetFiles(szpath, szFileNameV);

	for (auto iter = szFileNameV.begin(); iter != szFileNameV.end(); ++iter)
	{
		if (m_szFileNameSet.find((*iter).c_str()) == m_szFileNameSet.end())
		{
			CString szFile = (*iter).c_str();
			szFile = szFile.Left((*iter).length() - 4);
			m_AllOrderCombo.AddString(szFile);
			m_szFileNameSet.insert((*iter).c_str());
		}	
	}

	m_AllOrderCombo.SetCurSel(0);
}


void CQueryOrderPage::OnBnClickedQueryorder()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_AllOrderCombo.GetLBText(m_AllOrderCombo.GetCurSel(), str);

	CString szFilePath = ".\\OrderTable\\" + str + ".txt";

	bool bFileExist = true;
	WIN32_FIND_DATA FindData;
	HANDLE FILEHANDE = ::FindFirstFile(szFilePath, &FindData);
	if (FILEHANDE == INVALID_HANDLE_VALUE)
	{
		bFileExist = false;
	}
	::FindClose(FILEHANDE);
	if (!bFileExist)
	{
		return;
	}
	m_TableShowCtrl.DeleteAllItems();
	std::ifstream infile(szFilePath, std::ios_base::in);
	std::string s = "";
	while (!infile.eof())
	{
		getline(infile, s);
		if (s == "")
		{
			continue;
		}

		stringstream stringin(s);

		int nRow = m_TableShowCtrl.InsertItem(0, "");
		int nColSize = sizeof(gszOrderTableColumnV) / sizeof(gszOrderTableColumnV[0]);
		for (int nColIndex = 0; nColIndex < nColSize; ++nColIndex)
		{
			std::string szValue;
			stringin >> szValue;
			m_TableShowCtrl.SetItemText(nRow, nColIndex, szValue.c_str());
		}
	}
	infile.close();
}
