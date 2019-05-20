
// LogisticsManagerDlg.h : ͷ�ļ�
//

#include <map>

#include "Pages\UserManagePage.h"
#include "Pages\AddOrderPage.h"
#include "Pages\QueryOrderPage.h"
#include "Pages\SummaryPage.h"

#pragma once

class CLogisticsManagerDlgAutoProxy;


// CLogisticsManagerDlg �Ի���
class CLogisticsManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogisticsManagerDlg);
	friend class CLogisticsManagerDlgAutoProxy;

// ����
public:
	CLogisticsManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CLogisticsManagerDlg();

// �Ի�������
	enum { IDD = IDD_LOGISTICSMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
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

	// ���ɵ���Ϣӳ�亯��
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
