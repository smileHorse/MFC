
// ProgressWnd.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProgressWndApp:
// �йش����ʵ�֣������ ProgressWnd.cpp
//

class CProgressWndApp : public CWinApp
{
public:
	CProgressWndApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProgressWndApp theApp;