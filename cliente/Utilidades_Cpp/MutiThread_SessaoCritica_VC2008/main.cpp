#include<windows.h>
#include<iostream>

using namespace std;

// Declarar a variável que ambas as threads utilização
static int  g_n;

// Objeto de Sessão Crítica
CRITICAL_SECTION m_cs;

UINT ThreadOne(LPVOID lParam)
{
	// Thread 1

	for(int i=0; i<10; i++)
	{
		cout << "Th1" << endl;
		system("pause");
	}

	// Bloquear sessão crítica
	EnterCriticalSection(&m_cs);

	// Executar comandos
	for(int i=0; i<10; i++)
	{
		g_n++;
		cout << "Thread 1 :" << g_n << "\n";
	}

	// Desbloquear sessão crítica
	LeaveCriticalSection(&m_cs);
		
	return 0;
}

UINT ThreadTwo(LPVOID lParam)
{

	for(int i=0; i<10; i++)
	{
		cout << "Th2" << endl;
		system("pause");
	}

	// Bloquear sessão crítica
	EnterCriticalSection(&m_cs); 

	for(int i=0; i<10; i++)
	{
		g_n++;
		cout << "Thread 2: "<< g_n << "\n";
	}

	// Desbloquear sessão crítica
	LeaveCriticalSection(&m_cs);

	return 0;
}

int main()
{

	// Cria referências para as threads
	HANDLE hThrd[2];
	
	// Variáveis para guardar os IDs das threads
	DWORD IDThread1, IDThread2;
	
	// Inicializar sessão crítica
	InitializeCriticalSection(&m_cs); 

	// Criar threads usando a função CreateThread
	hThrd[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadOne, (LPVOID)NULL, 0, &IDThread1);       
	hThrd[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadTwo, (LPVOID)NULL, 0, &IDThread2); 

	// Esperar a execução da thread principal (tempo infinito)
	WaitForMultipleObjects(2, hThrd, TRUE, INFINITE);

	// Deletar a sessão crítica
	DeleteCriticalSection(&m_cs);

	system("pause");
	
	return 0;
}