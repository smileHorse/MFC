
// sketch.h : sketch Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CsketchApp:
// �йش����ʵ�֣������ sketch.cpp
//

class CsketchApp : public CWinApp
{
public:
	CsketchApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CsketchApp theApp;
