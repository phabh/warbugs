#ifndef _CBUGTHREAD_CPP_
#define _CBUGTHREAD_CPP_

#include "CBugThread.h"


CBugThread::CBugThread() 
{
	_error = 0;
	_running = false;
}

CBugThread::~CBugThread() 
{
	stop();
}

bool CBugThread::start() 
{
	_running = true;
	InitializeCriticalSection(&m_cs);
	_error = _beginthread( CBugThread::_exec, 0, (void *) this);
	if( _error != 0 ) 
		return false;
	
	return true;
}

void CBugThread::stop() 
{
	_running = false;
}

void CBugThread::_exec(void * instance)
{
	CBugThread * This = reinterpret_cast<CBugThread *>(instance);


	bool exitRet = true;

	while( (exitRet = This->run()) && This->isRunning() ) {
		
	}

	_endthread();
}

bool CBugThread::isRunning()
{
	return _running; 
}

void CBugThread::enterCriticalSection()
{
	EnterCriticalSection(&m_cs);
}

void CBugThread::leaveCriticalSection()
{
	LeaveCriticalSection(&m_cs);
}


#endif