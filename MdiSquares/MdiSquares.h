
// MdiSquares.h : MdiSquares Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMdiSquaresApp:
// �йش����ʵ�֣������ MdiSquares.cpp
//

class CMdiSquaresApp : public CWinApp
{
public:
	CMdiSquaresApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMdiSquaresApp theApp;
