#ifdef WIN32
// Windows-specific headers
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <windows.h>
#include <winsock2.h>

#pragma comment( lib, "winmm.lib" )
#else
// Unix-specific headers
#include <memory.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
// Common headers
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "dreamSock.h"
//#include "dreamSockLog.h"


/*************************************************************************************

	Fun��es de Configura��o da dreamSock

*************************************************************************************/

int dreamSock_Initialize(void)
{
	if(_dreamSock_init == true)
		return 0;

	_dreamSock_init = true;

//	StartLog();

	#ifdef WIN32
		return dreamSock_InitializeWinSock();
	#else
		return 0;
	#endif
}

int dreamSock_InitializeWinSock(void)
{
	WORD versionRequested;
	WSADATA wsaData;
	DWORD bufferSize = 0;
	LPWSAPROTOCOL_INFO SelectedProtocol;
	int NumProtocols;
	
	// Start WinSock2. If it fails, we do not need to call WSACleanup()
	versionRequested = MAKEWORD(2, 0);
	int error = WSAStartup(versionRequested, &wsaData);
	if(error)
	{
		//LogString("FATAL ERROR: WSAStartup failed (error = %d)", error);
		return 1;
	}
	else
	{
		//LogString("WSAStartup OK");

		// Confirm that the WinSock2 DLL supports the exact version we want. If not, call WSACleanup().
		if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion)!= 0)
		{
			//LogString("FATAL ERROR: WinSock2 DLL does not support the correct version (%d.%d)",	LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
			WSACleanup();
			return 1;
		}
	}

	// Call WSAEnumProtocols to figure out how big of a buffer we need
	NumProtocols = WSAEnumProtocols(NULL, NULL, &bufferSize);
	if((NumProtocols != SOCKET_ERROR) && (WSAGetLastError() != WSAENOBUFS))
	{
		WSACleanup();
		return 1;
	}

	// Allocate a buffer and call WSAEnumProtocols to get an array of
	// WSAPROTOCOL_INFO structs
	SelectedProtocol = (LPWSAPROTOCOL_INFO) malloc(bufferSize);
	if(SelectedProtocol == NULL)
	{
		WSACleanup();
		return 1;
	}

	// Allocate memory for protocol list and define the protocols to look for
	int *protos = (int *) calloc(2, sizeof(int));
	protos[0] = IPPROTO_TCP;
	protos[1] = IPPROTO_UDP;
	NumProtocols = WSAEnumProtocols(protos, SelectedProtocol, &bufferSize);
	free(protos);
	protos = NULL;
	free(SelectedProtocol);
	SelectedProtocol = NULL;

	if(NumProtocols == SOCKET_ERROR)
	{
		//LogString("FATAL ERROR: Didn't find any required protocols");
		WSACleanup();
		return 1;
	}

	return 0;
}

void dreamSock_Shutdown(void)
{
	if(_dreamSock_init == false)
		return;

	//LogString("Shutting down dreamSock");
	_dreamSock_init = false;
//	StopLog();

	#ifdef WIN32
		WSACleanup();
	#endif
}

/***************************************************************************************

	Fun��es de Socket da dreamSock

****************************************************************************************/

SOCKET dreamSock_Socket(int protocol)
{
	int type;
	int proto;
	SOCKET sock;

	// Check which protocol to use
	if(protocol == DREAMSOCK_TCP)
	{
		type = SOCK_STREAM;
		proto = IPPROTO_TCP;
	}
	else
	{
		type = SOCK_DGRAM;
		proto = IPPROTO_UDP;
	}

	// Create the socket
	if((sock = socket(AF_INET, type, proto)) ==  INVALID_SOCKET)
	{
		//LogString("dreamSock_Socket - socket() failed");
		#ifdef WIN32
			errno = WSAGetLastError();
			//LogString("Error: socket() code %d : %s", errno, strerror(errno));
		#else
			LogString("Error: socket() : %s", strerror(errno));
		#endif

		return DREAMSOCK_INVALID_SOCKET;
	}
		

	return sock;
}

int dreamSock_SetNonBlocking(SOCKET sock, u_long setMode)
{
	u_long set = setMode;

	// Set the socket option
	#ifdef WIN32
		return ioctlsocket(sock, FIONBIO, &set);
	#else
		return ioctl(sock, FIONBIO, &set);
	#endif
}

int dreamSock_SetBroadcasting(SOCKET sock, int mode)
{
	// make it broadcast capable
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &mode,sizeof(int)) < 0)
	{
		//LogString("DreamSock_SetBroadcasting failed");

		#ifdef WIN32
			int err = WSAGetLastError();
			//LogString("Error code %d: setsockopt() : %s", err, strerror(err));
		#else
			LogString("Error code %d: setsockopt() : %s", errno,
			strerror(errno));
		#endif

		return DREAMSOCK_INVALID_SOCKET;
	}

	return 0;
}

int dreamSock_StringToSockaddr(char *addressString, struct sockaddr *sadr)
{
	char copy[128];
	memset(sadr, 0, sizeof(struct sockaddr));
	struct sockaddr_in *addressPtr = (struct sockaddr_in *) sadr;
	addressPtr->sin_family = AF_INET;
	addressPtr->sin_port = htons(0);
	strcpy(copy, addressString);

	// If the address string begins with a number, assume an IP address
	if(copy[0] >= '0' && copy[0] <= '9')
	{
		*(int *) &addressPtr->sin_addr = inet_addr(copy);
		return 0;
	}
	else 
		return 1;
}

