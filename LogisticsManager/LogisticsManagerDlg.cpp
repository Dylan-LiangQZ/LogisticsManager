
// LogisticsManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LogisticsManager.h"
#include "LogisticsManagerDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <crtdbg.h>
#include "Wininet.h"

#include "pages\LoginDlg.h"

#include "Tinyxml\XMLFile.h"
#include "DataBase\DBConn.h"
#include "LMCommonVariable.h"

const static int TOOLBARHEIGHT = 80;
const static int STATUSBARHEIGHT = 60;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLogisticsManagerDlg �Ի���


IMPLEMENT_DYNAMIC(CLogisticsManagerDlg, CDialogEx);

CLogisticsManagerDlg::CLogisticsManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogisticsManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	m_BgExitHD = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

CLogisticsManagerDlg::~CLogisticsManagerDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;

	::SetEvent(m_BgExitHD);

	m_PagesMap.clear();

	delete m_pUserManagePage;
	m_pUserManagePage = NULL;
	delete m_pAddOrderPage;
	m_pAddOrderPage = NULL;
	delete m_pQueryOrderPage;
	m_pQueryOrderPage = NULL;
	delete m_pCSummaryPage;
	m_pCSummaryPage = NULL;
	delete m_pEnterStorePage;
	m_pEnterStorePage = NULL;

	Sleep(1000);

	_CrtDumpMemoryLeaks();

	::CloseHandle(m_BgExitHD);
}

void CLogisticsManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

#define WM_INTERNETSTATUS_CHANGE WM_USER + 1
#define WM_DATABASESTATUS_CHANGE WM_USER + 2

BEGIN_MESSAGE_MAP(CLogisticsManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_LOGIN, OnMENUlogin)
	ON_COMMAND(IDB_ON_USER, OnBUTTONUser)
	ON_COMMAND(IDB_ON_GOODS, OnBUTTONGOODS)
	ON_COMMAND(IDB_ON_ADDORDER, OnBUTTONAddOrder)
	ON_COMMAND(IDB_ON_QUERYORDER, OnBUTTONQueryOrder)
	ON_COMMAND(IDB_ON_SUMMMERY, OnBUTTONSummary)
	ON_MESSAGE(WM_INTERNETSTATUS_CHANGE, InternetStatusChanged)
	ON_MESSAGE(WM_DATABASESTATUS_CHANGE, DatabaseStatusChanged)
END_MESSAGE_MAP()

enum StatusBarItem
{
	PROJECTNAME = 0,
	INTERNETSTATUS = 1,
	DATABASESTATUS = 2,
	USERNAME = 3,
	CURRENTTIME = 4,

	MAX_STATUSBARITEM
};

// CLogisticsManagerDlg ��Ϣ�������

