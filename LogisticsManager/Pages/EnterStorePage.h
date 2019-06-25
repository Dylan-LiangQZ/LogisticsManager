#pragma once


// CEnterStorePage �Ի���

class CEnterStorePage : public CDialogEx
{
	DECLARE_DYNAMIC(CEnterStorePage)

public:
	CEnterStorePage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEnterStorePage();

	enum { IDD = IDD_DIALOG_ENTERSTORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CRect		m_RectWorkingArea;
	CFont		m_FontStatic1;
	CFont		m_FontEdit1;
	LOGFONT		m_FontList1;

	CDateTimeCtrl m_DateTimeQuery;
	CListCtrl	  m_TableEnterGoods;

	virtual BOOL OnInitDialog();
	void OnResizeControl(int CtrlID, double cx, double cy);

public:
	void SetWorkingArea(CRect & rect);
	afx_msg void OnBnClickedEEnter();
	afx_msg void OnBnClickedEQuery();
};
