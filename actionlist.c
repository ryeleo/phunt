// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
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
    Parameter a_param;
    struct Action action;


    ///// Set all of the pointers to null
    actionList->prev = NULL;
    actionList->next = NULL;
    actionList->head = NULL;


    ///// Parse the provided config file, adding all of the actions to actionList
    // Open fileName 
    ret = open(fileName, O_RDONLY);
    if (ret == -1)
        return -4;
    else
        fd = ret;

    // Parse the file line-by-line
    while(1){
        // Read next line of file
        lineLen = readLine(fd, line, MAX_BYTELEN_BUFFER);
        if (lineLen == -1)
            return -4;// indicates that there was read error
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
            return -4;  // indicates that something went wrong in IO

        // Get the action type...
        ret = getActionType(actionTypeStr);
        if (ret == -2)
            return -4; // indicates that something went wrong in IO
        else
            action_type = ret;

        // ... the param type... 
        ret = getParamType(paramTypeStr);
        if (ret == -2)
            return -4; // indicates that something went wrong in IO
        else
            param_type = ret;

        // ... and the paramater
        ret = getParam(param_type, paramStr, &a_param);
        if (ret == -2)
            return -4; // indicates that something went wrong in IO

        // Create a new action
        initAction(action_type, param_type, &a_param, &action);

        // Insert it into actionList
        insertAction(&action, actionList);
    }

    return 0;
}


int insertAction(struct Action *action, struct ActionList **actionList){
    struct Action *newAction;
    struct ActionList *newActionListItem;

    // Make sure that params aren't null
    if (*actionList == NULL || action == NULL)
        return -2;

    ///// malloc space for new action
    newAction = malloc(sizeof(struct Action));

    ///// insert contents of new action
    memcpy(newAction, action, sizeof(struct Action));


    ///// adjust pointers in list to hold new action
    // make space for newActionListItem
    newActionListItem = malloc(sizeof(struct ActionList));

    // if we are the first guy on the block, set next to ourself
    if ((*actionList)->next == NULL)
        newActionListItem->next = newActionListItem;
    else
        newActionListItem->next = (*actionList)->next;

    // if we are the first guy on the block, set prev to ourself
    if ((*actionList)->prev == NULL)
        newActionListItem->prev = newActionListItem;
    else
        newActionListItem->prev = (*actionList);

    // if we are first guy on the block, set head to ourself also
    if ((*actionList)->head == NULL)
        newActionListItem->head = newActionListItem;
    else
        newActionListItem->head = (*actionList)->head;

    // finally, set actionList to point to the newly inserted action.
    (*actionList) = newActionListItem;

    return 0;
}



int getAction(struct Action *retAction, struct ActionList **actionList){
    // Make sure that params aren't null
    if (actionList == NULL)
        return -2;

    ///// Set retAction to the action provided by the list
    retAction = &actionList->action;    
    return 0;
}



int nextAction(struct ActionList **actionList){
    // Make sure that params aren't null
    if ((*actionList) == NULL || (*actionList)->next == NULL)
        return -2;

    ///// Simply update actionList to point to the next element.
    (*actionList) = (*actionList)->next;

    return 0;
}



int freeActionList(struct ActionList **actionList){
    struct ActionList *ptrActionList;

    // Make sure that params aren't null
    if ((*actionList) == NULL)
        return -2;

    // Step through each actionListItem and free it
    while((*actionList)->next != (*actionList)){
        // free the action
        freeAction(&((*actionList)->action);

        // free the action list
        ptrActionList = *actionList;
        nextAction(actionList);
        free(ptrActionList);
    }
    freeAction(&((*actionList)->action));
    free(*actionList);
    *actionList = NULL;
    return 0;
}
