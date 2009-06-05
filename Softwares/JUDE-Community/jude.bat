@echo off
rem Batch file to run JUDE on Windows

rem Remove "rem" from following two lines, if you'd like to use j2sdk.
rem set JAVA_HOME=C:\j2sdk1.4.2_09
rem set PATH=%JAVA_HOME%\bin;%PATH%

set JUDE_JAR=jude-community.jar
set INITIAL_HEAP_SIZE=16m
set MAXIMUM_HEAP_SIZE=384m
set STACK_SIZE=2m

set USER_LANGUAGE=
rem set USER_LANGUAGE=ja
rem set USER_LANGUAGE=en

set USER_COUNTRY=
rem set USER_COUNTRY=JP
rem set USER_COUNTRY=US


rem JUDE_HOME should be this folder
if not "%JUDE_HOME%"=="" goto hasJudeHome

if "%OS%"=="Windows_NT" goto setJudeHomeNT

rem *** Windows98 user have to edit here ****
rem set JUDE_HOME=c:\Program Files\JUDE-Community

if "%JUDE_HOME%"=="" goto noJudeHome
if not exist "%JUDE_HOME%\%JUDE_JAR%" goto badJudeHome
goto hasJudeHome

rem for Windows2000, XP, NT
:setJudeHomeNT
set JUDE_HOME=%~dp0

:hasJudeHome

rem set CLASSPATH=%JUDE_HOME%\%JUDE_JAR%


set JAVA_OPTS=-Xms%INITIAL_HEAP_SIZE% -Xmx%MAXIMUM_HEAP_SIZE% -Xss%STACK_SIZE%
if not "%USER_LANGUAGE%"=="" set JAVA_OPTS=%JAVA_OPTS% -Duser.language=%USER_LANGUAGE%
if not "%USER_COUNTRY%"=="" set JAVA_OPTS=%JAVA_OPTS% -Duser.country=%USER_COUNTRY%

if exist "%JUDE_HOME%\jre\bin\javaw.exe" set PATH=%JUDE_HOME%\jre\bin;%PATH%

rem run Jude
start javaw %JAVA_OPTS% -jar "%JUDE_HOME%\%JUDE_JAR%"  %1 %2 %3
IF ERRORLEVEL 2 goto noJavaw
goto end

:noJudeHome
echo.
echo JUDE_HOME is not set.  Please set JUDE_HOME environment variable
echo or edit jude.bat to set JUDE_HOME.
echo. 
pause
goto end

:badJudeHome
echo.
echo JUDE_HOME is invalid.  Please check your JUDE_HOME.
echo. 
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
echo       rem set JAVA_HOME=C:\j2sdk1.4.2_08
echo       rem set PATH=%JAVA_HOME%\bin;%PATH%
echo     after:
echo       set JAVA_HOME=C:\j2sdk1.4.2_08
echo       set PATH=%JAVA_HOME%\bin;%PATH%
echo.
echo.
pause
goto end

:end
