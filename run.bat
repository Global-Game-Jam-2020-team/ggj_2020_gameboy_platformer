@REM kill open instance of BGB
taskkill /f /im javaw.exe

@REM start up bgb with latest compiled .gb
start /b C:\Users\mattm\Games\emulicious\emulicious.exe %cd%\main.gb
