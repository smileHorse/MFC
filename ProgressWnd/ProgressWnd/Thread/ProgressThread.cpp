/*!
 * \file ProgressThread.h
 *
 * \author mateng
 * \date 三月 2019
 *
 * 操作对话框进度条的线程
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

// 开始进度处理
void CProgressThread::startProgress()
{
	AfxBeginThread((AFX_THREADPROC)ProgressThreadProc, this);
}
