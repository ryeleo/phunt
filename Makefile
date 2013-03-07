CC			= gcc
PROJECTDIR 	= .
CFLAGS		= -Wall
#LIBS		= 
DEBUG		= -g -DDEBUG

default: phunt

test:
	$(CC) test_util.c util.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_util
	$(CC) test_log.c log.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_log
	$(CC) test_actionlist.c actionlist.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_actionlist

debug: CFLAGS += $(DEBUG)
debug: default

phunt: phunt.c
	$(CC) phunt.c $(CFLAGS) -o $(PROJECTDIR)/phunt

clean:
	rm -f *.o
	@rm $(PROJECTDIR)/phunt $(PROJECTDIR)/test_util $(PROJECTDIR)/test_log $(PROJECTDIR)/test_actionlist
