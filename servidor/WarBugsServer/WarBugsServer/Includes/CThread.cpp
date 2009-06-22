#ifndef _CTHREAD_CPP_
#define _CTHREAD_CPP_
/*
 * ThreadJC.cpp
 *
 *  Created on: 08/12/2008
 *      Author: kurumim
 */

#include "CThread.h"


CThread::CThread() {}
CThread::~CThread()
{
	_endthread();
}

int CThread::Start(void *arg)
{
	//pthread_t threads[1];
	Arg(arg); // store user data
	//char *message1 = "Thread 1";
	InitializeCriticalSection(&sessaoCritica);
	int errcode = _beginthread( CThread::EntryPoint, 0, (void *)this);
	return errcode;
}

void CThread::Run(void * arg)
{
   Setup();
   Execute();
}

void CThread::Setup()
{
    // Do any setup here
}

void CThread::Execute()
{
    // Your code goes here
}

 void CThread::EntryPoint(void * pthis)
 {
	 CThread * pt = (CThread*)pthis;
	 pt->Run(pthis);

 }

void CThread::EndThread()
{
	_endthread();
	DeleteCriticalSection(&sessaoCritica);
}



#endif