BOOL CLogisticsManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)), TRUE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	LoadParameters();

	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	// Full Screen
	int nCurScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	CRect rectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rectWorkArea, 0);
	MoveWindow(0, 0, nCurScreenWidth, rectWorkArea.bottom);

	// ����״̬�� /////////////////////////////////////////////////////////
	CTime Time;
	Time = CTime::GetCurrentTime();
	CString Str = Time.Format("%Y-%m-%d");

	UINT Array[MAX_STATUSBARITEM];
	for (int i = 0; i < MAX_STATUSBARITEM; i++)
	{
		Array[i] = 10000 + i;
	}
	m_Statusbar.Create(this);
	m_Statusbar.SetIndicators(Array, MAX_STATUSBARITEM);
	m_Statusbar.SetPaneInfo(0, Array[0], 0, nCurScreenWidth*0.2);
	m_Statusbar.SetPaneInfo(1, Array[1], 0, nCurScreenWidth*0.2);
	m_Statusbar.SetPaneInfo(2, Array[2], 0, nCurScreenWidth*0.2);
	m_Statusbar.SetPaneInfo(3, Array[3], 0, nCurScreenWidth*0.2);
	m_Statusbar.SetPaneInfo(4, Array[4], 0, nCurScreenWidth*0.2);
	m_Statusbar.SetPaneText(0, "  ������������ϵͳ ");
	m_Statusbar.SetPaneText(1, "  ������״̬��δ����");
	m_Statusbar.SetPaneText(2, "  ���ݿ�״̬: δ����");
	m_Statusbar.SetPaneText(3, "  �û��� δ��½");
	m_Statusbar.SetPaneText(4, "  ��ǰʱ�� : " + Str);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	// Init DataBase
	BOOL bReply = CDBConn::Instance()->InitDataBase();
	bReply = CDBConn::Instance()->ConnectDataBase(m_szDataBaseName);
	_beginthreadex(NULL, 0, StatusCheckThread, this, 0, NULL);

	InitializeConfig();

	// Add pages
	CRect rectStatusBar;
	m_Statusbar.GetClientRect(rectStatusBar);
	CRect rectMenuBar;
	m_Toolbar.GetClientRect(rectMenuBar);
	CRect rectDlg;
	GetClientRect(rectDlg);
	
	m_PagesMap.clear();
	m_pUserManagePage = new CUserManagePage;
	m_pUserManagePage->SetWorkingArea(CRect(0, rectMenuBar.Height(), rectDlg.Width(), rectDlg.Height() - rectStatusBar.Height()));
	m_pUserManagePage->Create(IDD_DIALOG_USERMANAGE, this);

	m_pAddOrderPage = new CAddOrderPage;
	m_pAddOrderPage->SetWorkingArea(CRect(0, rectMenuBar.Height(), rectDlg.Width(), rectDlg.Height() - rectStatusBar.Height()));
	m_pAddOrderPage->Create(IDD_DIALOG_ADDORDER, this);

	m_pQueryOrderPage = new CQueryOrderPage;
	m_pQueryOrderPage->SetWorkingArea(CRect(0, rectMenuBar.Height(), rectDlg.Width(), rectDlg.Height() - rectStatusBar.Height()));
	m_pQueryOrderPage->Create(IDD_DIALOG_QUERYORDER, this);

	m_pCSummaryPage = new CSummaryPage;
	//m_pCSummaryPage->SetWorkingArea(CRect(0, rectMenuBar.Height(), rectDlg.Width(), rectDlg.Height() - rectStatusBar.Height()));
	m_pCSummaryPage->Create(IDD_DIALOG_SUMMARY, this);

	m_pEnterStorePage = new CEnterStorePage;
	m_pEnterStorePage->SetWorkingArea(CRect(0, rectMenuBar.Height(), rectDlg.Width(), rectDlg.Height() - rectStatusBar.Height()));
	m_pEnterStorePage->Create(IDD_DIALOG_ENTERSTORE, this);

	m_PagesMap.insert(std::make_pair(0, m_pUserManagePage));
	m_PagesMap.insert(std::make_pair(1, m_pEnterStorePage));
	m_PagesMap.insert(std::make_pair(2, m_pAddOrderPage));
	m_PagesMap.insert(std::make_pair(3, m_pQueryOrderPage));
	m_PagesMap.insert(std::make_pair(4, m_pCSummaryPage));


	// �Ի��� /////////////////////////////////////////////////////////////
	//CLoginDlg Logindlg;
	//if (Logindlg.DoModal() == IDOK)
	{
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_USER, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_GOODS, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_ADDORDER, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_QUERYORDER, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_SUMMMERY, true);

		m_Statusbar.SetPaneText(USERNAME, "�û���zeyu");
	}
	//else
	{

	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLogisticsManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLogisticsManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	for (auto iter = m_PagesMap.begin(); iter != m_PagesMap.end(); ++iter)
	{
		//(*iter).second->MoveWindow(0, 80, WINDOWWIDTH, WINDOWHEIGHT - MENUHEIGHT - STATUSHEIGHT - 30);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLogisticsManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CLogisticsManagerDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CLogisticsManagerDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CLogisticsManagerDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CLogisticsManagerDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CLogisticsManagerDlg::LoadParameters()
{
	CString szSystemFile;
	szSystemFile.Format(_T("Config\\System.xml"));
	CXMLFile  xmlFileSystem(CString("System"));
	xmlFileSystem.Load(szSystemFile);

	CXMLElementHandle rootHandle(xmlFileSystem.Root());

	rootHandle.GetInt("UserType", m_nUserType);
	rootHandle.GetStr("DataBaseName", m_szDataBaseName);

	CXMLElementHandle ElementHandle1(rootHandle.FirstChild("PackingWay").ToElement());
	CLMCommonVariable::Instance()->LoadPackingWay(ElementHandle1);

	CXMLElementHandle ElementHandle2(rootHandle.FirstChild("PayWay").ToElement());
	CLMCommonVariable::Instance()->LoadPayWay(ElementHandle2);

	CXMLElementHandle ElementHandle3(rootHandle.FirstChild("DeliveryFare").ToElement());
	CLMCommonVariable::Instance()->LoadDeliveyFare(ElementHandle3);
}


void CLogisticsManagerDlg::InitializeConfig()
{	
	// �����˵�
	switch (m_nUserType)
	{
	case 0:	// All Pages
	{	
		m_Imagelist.DeleteImageList();
		m_Imagelist.Create(50, 40, ILC_COLOR24 | ILC_MASK, 1, 1);
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_USER));
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_Goods));
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_ADD));
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_QUERY));
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_SUM));

		const int nMenuMember = 5;
		UINT Array[nMenuMember];
		for (int i = 0; i < nMenuMember; i++)
		{
			Array[i] = 9000 + i;
		}

		m_Toolbar.Create(this);
		m_Toolbar.SetButtons(Array, nMenuMember);
		m_Toolbar.SetButtonText(0, "�ͻ�����");
		m_Toolbar.SetButtonText(1, "���Ǽ�");
		m_Toolbar.SetButtonText(2, "��������");
		m_Toolbar.SetButtonText(3, "������ѯ");
		m_Toolbar.SetButtonText(4, "ͳ�ƽ���");
		m_Toolbar.GetToolBarCtrl().SetButtonWidth(60, 120);
		m_Toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist);
		m_Toolbar.SetSizes(CSize(100, TOOLBARHEIGHT), CSize(50, 40));
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_USER, false);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_GOODS, false);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_ADDORDER, false);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_QUERYORDER, false);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_SUMMMERY, false);
	}
	break;
	case 1:	// Logistics manager
	{

	}
	break;
	case 2:	// Logistics operator
	{
		m_Imagelist.Create(50, 40, ILC_COLOR24 | ILC_MASK, 1, 1);
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_ADD));

		const int nMenuMember = 1;
		UINT Array[nMenuMember];
		Array[0] = 9000 + 1;

		m_Toolbar.Create(this);
		m_Toolbar.SetButtons(Array, nMenuMember);
		m_Toolbar.SetButtonText(0, "��������");
		m_Toolbar.GetToolBarCtrl().SetButtonWidth(60, 120);
		m_Toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist);
		m_Toolbar.SetSizes(CSize(100, TOOLBARHEIGHT), CSize(50, 40));
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_ADDORDER, false);
	}
	break;
	case 3:	// WareHouse keeper
	{

	}
	break;
	case 4:	// Orderer
	{

	}
	break;
	default:
		break;
	}

}


