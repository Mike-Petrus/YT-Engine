#OBJS specifies which files to compile as part of the project
OBJS = main.cpp src/Core/Engine.cpp src/Graphics/TextureManager.cpp src/Characters/Warrior.cpp src/Animation/Animation.cpp \
src/Inputs/Input.cpp src/Timer/Timer.cpp src/Map/TileLayer.cpp src/Map/MapParser.cpp src/Camera/Camera.cpp \
src/Collision/CollisionHandler.cpp \
src/Vendor/TinyXML/tinyxml.cpp src/Vendor/TinyXML/tinyxmlparser.cpp src/Vendor/TinyXML/tinyxmlerror.cpp src/Vendor/TinyXML/tinystr.cpp 

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f main main.o *.o