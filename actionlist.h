/* 
2013 - Ryan Leonard <ryan.leonard71@gmail.com>
ActionList offers a way to load from a predefined .conf file with the format
following the structure of this example:

    # Comments are started with hashes
    # <action_type> <param_type> <param>
    kill user badguy

    # Extra spaces are ignored
*/
#include "action.h"


#define MAX_BYTELEN_BUFFER 1024


struct ActionList{
    struct Action action;
    struct ActionList *next;
};



/*
Description: Initialize actionList from the file provided in fileName.

Return: 
*/
int initActionList(char *fileName, struct ActionList *actionList);



/*
Description: 

Return: 
*/
int insertAction(struct Action *action, struct ActionList *actionList);




/*
Description: Get the next action from the action list, in a queue like fashion,
but never actually removing any elements from the action.
NOTE: We pass back a reference to the action, not a copy of it.

Return: 
*/
int getAction(struct Action *retAction, struct ActionList *actionList);



/*
Description: Simply updates this actionList to point at the next action in the
list. This should generally be called in juncture with getAction().

Return: 
*/
int nextAction(struct ActionList *actionList);
