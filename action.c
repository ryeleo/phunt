#include "action.h"
#include "log.h"

int initAction(action_t at, param_t pt, void *param, struct Action *action){
    int ret;

    ///// copy action type and param type to action
    action->paramType = pt;
    action->actionType = at;


    ///// copy the parameter
    switch(action->paramType){
        case pt_user:
            action->uid = *param;
            break;
        case pt_mem:
            action->memoryCap = *param;
            break;
        case pt_path:
            action->pathName = malloc(strnlen(param, MAX_STRLEN_FILENAME));
            strncpy(action->pathName, param, strnlen(param, MAX_STRLEN_FILENAME));
            action->pathname[MAX_STRLEN_FILENAME-1] = '\0';
            break;
        default:
            return -XXX;
    }

    return 0;
}



int actionToLog(char *out, struct Action *action){
}



int takeAction(struct Action *action){

    ///// Get snapshot of what we need in /proc that matches our criteria specified in action->param
    switch(action->paramType){
        case pt_user:
            break;
        case pt_mem:
            break;
        case pt_path:
            break;
        default:
            return -XXX;
    }


    ///// Either nice() or kill() process depending on what is required

    return 0;
}



// getUidFromUser returns the user that owns the process
static inline int getUidFromUser(str uname, int *result_pids){
}

// GetUIDFromProcess Returns the uid of the owner of the process
static inline int getUIDFromProcess(str uname, int *result_pids){
}