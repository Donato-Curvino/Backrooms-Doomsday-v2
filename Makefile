ifeq ($(OS), Windows_NT)
	DEBUG_FLAGS=-static-libgcc -static-libstdc++ -gdwarf-2
	FILE_EXTENSION=.exe
else
	DEBUG_FLAGS=-g
	FILE_EXTENSION=.out
endif

test:
	g++ -o bin/BackroomsDoomsdayTST$(FILE_EXTENSION) $(DEBUG_FLAGS) src/BackroomsDoomsday.cpp -lsfml-window -lsfml-system -lsfml-graphics