unsigned int _stdcall CLogisticsManagerDlg::StatusCheckThread(void *p)
{
	CLogisticsManagerDlg* pthis = (CLogisticsManagerDlg*)p;
	while (true)
	{
		DWORD   flag;
		if (InternetGetConnectedState(&flag, 0))
		{	
			pthis->PostMessage(WM_INTERNETSTATUS_CHANGE, 1, 0);
		}
		else
		{
			pthis->PostMessage(WM_INTERNETSTATUS_CHANGE, 0, 0);
		}

		if (CDBConn::Instance()->IsConnecting())
		{
			pthis->PostMessage(WM_DATABASESTATUS_CHANGE, 1, 1);
		} 
		else
		{
			pthis->PostMessage(WM_DATABASESTATUS_CHANGE, 0, 0);
			CDBConn::Instance()->ConnectDataBase(pthis->m_szDataBaseName);
		}

		Sleep(500);

		DWORD dwReply = ::WaitForSingleObject(pthis->m_BgExitHD,1000);
		if (dwReply == WAIT_OBJECT_0)
		{
			break;
		}	
	}

	return 0;
}


void CLogisticsManagerDlg::OnMENUlogin()
{
	CLoginDlg Logindlg;
	if (Logindlg.DoModal() == IDOK)
	{
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_USER, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_GOODS, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_ADDORDER, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_QUERYORDER, true);
		m_Toolbar.GetToolBarCtrl().EnableButton(IDB_ON_SUMMMERY, true);

		m_Statusbar.SetPaneText(1, "�û���zeyu");
	}
	else
	{
		
	}
}


