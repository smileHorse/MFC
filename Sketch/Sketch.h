
// Sketch.h : Sketch Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSketchApp:
// �йش����ʵ�֣������ Sketch.cpp
//

class CSketchApp : public CWinApp
{
public:
	CSketchApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSketchApp theApp;
