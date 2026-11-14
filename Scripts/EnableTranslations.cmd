@echo off

echo Enabling CLEVO Keyboard Colour translations...

reg add HKCU\Software\CLEVO_KeyboardColour /v EnableTranslations /t REG_DWORD /d 1 /f

echo Translations are ENABLED. Restart CLEVO_KeyboardColour for the settings to take effect.

pause