@echo off

windres src/addIcon.rc -O coff -o bin/build/my.res
g++ -o bin/BackroomsDoomsdayTST.exe -static-libgcc -static-libstdc++ -gdwarf-2 ^
    src/BackroomsDoomsday.cpp src/engine/Map.cpp bin/build/my.res ^
    -lsfml-window -lsfml-system -lsfml-graphics

@REM g++ -o bin/BackroomsDoomsdayTST.exe -mwindows -static-libgcc -static-libstdc++ -gdwarf-2 src/BackroomsDoomsday.cpp bin/build/my.res -lsfml-window -lsfml-system -lsfml-graphics

IF %ERRORLEVEL% NEQ 0 Goto :Done
cd bin
BackroomsDoomsdayTST.exe
cd ..

:Done
