
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CLogisticsManagerDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLogisticsManagerDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLogisticsManagerDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_ILogisticsManager ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {32B476DB-609D-41C0-AE45-83BBCCADC14D}
static const IID IID_ILogisticsManager =
{ 0x32B476DB, 0x609D, 0x41C0, { 0xAE, 0x45, 0x83, 0xBB, 0xCC, 0xAD, 0xC1, 0x4D } };

BEGIN_INTERFACE_MAP(CLogisticsManagerDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLogisticsManagerDlgAutoProxy, IID_ILogisticsManager, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {7FF20474-B532-4E97-B339-4A7B356D1336}
IMPLEMENT_OLECREATE2(CLogisticsManagerDlgAutoProxy, "LogisticsManager.Application", 0x7ff20474, 0xb532, 0x4e97, 0xb3, 0x39, 0x4a, 0x7b, 0x35, 0x6d, 0x13, 0x36)


// CLogisticsManagerDlgAutoProxy ��Ϣ�������
