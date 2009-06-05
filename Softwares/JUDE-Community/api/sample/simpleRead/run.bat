@echo off
rem Batch file to run a sample of JUDE API on Windows

rem Remove "rem" from following two lines, if you'd like to use j2sdk.
rem set JAVA_HOME=C:\j2sdk1.4.2_10
rem set PATH=%JAVA_HOME%\bin;%PATH%

set JUDE_JAR=..\..\..\jude-community.jar
set API_JAR=..\..\..\jude-api.jar
set CLASSPATH=%JUDE_JAR%;%API_JAR%;

set INITIAL_HEAP_SIZE=16m
set MAXIMUM_HEAP_SIZE=256m
set STACK_SIZE=2m

set JAVA_OPTS=-Xms%INITIAL_HEAP_SIZE% -Xmx%MAXIMUM_HEAP_SIZE% -Xss%STACK_SIZE%
set JAVA_OPTS=%JAVA_OPTS% -classpath %CLASSPATH%

rem run
java %JAVA_OPTS% APIForReadingModelsSample %1 %2
IF ERRORLEVEL 2 goto noJavaw
pause
goto end

:noJavaw
echo.
echo Failed to run java.
echo Java runtime environment is required to run JUDE.
echo Please read README.txt in %JUDE_HOME%
echo and setup Java environment at first.
echo.
echo JUDE tries to run javaw. It should be in PATH system environment variable.
echo.
echo If you would like to run java in your specified folder, you can edit jude.bat
echo in %JUDE_HOME%
echo like followings and set your JAVA_HOME.
echo     before:
echo       rem set JAVA_HOME=C:\j2sdk1.4.2_10
echo       rem set PATH=%JAVA_HOME%\bin;%PATH%
echo     after:
echo       set JAVA_HOME=C:\j2sdk1.4.2_10
echo       set PATH=%JAVA_HOME%\bin;%PATH%
echo.
echo.
pause
goto end

:end
