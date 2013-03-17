2013
Ryan Leonard
James Ingalls

Submitted Source Files:
phunt.c
action.h
action.c
actionlist.h
actionlist.c
log.h
log.c
util.h
util.c

Type "make" to compile the code. Type "make clean" to remove the compiled files. 

Work accomplished:
Created the phunt program as described. It is capable of parsing a config file, and performing all specified actions. It can also be run as a daemon by using the "-d" flag.

Descrption of Code and Layout:

The code is broken up into a few files for simplicity. phunt is the main program which parses the input and config file, and creates the actionlist as described in actionlist.c to be sent to action.c to be acted on. util.c contains a method to read in a line of a file, used in parsing the config (in actionlist.c) as well as the /proc filesystem in (action.c), and a method for handling our descriptive errors for debugging purposes used throughout.

action.c  is comprised 

We would both like to use one grace day each for this assignment.

We are assuming for the case of memory ceiling actions, that we will not kill or suspend unless the process EXCEEDS the ceiling. This also means that if it is actually equal to the ceiling we will nice for memory nice rules.


