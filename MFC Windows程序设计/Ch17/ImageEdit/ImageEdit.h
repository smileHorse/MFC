
// ImageEdit.h : ImageEdit Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CImageEditApp:
// �йش����ʵ�֣������ ImageEdit.cpp
//

class CImageEditApp : public CWinApp
{
public:
	CImageEditApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageEditApp theApp;
