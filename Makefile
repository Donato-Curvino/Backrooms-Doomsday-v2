ifeq ($(OS), Windows_NT)
	DEBUG_FLAGS=-static-libgcc -static-libstdc++ -gdwarf-2
	FILE_EXTENSION=.exe
else
	DEBUG_FLAGS=-g -fsanitize=address,undefined
	FILE_EXTENSION=.out
endif

FILES=src/*.cpp src/engine/*.cpp src/components/*.cpp

test:
	g++ -o bin/BackroomsDoomsdayTST$(FILE_EXTENSION) $(DEBUG_FLAGS) $(FILES) -lsfml-window -lsfml-system -lsfml-graphics
	bash -c "cd $(CURDIR)/bin && ./BackroomsDoomsdayTST$(FILE_EXTENSION)"
