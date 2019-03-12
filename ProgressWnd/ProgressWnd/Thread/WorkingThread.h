/*!
 * \file WorkingThread.h
 *
 * \author mateng
 * \date ���� 2019
 *
 * �����߳�
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

	// ��ʼ����
	void startWorking();

	CWnd* getWnd() const { return m_pWnd; }
	void setWnd(CWnd* val) { m_pWnd = val; }
	
private:
	CWnd* m_pWnd;
};

#endif