#pragma once

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

class CTimer
{

private:

	float _deltaTime, td, td2;
	__int64       _frequencia;
	float         _resolucao;	
	unsigned long _timerStart;	
	unsigned long _timerElapsed;	
	bool		  _hiPerformanceTimer;	
	__int64       _performanceTimerStart;	
	__int64       _performanceTimerElapsed;
	
public:

	CTimer()
	{
		_deltaTime = 0;
		td2 = 0;
		td = 0;
		_frequencia = 0;
		_performanceTimerStart = 0;
		_resolucao = 0;
		_timerStart = 0;
		_timerElapsed = 0;
		_performanceTimerElapsed = 0;
		_hiPerformanceTimer = 0;

		initialize();
	}

	void update() 
	{
		td2 = getTime();
		_deltaTime = (td2-td) * 0.1f; 
		td = td2;
	}

	void initialize()
	{
		if (!QueryPerformanceFrequency((LARGE_INTEGER *) &_frequencia))
		{
			// Se o computador não suportar contador de alta performance
			_hiPerformanceTimer	= false;					
			_timerStart	= timeGetTime(); 
			_resolucao = 1.0f/1000.0f;				
			_frequencia = 1000;						
			_timerElapsed = _timerStart;
		}
		else
		{
			QueryPerformanceCounter((LARGE_INTEGER *) &_performanceTimerStart);
			_hiPerformanceTimer	= true;
			_resolucao = (float) (((double)1.0f)/((double)_frequencia));
			_performanceTimerElapsed = _performanceTimerStart;
		}
	}

	float getDeltaTime() const 
	{ 
		return _deltaTime; 
	}

	float getTime() const
	{
		__int64 tempo;									

		if (_hiPerformanceTimer)
		{
			QueryPerformanceCounter((LARGE_INTEGER *) &tempo);
			return ( (float) ( tempo - _performanceTimerStart) * _resolucao)*1000.0f;
		}
		else
		{ 
			return( (float) ( timeGetTime() - _timerStart) * _resolucao) * 1000.0f;
		}
	}
};