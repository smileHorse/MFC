
// WinDir.h : WinDir Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CWinDirApp:
// �йش����ʵ�֣������ WinDir.cpp
//

class CWinDirApp : public CWinApp
{
public:
	CWinDirApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinDirApp theApp;
