@REM mod2gbt [mod file name] [-c to create .c file] [memory bank number]
mod2gbt matts_demo.mod song -c 2

@REM Compile music: output.c is created by mod2gbt
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w  -c -o output.o output.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w  -c -o gbt_player.o gbt_player.s
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w  -c -o gbt_player_bank1.o gbt_player_bank1.s


@REM you should pass --debug to frontend (Wf--debug)
@REM you should pass -y to the linker to make it create a CDB file used for debugging (-Wl-y )
@REM and also pass -m -w to the linker to produce "wide maps" that are useful for emulicious (-Wl-m)
@REM add -Wl-j if you want to create NoICE symbol file .NOI for use in BGB emulator

@echo off
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb main.o output.o gbt_player.o gbt_player_bank1.o audio_configuration.c game_configuration.c player.c scene_configuration.c

del *.o *.lst