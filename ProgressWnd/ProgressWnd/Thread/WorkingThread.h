/*!
 * \file WorkingThread.h
 *
 * \author mateng
 * \date 三月 2019
 *
 * 工作线程
 */
#ifndef WORKINGTHREAD_H
#define WORKINGTHREAD_H

#include "afxcmn.h"
#include "afxwin.h"

class CWorkingThread
{
public:
	CWorkingThread();
	CWorkingThread(CWnd* pWnd);

	// 开始处理
	void startWorking();

	CWnd* getWnd() const { return m_pWnd; }
	void setWnd(CWnd* val) { m_pWnd = val; }
	
private:
	CWnd* m_pWnd;
};

#endif