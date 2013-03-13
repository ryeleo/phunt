/* 
2013 - Ryan Leonard <ryan.leonard71@gmail.com>
ActionList offers a way to load from a predefined .conf file with the format
following the structure of this example:

    # Comments are started with hashes
    # <action_type> <param_type> <param>
    kill user badguy

    # Extra spaces are ignored

Further, the action list gives the ability to continuously cycle through actions
from the begining to the end.
*/
#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__


#include "action.h"


#define MAX_STRLEN_FILENAME 256
#define MAX_BYTELEN_BUFFER 1024


struct ActionList{
    struct Action action;
    struct ActionList 
        *next,  // points to the next actionList
        *prev,  // points to the prev actionList
        *head;  // points to the inital actionList
};



/*
Description: Initialize actionList from the file provided in fileName. Assumes that
the provided actionList item is established already.

Return: 0 upon success
*/
int initActionList(char *fileName, struct ActionList **actionList);



/*
Description: Inserts the provided action into actionList.

Return: 0 upon success
*/
int insertAction(struct Action *action, struct ActionList **actionList);




/*
Description: Get the next action from the action list, without removing any elements
from the list.
NOTICE: We pass back a reference to the action, not a copy of it.

Return: 0 upon success,
*/
int getAction(struct Action **retAction, struct ActionList **actionList);



/*
Description: Simply updates this actionList to point at the next action in the
list. This should generally be called in juncture with getAction().

Return: 0 upon success
*/
int nextAction(struct ActionList **actionList);

/*
Description: Free all elements from actionList which were inserted using the 
insertAction method. This should be called when we are done using actionList,
and will result in actionList being a NULL pointer.

Return:
*/
int freeActionList(struct ActionList **actionList);

#endif//__ACTIONLIST_H__
