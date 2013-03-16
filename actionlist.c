// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
// 2013 - James Ingalls <james.ingalls@gmail.com>

#include "util.h"
#include "action.h"
#include "actionlist.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int initActionList(char *fileName, struct ActionList **actionList){
    int ret;
    int fd;
    int lineLen;
    char line[MAX_BYTELEN_BUFFER];
    char paramTypeStr[MAX_BYTELEN_BUFFER];
    char actionTypeStr[MAX_BYTELEN_BUFFER];
    char paramStr[MAX_BYTELEN_BUFFER];
    action_t action_type;
    param_t  param_type;
    struct Action action;

    // Make sure params are not null
    if (fileName == NULL || actionList == NULL)
        return NullParamErr;

    // assure that the actionList is initialized to null
    (*actionList) = NULL;

    ///// Parse the provided config file, adding all of the actions to actionList
    // Open fileName 
    ret = open(fileName, O_RDONLY);
    if (ret == -1)
        return IOErr;
    else
        fd = ret;

    // Parse the file line-by-line
    while(1){
        // Read next line of file
        lineLen = readLine(fd, line, MAX_BYTELEN_BUFFER);
        if (lineLen == -1)
            return IOErr;// indicates that there was read error
        else if (lineLen == -6)
            break;      // indicates that we are done reading from the file
        else if (lineLen == 0)
            continue;   // indicates that this line is blank

        // If line begins with '#', ignore it
        if (line[0] == '#')
            continue;
        
        // Scan the line into its parts
        ret = sscanf(line, "%s %s %s", actionTypeStr, paramTypeStr, paramStr);
        if (ret != 3)
            return ParseFileErr;  // indicates broken config file

        // Get the action type...
        ret = getActionType(actionTypeStr);
        if (ret == NullParamErr)
            return ParseFileErr; // indicates broken config file
        else
            action_type = ret;

        // ... the param type... 
        ret = getParamType(paramTypeStr);
        if (ret == NullParamErr)
            return ParseFileErr; // indicates broken config file
        else
            param_type = ret;

        // Create a new action
        ret = initAction(action_type, param_type, paramStr, &action);
        if (ret == NullParamErr)
            return ParseFileErr; // indicates broken config file

        // Insert it into actionList
        ret = insertAction(&action, actionList);
        if (ret < 0)
            return CodeErr; // indicates that something went wrong in programming this function...
    }

    // intuatively, the returned pointer should point to the head of the list
    *actionList = (*actionList)->head;
    return NoneErr;
}


int insertAction(struct Action *action, struct ActionList **actionList){
    struct ActionList *newActionListItem;

    // Make sure that params aren't null
    if (actionList == NULL || action == NULL)
        return NullParamErr;

    // make space for newActionListItem
    newActionListItem = malloc(sizeof(struct ActionList));
    if (newActionListItem == NULL)
        return MemErr;

    // insert contents of new action
    memcpy(&newActionListItem->action, action, sizeof(struct Action));

    ///// adjust pointers in list to hold new action
    // if we are the first guy on the block, set next to ourself
    if ((*actionList) == NULL){
        newActionListItem->next = newActionListItem;
    }else{ // default case
        newActionListItem->next = (*actionList)->next;
        (*actionList)->next->prev = newActionListItem;
    }

    // if we are the first guy on the block, set prev to ourself
    if ((*actionList) == NULL){
        newActionListItem->prev = newActionListItem;
    }else{ // default case
        newActionListItem->prev = (*actionList);
        (*actionList)->next = newActionListItem;
    }

    // if we are first guy on the block, set head to ourself also
    if ((*actionList) == NULL){
        newActionListItem->head = newActionListItem;
    }else{ // default case
        newActionListItem->head = (*actionList)->head;
    }

    // finally, set actionList to point to the newly inserted action.
    (*actionList) = newActionListItem;

    return NoneErr;
}



int getAction(struct Action **retAction, struct ActionList **actionList){
    // Make sure that params aren't null
    if (actionList == NULL)
        return NullParamErr;

    ///// Set retAction to the action provided by the list
    (*retAction) = &((*actionList)->action);    
    return NoneErr;
}



int nextAction(struct ActionList **actionList){
    // Make sure that params aren't null
    if (actionList == NULL)
        return NullParamErr;

    ///// Simply update actionList to point to the next element.
    (*actionList) = (*actionList)->next;

    return NoneErr;
}



int freeActionList(struct ActionList **actionList){
    // a temporary pointer for deleting items
    struct ActionList *ptrActionList;

    // Make sure that params aren't null
    if (actionList == NULL)
        return NullParamErr;

    // Step through each actionListItem and free it
    struct ActionList *pal = *actionList;
    do{
        // free any memory allocated by the action
        freeAction(& (pal->action));

        // free the action list item
        ptrActionList = pal;
        nextAction(&pal);
        free(ptrActionList);
    } while ( pal != *actionList );
    *actionList = NULL;

    return NoneErr;
}
