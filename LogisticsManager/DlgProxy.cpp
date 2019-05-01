
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "LogisticsManager.h"
#include "DlgProxy.h"
#include "LogisticsManagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogisticsManagerDlgAutoProxy

IMPLEMENT_DYNCREATE(CLogisticsManagerDlgAutoProxy, CCmdTarget)

CLogisticsManagerDlgAutoProxy::CLogisticsManagerDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CLogisticsManagerDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CLogisticsManagerDlg)))
		{
			m_pDialog = reinterpret_cast<CLogisticsManagerDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CLogisticsManagerDlgAutoProxy::~CLogisticsManagerDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CLogisticsManagerDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLogisticsManagerDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLogisticsManagerDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_ILogisticsManager 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {32B476DB-609D-41C0-AE45-83BBCCADC14D}
static const IID IID_ILogisticsManager =
{ 0x32B476DB, 0x609D, 0x41C0, { 0xAE, 0x45, 0x83, 0xBB, 0xCC, 0xAD, 0xC1, 0x4D } };

BEGIN_INTERFACE_MAP(CLogisticsManagerDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLogisticsManagerDlgAutoProxy, IID_ILogisticsManager, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {7FF20474-B532-4E97-B339-4A7B356D1336}
IMPLEMENT_OLECREATE2(CLogisticsManagerDlgAutoProxy, "LogisticsManager.Application", 0x7ff20474, 0xb532, 0x4e97, 0xb3, 0x39, 0x4a, 0x7b, 0x35, 0x6d, 0x13, 0x36)


// CLogisticsManagerDlgAutoProxy 消息处理程序
