@echo off
rem Batch file to compile a sample of JUDE API on Windows

rem Remove "rem" from following two lines, if you'd like to use j2sdk.
rem set JAVA_HOME=C:\j2sdk1.4.2_10
rem set PATH=%JAVA_HOME%\bin

rem set JUDE_JAR=..\..\..\jude-pro.jar
rem set JUDE_JAR=..\..\..\jude-community.jar
set API_JAR=..\..\..\jude-api.jar
set CLASSPATH=%JUDE_JAR%;%API_JAR%

rem compile
javac -classpath %CLASSPATH% *.java
IF ERRORLEVEL 2 goto noJavac
goto end

:noJavac
echo.
echo Failed to compile.
echo Java SDK is required to compile.
echo.
pause
goto end

:end