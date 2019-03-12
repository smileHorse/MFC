/*!
 * \file WorkingThread.h
 *
 * \author mateng
 * \date 三月 2019
 *
 * 工作线程
 */

#include "stdafx.h"
#include "WorkingThread.h"
#include "../MessageDefine.h"

#include <iostream>
using namespace std;

UINT WorkingThreadProc(LPVOID param)
{
	CWorkingThread* pThread = (CWorkingThread*)param;
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

	for (int i = 0; i < 1000; ++i)
	{
		cout << "i = " << i << endl;
		Sleep(10);
	}

	::PostMessage(hWnd, PROGRESS_FINISHED, 0, 0);
	return 0;
}

CWorkingThread::CWorkingThread()
{

}

CWorkingThread::CWorkingThread(CWnd* pWnd)
{

}

// 开始处理
void CWorkingThread::startWorking()
{
	CWinThread* pThread = AfxBeginThread((AFX_THREADPROC)WorkingThreadProc, this);
	pThread->ResumeThread();
}
