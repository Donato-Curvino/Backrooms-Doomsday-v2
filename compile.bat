@echo off
windres src/addIcon.rc -O coff -o bin/build/my.res

IF %1 EQU export GOTO :Export

g++ -o bin/BackroomsDoomsdayTST.exe -std=c++17 -static-libgcc -static-libstdc++ -gdwarf-2 ^
    src/BackroomsDoomsday.cpp src/engine/*.cpp src/components/*.cpp bin/build/my.res ^
    -lsfml-window -lsfml-system -lsfml-graphics

@REM g++ -o bin/BackroomsDoomsdayTST.exe -mwindows -static-libgcc -static-libstdc++ -gdwarf-2 src/BackroomsDoomsday.cpp bin/build/my.res -lsfml-window -lsfml-system -lsfml-graphics

IF %ERRORLEVEL% NEQ 0 Goto :Done
    cd bin
    BackroomsDoomsdayTST.exe
    cd ..
Goto :Done

:Export
    g++ -o bin/BackroomsDoomsday.exe -DSFML_STATIC -std=c++17 -static-libgcc -static-libstdc++ -static ^
        src/BackroomsDoomsday.cpp src/engine/*.cpp src/components/*.cpp bin/build/my.res ^
        -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lopengl32 -lgdi32 -lfreetype 
    cd bin
    zip -r BackroomsDoomsdayFull.zip BackroomsDoomsday.exe assets/*
    cd ..

:Done
