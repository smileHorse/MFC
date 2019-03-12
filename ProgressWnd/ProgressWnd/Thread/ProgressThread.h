/*!
 * \file ProgressThread.h
 *
 * \author mateng
 * \date ���� 2019
 *
 * �����Ի�����������߳�
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

	// ��ʼ���ȴ���
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