
// DriveView.h : DriveView Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDriveViewApp:
// �йش����ʵ�֣������ DriveView.cpp
//

class CDriveViewApp : public CWinApp
{
public:
	CDriveViewApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDriveViewApp theApp;
