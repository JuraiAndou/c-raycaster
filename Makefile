SOUCEDIR = src

SOURCES := $(shell find $(SOUCEDIR) -name '*.cpp')

#OBJS specifies which files to compile as part of the project
OBJS := $(SOURCES)

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LINKER_FLAGS = -lGL -lGLU -lglut
endif
ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS = -framework OpenGL -framework GLUT
endif

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = c_raycast

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME).out

