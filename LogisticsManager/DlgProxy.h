
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CLogisticsManagerDlg;


// CLogisticsManagerDlgAutoProxy ����Ŀ��

class CLogisticsManagerDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLogisticsManagerDlgAutoProxy)

	CLogisticsManagerDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CLogisticsManagerDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CLogisticsManagerDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLogisticsManagerDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

