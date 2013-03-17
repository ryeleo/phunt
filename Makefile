CC			= gcc
PROJECTDIR 	= .
CFLAGS		= -Wall
#LIBS		= 
DEBUG		= -g -DDEBUG

default: phunt

test_util:
	$(CC) test_util.c util.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_util

test_log:
	$(CC) test_log.c log.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_log

test_action:
	$(CC) test_action.c action.c util.c log.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_action

test_actionlist:
	$(CC) test_actionlist.c actionlist.c util.c action.c $(CFLAGS) -g -DDEBUG -o $(PROJECTDIR)/test_actionlist

debug: CFLAGS += $(DEBUG)
debug: test_action

phunt: phunt.c
	$(CC) phunt.c actionlist.c action.c util.c log.c $(CFLAGS) -o $(PROJECTDIR)/phunt

clean:
	rm -f *.o
	@ rm $(PROJECTDIR)/phunt $(PROJECTDIR)/test_util $(PROJECTDIR)/test_log $(PROJECTDIR)/test_actionlist $(PROJECTDIR)/test_action 
