@echo off
set filename=%1
set bank=%2

if %1.==. GOTO No1
if %2.==. set bank=2

@REM @REM mod2gbt [mod file name] [-c to create .c file] [memory bank number]
music\mod2gbt music\skate_%filename%.mod song_%filename% -c %bank%

@REM @REM Compile music: output.c is created by mod2gbt. Rename to music\output_{filename}.c
move output.c music\output\output_%filename%.c

@REM Create object files with compiler for final make.bat build
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build\output\output_%filename%.o music\output\output_%filename%.c
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build\output\gbt_player.o music\gbt_player.s
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build\output\gbt_player_bank1.o music\gbt_player_bank1.s

echo Done creating output_%filename%.c

GOTO End1

:No1
    ECHO You forgot to pass in an argument ya TURKEY :)

:End1
