CC			= gcc
PROJECTDIR 	= .
CFLAGS		= -Wall
#LIBS		= 
DEBUG		= -g -DDEBUG

default: phunt

test:
	$(CC) test_log.c log.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_log

debug: CFLAGS += $(DEBUG)
debug: default

phunt: phunt.c
	$(CC) phunt.c $(CFLAGS) -o $(PROJECTDIR)/phunt

clean:
	rm -f *.o
	@rm $(PROJECTDIR)/phunt $(PROJECTDIR)/test_log