void CLogisticsManagerDlg::OnBUTTONUser()
{
	for (auto iter = m_PagesMap.begin(); iter != m_PagesMap.end(); ++iter)
	{
		(*iter).second->ShowWindow(SW_HIDE);
	}

	m_pUserManagePage->ShowWindow(SW_SHOW);
	m_pUserManagePage->UpdateWindow();
}


void CLogisticsManagerDlg::OnBUTTONGOODS()
{
	for (auto iter = m_PagesMap.begin(); iter != m_PagesMap.end(); ++iter)
	{
		(*iter).second->ShowWindow(SW_HIDE);
	}

	m_pEnterStorePage->ShowWindow(SW_SHOW);
	m_pEnterStorePage->UpdateWindow();
}


void CLogisticsManagerDlg::OnBUTTONAddOrder()
{
	for (auto iter = m_PagesMap.begin(); iter != m_PagesMap.end(); ++iter)
	{
		(*iter).second->ShowWindow(SW_HIDE);
	}

	m_pAddOrderPage->ShowWindow(SW_SHOW);
	m_pAddOrderPage->UpdateWindow();
}


void CLogisticsManagerDlg::OnBUTTONQueryOrder()
{
	for (auto iter = m_PagesMap.begin(); iter != m_PagesMap.end(); ++iter)
	{
		(*iter).second->ShowWindow(SW_HIDE);
	}

	m_pQueryOrderPage->ShowWindow(SW_SHOW);
	m_pQueryOrderPage->UpdateWindow();	
}


void CLogisticsManagerDlg::OnBUTTONSummary()
{
	for (auto iter = m_PagesMap.begin(); iter != m_PagesMap.end(); ++iter)
	{
		(*iter).second->ShowWindow(SW_HIDE);
	}

	m_pCSummaryPage->ShowWindow(SW_SHOW);
	m_pCSummaryPage->UpdateWindow();
}

LRESULT CLogisticsManagerDlg::InternetStatusChanged(WPARAM wp, LPARAM lp)
{
	if (wp)
	{
		m_Statusbar.SetPaneText(INTERNETSTATUS, "  ������״̬�������ӡ�");
	} 
	else
	{
		m_Statusbar.SetPaneText(INTERNETSTATUS, "  ������״̬������ʧ�ܣ�");
	}

	return 0;
}


LRESULT CLogisticsManagerDlg::DatabaseStatusChanged(WPARAM wp, LPARAM lp)
{
	if (wp)
	{
		m_Statusbar.SetPaneText(DATABASESTATUS, "  ���ݿ�״̬�������ӡ�");
	}
	else
	{
		m_Statusbar.SetPaneText(DATABASESTATUS, "  ���ݿ�״̬������ʧ�ܣ�");
	}

	return 0;
}