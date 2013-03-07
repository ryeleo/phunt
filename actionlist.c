// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "util.h"
#include "actionlist.h"
#include <unistd.h>



int initActionList(char *fileName, struct ActionList *actionList){
    int ret;
    int fd;
    int lineLen;
    char line[MAX_BYTELEN_BUFFER];
    char param[MAX_BYTELEN_BUFFER];
    action_t action_type;
    param_t  param_type;
    void *param;


    ///// Parse the provided config file, adding all of the actions to actionList
    // Open fileName 
    ret = open(fileName, O_RDWR | O_APPEND | O_CREAT, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (ret == -1)
        return -4;
    else
        fd = ret;

    // Parse the file line-by-line
    while(1){
        // Read next line of file
        lineLen = readLine(fd, line, MAX_BYTELEN_BUFFER);
        if (lineLen == -1)
            return -XXX;// indicates that there was read error
        else if (lineLen == 0)
            break;      // indicates that we are done reading from the file

        // Get the action type, the param type, and the paramater
        sscanf(line, "%d %d %s", &action_t, &param_t, param);
        switch (param_t){
            case pt_user:
                // TODO Check that this works
                sscanf(param, "%d", *param);
                break;
            case pt_path:
                // param = param... don't do anything
                break;
            case pt_mem:
                // TODO Check that this works
                sscanf(param, "%d", *param);
                break;
            default:
                return -XXX;
        }

        // Create a new action
        initAction(action_type, param_type, (void*) param, action);

        // Insert it into actionList
        insertAction(action, actionList);
    }

    return 0;
}

int getAction(struct Action *retAction, struct ActionList *actionList){
    // Make sure that params aren't null
    if (actionList == NULL || actionList.next == NULL)
        return -2;

    ///// Set retAction to the action provided by the list
    retAction = actionList.action;    
    return 0;
}



int nextAction(struct ActionList *actionList){
    // Make sure that params aren't null
    if (actionList == NULL || actionList.next == NULL)
        return -2;

    ///// Simply update actionList to point to the next element.
    actionList = actionList.next;

    return 0;
}
