CC			= gcc
PROJECTDIR 	= .
CFLAGS		= -Wall
#LIBS		= 
DEBUG		= -g -DDEBUG

default: phunt

debug: CFLAGS += $(DEBUG)
debug: default

uoenc: phunt.c
	$(CC) phunt.c $(CFLAGS) -o $(PROJECTDIR)/phunt

clean:
	rm -f *.o
	rm $(PROJECTDIR)/phunt

