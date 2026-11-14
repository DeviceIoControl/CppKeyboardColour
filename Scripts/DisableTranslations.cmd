@echo off

echo Disabling CLEVO Keyboard Colour translations...

reg delete HKCU\Software\CLEVO_KeyboardColour /va /f

echo Translations are DISABLED. Restart CLEVO_KeyboardColour for the settings to take effect.

pause