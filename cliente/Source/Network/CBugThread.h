#ifndef _CBUGTHREAD_H_
#define _CBUGTHREAD_H_

#include <windows.h>
#include <process.h>

static CRITICAL_SECTION m_cs;

class CBugThread{

private:
	int _error;
	bool _running;



public:
	CBugThread();
	~CBugThread();

	bool start();
	void stop();

	static void enterCriticalSection();
	static void leaveCriticalSection();

	static void _exec(void * instance);

	virtual bool run()=0;

	bool isRunning();
};




#endif