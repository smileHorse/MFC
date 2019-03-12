/*!
 * \file ProgressThread.h
 *
 * \author mateng
 * \date ���� 2019
 *
 * �����Ի�����������߳�
 */

#include "stdafx.h"
#include "ProgressThread.h"
#include "../MessageDefine.h"

UINT ProgressThreadProc(LPVOID param)
{
	CProgressThread* pThread = (CProgressThread*)param;
	if (!pThread)
	{
		return -1;
	}

	CWnd* pWnd = pThread->getWnd();
	if (!pWnd)
	{
		return -1;
	}
	HWND hWnd = pWnd->GetSafeHwnd();

	while(true)
	{
		if (pThread->isStop())
		{
			break;
		}

		::PostMessage(hWnd, PROGRESS_OFFSET, 0, 0);
		Sleep(100);
	}
	return 0;
}

CProgressThread::CProgressThread()
	: m_bStop(false)
{

}

CProgressThread::CProgressThread(CWnd* pWnd)
	: m_pWnd(pWnd), m_bStop(false)
{

}

// ��ʼ���ȴ���
void CProgressThread::startProgress()
{
	AfxBeginThread((AFX_THREADPROC)ProgressThreadProc, this);
}
