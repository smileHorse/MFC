
// Wanderer.h : Wanderer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CWandererApp:
// �йش����ʵ�֣������ Wanderer.cpp
//

class CWandererApp : public CWinApp
{
public:
	CWandererApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWandererApp theApp;
