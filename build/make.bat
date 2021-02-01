@echo off

@REM you should pass --debug to frontend (Wf--debug)
@REM you should pass -y to the linker to make it create a CDB file used for debugging (-Wl-y )
@REM and also pass -m -w to the linker to produce "wide maps" that are useful for emulicious (-Wl-m)
@REM add -Wl-j if you want to create NoICE symbol file .NOI for use in BGB emulator

@REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o build\main.o main.c
@REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb build\output\output_intro.o build\output\output_outro.o build\output\output_gameplay.o build\main.o build\output\gbt_player.o build\output\gbt_player_bank1.o audio_configuration.c music_configuration.c game_configuration.c player.c scene_configuration.c sprites\Skater.c sprites\SpiritSkater.c sprites\MiscAssets.c sprites\LongSkateBackground.c sprites\LongSkateBgTiles.c 

c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build\main.o main.c
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -o Rolling_On.gb build\output\output_intro.o build\output\output_gameplay.o build\main.o build\output\gbt_player.o build\output\gbt_player_bank1.o music_configuration.c game_configuration.c player.c scene_configuration.c sprites\Skater.c sprites\SpiritSkater.c sprites\MiscAssets.c sprites\LongSkateBackground.c sprites\LongSkateBgTiles.c 

@REM Below files have been removed from compilation 
@REM   build\output\output_outro.o audio_configuration.c

del build\*.o build\*.lst build\*.adb build\*.asm build\*.sym
