@echo off

rem Written by DeviceIoControl - Register CLEVO_KeyboardColour as a service to start on boot in the background.

net session > nul 2>&1
if not %errorlevel%==0 goto OnAccessError
if not exist %cd%\RegisterClevoKbOnBoot.cmd goto OnCurrDirError

echo Before continuing, please ensure you have adjusted the StartClevoKB.cmd script (in the current directory) to a theme of your choice.
echo If you have already registered this program on boot and still wish to change the theme, please change the command-line in C:\ClevoKB\StartClevoKB.cmd.
pause

echo Creating service directories...
if exist C:\ClevoKB goto SvcAlreadyRegd
mkdir C:\ClevoKB
mkdir C:\ClevoKB\Service

echo Copying files...
copy StartClevoKB.cmd C:\ClevoKB\ > nul
copy ..\CLEVO_KeyboardColour.exe C:\ClevoKB\Service\ > nul
copy ..\InsydeDCHU.dll C:\ClevoKB\Service\ > nul
copy ..\GetProductID64.dll C:\ClevoKB\Service\ > nul

echo Registering CLEVO Keyboard Colours startup service...
sc create "CLEVO Keyboard Colours" binPath="cmd.exe /c \"call C:\ClevoKB\StartClevoKB.cmd\"" type=own depend=winmgmt start=auto error=normal

echo Starting CLEVO KB Colour Service...
sc start "CLEVO Keyboard Colours" > nul

echo Successfully registered CLEVO KB service!
pause
exit

:SvcAlreadyRegd
echo Clevo KB Colour service is already registered, please adjust C:\ClevoKB\StartClevoKB.cmd to change theme and restart your machine.
pause
exit

:OnCurrDirError
echo Please change current directory (using the cd command) to the "Scripts\" directory before running this command.
pause
exit

:OnAccessError
echo Insufficient privileges - Please run this script as Administrator!
pause
exit

