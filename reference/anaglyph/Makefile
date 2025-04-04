
EXEC = anaglyph
CC = gcc
CFLAGS = -O2\
	-Wall\
	-pedantic\
	-ffast-math\
	-I/usr/X11R6/include
LFLAGS = -L/usr/X11R6/lib
LIBS = -lm -lGL -lglut -lGLU -lX11 -lXmu -lXi
OBJS = anaglyph.o

all:: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS) $(LIBS)

clean::
	-rm -f $(EXEC) *.o core tags
