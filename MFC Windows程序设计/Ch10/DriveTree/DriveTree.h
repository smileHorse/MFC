
// DriveTree.h : DriveTree Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDriveTreeApp:
// �йش����ʵ�֣������ DriveTree.cpp
//

class CDriveTreeApp : public CWinApp
{
public:
	CDriveTreeApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDriveTreeApp theApp;
