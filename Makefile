CC = g++
CFLAGS = -Wall
PROG = Game

SRCS = headerFiles.h world.h camera.h block.h humanoid.h vec3f.cpp  text.h md2model.cpp imageloader.cpp main.cpp
LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
