
// LogisticsManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLogisticsManagerApp: 
// �йش����ʵ�֣������ LogisticsManager.cpp
//

class CLogisticsManagerApp : public CWinApp
{
public:
	CLogisticsManagerApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLogisticsManagerApp theApp;