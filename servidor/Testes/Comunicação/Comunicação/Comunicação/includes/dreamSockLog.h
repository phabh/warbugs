#ifndef __DREAMSOCKLOG_H__
#define __DREAMSOCKLOG_H__
#ifdef WIN32
class dreamConsole
{
public:
dreamConsole(char *title);
~dreamConsole();
void println(char *string, int type, ...);
};
#define CONSOLE_NOTIFY 0
#define CONSOLE_ERROR 1
#define CONSOLE_FATAL 2
// Function prototypes
void StartLogConsole(void);
#endif
// Function prototypes
void StartLog(void);
void StopLog(void);
void LogString(char *string, ...);
#endif

#ifdef WIN32
void StartLogConsole(void)
{
	console = new dreamConsole("dreamSock application");
}
#endif

dreamConsole::dreamConsole(char *title)
{
	AllocConsole();
	SetConsoleTitle(title);
}

dreamConsole::~dreamConsole()
{
	FreeConsole();
}

void dreamConsole::println(char *string, int type, ...)
{
	char buf[1024];
	char buf2[1024];
	va_list ap;
	va_start(ap, string);
	vsprintf(buf, string, ap);
	va_end(ap);
	sprintf(buf2, "-> %s\n", buf);
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	switch(type)
	{
		case 0:
			SetConsoleTextAttribute(console, FOREGROUND_GREEN |
			FOREGROUND_INTENSITY);
			break;
		case 1:
			SetConsoleTextAttribute(console, FOREGROUND_RED |
			FOREGROUND_INTENSITY);
			break;
	}

	WriteConsole(console, buf2, strlen(buf2), NULL, NULL);
}

void StartLog(void)
{
	time_t current = time(NULL);
	if((LogFile = fopen("dreamSock.log", "w")) != NULL)
	{
		fprintf(LogFile, "Log file started %s", ctime(&current));
		fclose(LogFile);
	}
	if((LogFile = fopen("dreamSock.log", "a")) != NULL)
	{
	}
}

void LogString(char *string, ...)
{
	char buf[1024];
	va_list ap;
	va_start(ap, string);
	vsprintf(buf, string, ap);
	va_end(ap);
	// Get current time and date
	time_t current = time(NULL);
	char timedate[64];
	sprintf(timedate, ctime(&current));
	// Remove linefeed from time/date string
	inti=0;
	while(timedate[i] != '\n')
	{
		i++;
	}
	timedate[i] = '\0';
	// Output log string
	#ifdef WIN32
		fprintf(LogFile, "%s: %s\n", timedate, buf);
		if(console)
			console->println(buf, 0);
	#else
		// Linux outputs to screen and to the open file when running as daemon
		printf("%s: %s\n", timedate, buf);
	#endif
}

void StopLog(void)
{
	fclose(LogFile);
	#ifdef WIN32
		if(console != NULL)
			delete console;
	#endif
}