SOCKET dreamSock_OpenUDPSocket(char *netInterface, int port)
{
	SOCKET sock;
	struct sockaddr_in address;
	sock = dreamSock_Socket(DREAMSOCK_UDP);

	if(sock == DREAMSOCK_INVALID_SOCKET)
		return sock;

	dreamSock_SetNonBlocking(sock, 1);
	dreamSock_SetBroadcasting(sock, 1);

	// If no address string provided, use any interface available
	if(!netInterface || !netInterface[0] || !strcmp(netInterface,"localhost"))
	{
		//LogString("No net interface given, using any interface available");
		address.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		//LogString("Using net interface = '%s'", netInterface);
		dreamSock_StringToSockaddr(netInterface, (struct sockaddr *)&address);
	}

	// If no port number provided, use any port number available
	if(port == 0)
	{
		//LogString("No port defined, picking one for you");
		address.sin_port = 0;
	}
	else
	{
		address.sin_port = htons((short) port);
	}

	address.sin_family = AF_INET;

	// Bind the address to the socket
	if(bind(sock, (struct sockaddr *) &address, sizeof(address)) < 0)
	{
		#ifdef WIN32
			errno = WSAGetLastError();
			//LogString("Error code %d: bind() : %s", errno, strerror(errno));
		#else
			LogString("Error code %d: bind() : %s", errno, strerror(errno));
		#endif

		return DREAMSOCK_INVALID_SOCKET;
	}

	// Get the port number (if we did not define one, we get the assigned port number here)
	socklen_t len = sizeof(address);
	getsockname(sock, (struct sockaddr *) &address, &len);
	//LogString("Opening UDP port = %d", ntohs(address.sin_port));

	return sock;
}

void dreamSock_CloseSocket(SOCKET sock)
{
	#ifdef WIN32
		closesocket(sock);
	#else
		close(sock);
	#endif
}

int dreamSock_GetPacket(SOCKET sock, char *data, struct sockaddr *from)
{
	int ret;
	struct sockaddr tempFrom;
	socklen_t fromlen;
	fromlen = sizeof(tempFrom);
	ret = recvfrom(sock, data, 1400, 0, (struct sockaddr *) &tempFrom,&fromlen);

	// Copy the address to the from pointer
	if(from != NULL)
		*(struct sockaddr *) from = tempFrom;

	if(ret == SOCKET_ERROR)
	{
		#ifdef WIN32
			errno = WSAGetLastError();

			// Silently handle wouldblock
			if(errno == WSAEWOULDBLOCK)
				return ret;

			if(errno == WSAEMSGSIZE)
			{
				// ERROR: Oversize packet
				return ret;
			}

			//LogString("Error code %d: recvfrom() : %s", errno, strerror(errno));
		#else

			// Silently handle wouldblock
			if(errno == EWOULDBLOCK || errno == ECONNREFUSED)
				return ret;

			LogString("Error code %d: recvfrom() : %s", errno, strerror(errno));
		#endif

		return ret;
	}

	return ret;
}

void dreamSock_SendPacket(SOCKET sock, int length, char *data, struct sockaddr addr)
{
	int ret;
	ret = sendto(sock, data, length, 0, &addr, sizeof(addr));
	if(ret == SOCKET_ERROR)
	{
		#ifdef WIN32
			errno = WSAGetLastError();

			// Silently handle wouldblock
			if(errno == WSAEWOULDBLOCK)
				return;

			//LogString("Error code %d: sendto() : %s", errno,strerror(errno));
		#else

			// Silently handle wouldblock
			if(errno == EWOULDBLOCK)
				return;

			LogString("Error code %d: sendto() : %s", errno,
			strerror(errno));
		#endif
	}

}

void dreamSock_Broadcast(SOCKET sock, int length, char *data, int port)
{
	struct sockaddr_in servaddr;
	socklen_t len;

	// Use broadcast address
	u_long inetAddr = inet_addr("255.255.255.255");

	// Fill address information structure
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inetAddr;
	len = sizeof(servaddr);

	// Broadcast!
	int ret = sendto(sock, data, length, 0, (struct sockaddr *) &servaddr, len);
	if(ret == SOCKET_ERROR)
	{
		#ifdef WIN32
			errno = WSAGetLastError();

			// Silently handle wouldblock
			if(errno == WSAEWOULDBLOCK)
				return;

			//LogString("Error code %d: sendto() : %s", errno, strerror(errno));
		#else

			// Silently handle wouldblock
			if(errno == EWOULDBLOCK)
				return;

			LogString("Error code %d: sendto() : %s", errno,
			strerror(errno));
		#endif
	}

}

int dreamSock_Win_GetCurrentSystemTime(void)
{
	int curtime;
	static int base;
	static bool initialized = false;

	
	if(!initialized)
	{
		//base = System::DateTime::Now.Millisecond;
		base = timeGetTime() & 0xffff0000;
		initialized = true;
	}
	
	curtime  = timeGetTime();
	curtime =  (curtime) - (base);
	//curtime = System::DateTime::Now.Millisecond - base;
	return curtime;
}

int dreamSock_GetCurrentSystemTime(void)
{
	#ifndef WIN32
		return dreamSock_Linux_GetCurrentSystemTime();
	#else
		return dreamSock_Win_GetCurrentSystemTime();
	#endif
}

