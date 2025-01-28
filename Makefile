SOUCEDIR = src

SOURCES := $(shell find $(SOUCEDIR) -name '*.cpp')

#OBJS specifies which files to compile as part of the project
OBJS := $(SOURCES:.cpp=.o)


#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = c_raycast

#LINKER_FLAGS specifies the libraries we're linking against
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LINKER_FLAGS = -lGL -lGLU -lglut
endif
ifeq ($(UNAME_S),Darwin)
	LINKER_FLAGS = -framework OpenGL -framework GLUT
endif


#This is the target that compiles our executable
all : $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(LINKER_FLAGS) 

%.o: %.cpp
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJ_NAME)

