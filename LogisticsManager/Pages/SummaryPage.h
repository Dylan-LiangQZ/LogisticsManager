#pragma once


// CSummaryPage dialog

class CSummaryPage : public CDialogEx
{
	DECLARE_DYNAMIC(CSummaryPage)

public:
	CSummaryPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSummaryPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUMMARY };

	CRect		m_RectWorkingArea;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void OnResizeControl(int CtrlID, double cx, double cy);

	DECLARE_MESSAGE_MAP()

public:
	void SetWorkingArea(CRect & rect);
};
