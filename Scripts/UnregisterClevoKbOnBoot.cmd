@echo off

rem CLEVO Keyboard colours will no longer startup on your system

net session > nul 2>&1
if not %errorlevel%==0 goto OnAccessError

echo Stopping CLEVO Keyboard Colours service...
taskkill /im CLEVO_KeyboardColour.exe /f > nul

echo Unregistering CLEVO Keyboard Colours startup service...
sc delete "CLEVO Keyboard Colours"

echo Deleting CLEVO Keyboard Colour service files...
del /f /q C:\ClevoKB\Service\CLEVO_KeyboardColour.exe > nul
del /f /q C:\ClevoKB\Service\InsydeDCHU.dll > nul
del /f /q C:\ClevoKB\Service\GetProductID64.dll > nul
del /f /q C:\ClevoKB\StartClevoKB.cmd > nul

echo Removing Clevo KB Colour service directories...
rmdir /q /s C:\ClevoKB\

echo CLEVO Keyboard Colours was unregistered - This will no longer start on boot.
pause
exit

:OnAccessError
echo Insufficient privileges - Please run this script as Administrator!
pause
exit