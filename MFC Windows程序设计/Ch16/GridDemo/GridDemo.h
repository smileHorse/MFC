
// GridDemo.h : GridDemo Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGridDemoApp:
// �йش����ʵ�֣������ GridDemo.cpp
//

class CGridDemoApp : public CWinApp
{
public:
	CGridDemoApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGridDemoApp theApp;
