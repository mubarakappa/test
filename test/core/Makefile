#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Render.cpp Console.cpp EventManager.cpp Map.cpp Game.cpp
#BUILD_DIR specifies where to build the exectuable
BUILD_DIR := "../Test"


#This is the target that compiles our executable
#-Wl,-subsystem,windows args that disable console
all : $(OBJS)
	g++ $(OBJS) -IC:\DEVOPS\SDL2-MINGW-32\include\SDL2 -LC:\DEVOPS\SDL2-MINGW-32\lib -w -lmingw32 -lSDL2main -lSDL2 -o $(BUILD_DIR)
