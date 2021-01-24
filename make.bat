@REM Compile
@REM pass --debug to frontend (-Wf--debug)
@REM pass -y to the linker to create CDB file used for debugging (-Wl-y)
@REM pass -m and -w to linker to produce "wide maps" useful for emulicious emulator
@REM can add -Wl-j if you want to create a .NOI for use in BGB emulator debugging assembly
c:\gbdk2020\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o main.o main.c
c:\gbdk2020\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb main.o
