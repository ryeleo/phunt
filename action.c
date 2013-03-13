// 2013 - James Ingalls <james.ingalls@gmail.com>
// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "action.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// We must have a global log in order to takeAction().
extern struct Log *log;

const char *actionStrings[3] = {
    "kill",
    "suspend",
    "nice"
};
const char *paramStrings[3] = {
    "user",
    "path",
    "memory"
};


int initAction(action_t at, param_t pt, Parameter *param, struct Action *action){

    ///// copy action type and param type to action
    action->paramType = pt;
    action->actionType = at;


    ///// copy the parameter
    switch(action->paramType){
        case pt_user:
            action->param.uid = param->uid;
            break;
        case pt_mem:
            action->param.memoryCap = param->memoryCap;
            break;
        case pt_path:
            action->param.pathName = malloc(strnlen(param->pathName, MAX_STRLEN_FILENAME));
            strncpy(action->param.pathName, param->pathName, strnlen(param->pathName, MAX_STRLEN_FILENAME));
            action->param.pathName[MAX_STRLEN_FILENAME-1] = '\0';
            break;
        default:
            return -2;  // Indicates incorrect parameter passed
    }   

    return 0;
}



int actionToLog(char *out, struct Action *action){
    return 0;
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
            return -6;
    }


    ///// Either nice() or kill() process depending on what is required

    return 0;
}


int getParam(param_t param_type, char *param, Parameter *ret_param){
    int ret;
    switch (param_type){
        case pt_user:
            ret = getUidFromUser(param);
            if (ret > 0)
                return -2;
            else
                ret_param->uid = ret;
            break;
        case pt_path:
            ret_param->pathName = malloc(MAX_STRLEN_FILENAME);
            strncpy(ret_param->pathName, param, strnlen(param, MAX_STRLEN_FILENAME));
            break;
        case pt_mem:
            sscanf(param, "%d", &(ret_param->memoryCap));
            break;
        default:
            return -2;
    }

    return 0;
}

param_t getParamType(char *paramTypeStr){
    if ( 0 == strncmp(paramTypeStr, paramStrings[pt_user], MAX_STRLEN_FILENAME) )    
        return pt_user;
    else if ( 0 == strncmp(paramTypeStr, paramStrings[pt_path], MAX_STRLEN_FILENAME) )    
        return pt_path;
    else if ( 0 == strncmp(paramTypeStr, paramStrings[pt_mem], MAX_STRLEN_FILENAME) )    
        return pt_mem;
    else
        return -2;
}

action_t getActionType(char *actionTypeStr){
    if ( 0 == strncmp(actionTypeStr, actionStrings[at_kill], MAX_STRLEN_FILENAME) )    
        return at_kill;
    else if ( 0 == strncmp(actionTypeStr, actionStrings[at_susp], MAX_STRLEN_FILENAME) )    
        return at_susp;
    else if ( 0 == strncmp(actionTypeStr, actionStrings[at_nice], MAX_STRLEN_FILENAME) )    
        return at_nice;
    else
        return -2;
}

int freeAction(struct Action *action){
    if (action->paramType == pt_path)
        free(action->param.pathName);
    return 0; 
}




// getUidFromUser returns the uid given a username
int getUidFromUser(char *uname){
    // #include <sys/types.h>
    // #include <pwd.h>
    // man 3 getpwnam
    // struct passwd *getpwnam(const char *name);
    return 0;
}

// GetUIDFromProcess Returns the uid of the owner of the process
int getUIDFromProcess(char *uname){
    return 0;
}
