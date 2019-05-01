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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
