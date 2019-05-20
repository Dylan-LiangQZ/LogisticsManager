
// LogisticsManagerDlg.h : 头文件
//

#include <map>

#include "Pages\UserManagePage.h"
#include "Pages\AddOrderPage.h"
#include "Pages\QueryOrderPage.h"
#include "Pages\SummaryPage.h"

#pragma once

class CLogisticsManagerDlgAutoProxy;


// CLogisticsManagerDlg 对话框
class CLogisticsManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogisticsManagerDlg);
	friend class CLogisticsManagerDlgAutoProxy;

// 构造
public:
	CLogisticsManagerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CLogisticsManagerDlg();

// 对话框数据
	enum { IDD = IDD_LOGISTICSMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CLogisticsManagerDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	WINDOWPLACEMENT			m_struOldWndpl;
	CMenu m_Menu;

	std::map<int, CDialogEx*>	m_PagesMap;
	CUserManagePage*		m_pUserManagePage;
	CAddOrderPage*			m_pAddOrderPage;
	CQueryOrderPage*		m_pQueryOrderPage;
	CSummaryPage*			m_pCSummaryPage;

	CImageList	m_Imagelist;
	CStatusBar	m_Statusbar;
	CToolBar	m_Toolbar;

	CString		m_szDataBaseName;
	int			m_nUserType;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();

	// User define function
	void LoadParameters();
	void InitializeConfig();

	afx_msg void OnMENUlogin();
	afx_msg void OnBUTTONUser();
	afx_msg void OnBUTTONAddOrder();
	afx_msg void OnBUTTONQueryOrder();
	afx_msg void OnBUTTONSummary();

	DECLARE_MESSAGE_MAP()

public:
};
