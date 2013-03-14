// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
/* 
ActionList offers a way to load from a predefined .conf file with the format
following the structure of this example:

    # Comments are started with hashes
    # <action_type>    <param_type>    <param>
    kill user badguy
    nice user     butler

    # Extra spaces are ignored

Further, the action list gives the ability to continuously cycle through actions
from the begining to the end. The prototype for how to do this is printed below.

// How to iterate through the actionList
struct ActionList *pal = p_actionList;
struct Action *p_action;
do{
    getAction(&p_action, &pal);
    nextAction(&pal);
    printf("%d, %d\n", p_action->actionType, p_action->paramType);
} while ( pal != p_actionList );

*/
#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__


#include "action.h"


#define MAX_STRLEN_FILENAME 256
#define MAX_BYTELEN_BUFFER 1024


struct ActionList{
    struct Action action;   // The action that this node of the actionList contains
    struct ActionList 
        *next,  // points to the next actionList
        *prev,  // points to the prev actionList
        *head;  // points to the inital actionList
};



/*
Description: Initialize actionList from the file provided in fileName. Assumes that
the provided actionList item is established already.

fileName: The config file to load from.
actionList: The struct ActionList to be initialized, should not point to anything initially.

Return: 0 upon success
-2 if a parameter passed was null
-3 if we run into a programming error
-4 upon IO Error
-7 if error while parsing file
*/
int initActionList(char *fileName, struct ActionList **actionList);



/*
Description: Inserts the provided action into a struct ActionList. The actionList
will append action immidiately after actionList, then update actionList to point 
to the newly inserted action.

action: The action to be inserted to the actionList.
actionList: The actionList which will be modified.

Return: 0 upon success
-1 if unable to malloc memory for actionList structure
-2 if null parameters passed
*/
int insertAction(struct Action *action, struct ActionList **actionList);




/*
Description: Get the next action from the action list, without removing any elements
from the list.
NOTICE: We pass back a reference to the action, not a copy of it.

retAction: A pointer which will point internal to the data structure to the
action asked for.
actionList: The actionList to be pulled from

Return: 0 upon success,
-2 if null parameters passed
*/
int getAction(struct Action **retAction, struct ActionList **actionList);



/*
Description: Simply updates this actionList to point at the next action in the
list. This should generally be called in juncture with getAction().

actionList: The actionList which will be updated to point to the next element in the List.

Return: 0 upon success,
-2 if null parameters passed
*/
int nextAction(struct ActionList **actionList);

/*
Description: Free all elements from actionList which were inserted using the 
insertAction method. This should be called when we are done using actionList,
and will result in actionList being a NULL pointer.

actionList: the actionList to be freed.

Return: 0 upon success,
-2 if null parameter
*/
int freeActionList(struct ActionList **actionList);

#endif//__ACTIONLIST_H__
