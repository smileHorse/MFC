
// ScrollDemo.h : ScrollDemo Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CScrollDemoApp:
// �йش����ʵ�֣������ ScrollDemo.cpp
//

class CScrollDemoApp : public CWinApp
{
public:
	CScrollDemoApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CScrollDemoApp theApp;
