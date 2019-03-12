/*!
 * \file ProgressThread.h
 *
 * \author mateng
 * \date 三月 2019
 *
 * 操作对话框进度条的线程
 */

#ifndef PROGRESSTHREAD_H
#define PROGRESSTHREAD_H

#include "afxcmn.h"
#include "afxwin.h"

class CProgressThread
{
public:
	CProgressThread();
	CProgressThread(CWnd* pWnd);

	// 开始进度处理
	void startProgress();

	CWnd* getWnd() const { return m_pWnd; }
	void setWnd(CWnd* val) { m_pWnd = val; }

	BOOL isStop() const { return m_bStop; }
	void setStop(BOOL val) { m_bStop = val; }

private:
	CWnd* m_pWnd;
	BOOL  m_bStop;
};

#endif