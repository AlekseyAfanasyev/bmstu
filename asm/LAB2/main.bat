echo off
:menu
cls
echo lab 2 menu:
echo 1. mode 1
echo 2. mode 2
echo 3. open help file
echo 4. make dirs
echo 5. exit
rem get digit
be ask "choose digit from: 1,2,3,4,5" '12345' default=2 timeout=10
rem branches
if ERRORLEVEL 5 goto fin
if ERRORLEVEL 4 goto 4
if ERRORLEVEL 3 goto 3
if ERRORLEVEL 2 GOTO 2
if ERRORLEVEL 1 GOTO 1
goto fin
:1
echo 1
pause
goto menu
:2
echo 2
pause
goto menu
:3
echo 3
pause
goto menu
:4
mkdir %1
shift
pause
goto menu
:fin
echo finishing programm
	
																																																																																										

