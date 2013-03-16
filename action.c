// 2013 - James Ingalls <james.ingalls@gmail.com>
// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "action.h"
#include "log.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

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


int initAction(action_t at, param_t pt, char *param, struct Action *action){
    int ret;

    ///// copy action type and param type to action
    action->paramType = pt;
    action->actionType = at;

    ///// copy the parameter
    switch (action->paramType){
        case pt_user:
            ret = getUidFromUser(param);
            if (ret < 0)
                return -2;
            else
                action->param.uid = ret;
            break;
        case pt_path:
            action->param.pathName = malloc(MAX_STRLEN_FILENAME);
            strncpy(action->param.pathName, param, strnlen(param, MAX_STRLEN_FILENAME));
            break;
        case pt_mem:
            ret = sscanf(param, "%d", &(action->param.memoryCap));
            if (ret != 1 || action->param.memoryCap < 0) // if we did not have a good param
                return -2;
            break;
        default:
            return -2;
    }

    return 0;
}



int actionToLog(char *out, struct Action *action){
    return 0;
}



int takeAction(struct Action *action){
    int i = 2,  // index of pid
        ret,    
        fd;
    DIR *curDir;
    char pidDirName[MAX_STRLEN_FILENAME];
    char pidStatDirName[MAX_STRLEN_FILENAME];
    char line[MAX_STRLEN_LINE];

// We want to take care of the user nice case outside of the loop because we can do that with setpriority()
    if (action->paramType == pt_nice && action->actionType == at_nice){       //nice all processes owned by a user
        ret = setpriority(PRIO_USER, action->param.uid, -20);   //nice all of user by uid (param)
        if (ret == -1)  // if setpriority failed
            return SyscallErr; 
        else 
            return 0;
    }


    while(i < PID_MAX){        //until looked at every numbered directory not beginning with '0' in /proc 
        for (; i<PID_MAX; i++) {

            ret = snprintf(pidDirName,"/proc/%d", i );
            if (ret < 0)
                return CLibCallErr;
            curDir = opendir(pidDirName);   //get proc/pid
            if (curDir == NULL){            //no directory of that number
                if (ENOENT == errno){
                    i++;
                    continue;
                }else
                    return IOErr;
            }else
                ret = closedir(pidDirName); //Close the directory cause we don't need it open
                if (ret == -1)
                    return IOErr;   //if we couldn't close the directory
                break;

        }



        switch(action->paramType){
            case pt_user:

                //get the actual location of status file of process with PID = i 
                ret = snprintf(pidStatDirName,"/proc/%d/%s", i, "status" );
                if (ret < 0)
                    return CLibCallErr;

                // 
                ret = open(pidStatDirName);
                if (ret == -1)
                    return IOErr;
                else
                    fd = ret;

                // walk through the status file until we find the line that starts with "Uid:"
                while(1){
                    ret = readline(fd, line, MAX_STRLEN_LINE);
                    if (ret < 0)
                        return IOErr;
                    ret = sscanf( line , "Uid: %d %*d %*d %*d", procUid )
                    if ( ret != 1 ) // This means that we did NOT find the line
                        continue;
                    else    // If we did find the correct line, the procUid from proc/i/status will be loaded into procUid
                        break;
                }

                // clear up system resources used in opening the file
                ret = close(fd);
                if (ret == -1)
                    return IOErr;

                // check if the procUid from the /proc/i/status file matches the action's param.uid
                if(action->param.uid == procUid){
                    switch(action->actionType){
                        // This should be taken care of before we iterate over proc, otherwise if we have a user nice case we would be setting the priority every time we look at any process
                        // case at_nice:       //nice all processes owned by a user
                            // ret = setpriority(PRIO_USER, parameter, -20);   //nice all of user by uid (parameter)
                            // if (ret == -1)  // if setpriority failed
                                // return SyscallErr; 
                            // break;
                        case at_kill:       //kill all processes owned by a user
        
                            break;
                        case at_susp:       //suspend all processes owned by the user
        
                            break;
        
                        default:
                            return -2;
        
                    }
                }else
                    continue;
    
    
                break;
            case pt_mem:    //crawl the /proc filesytem and read the memory values, then take action.
            
                switch(action->actionType){
                    case at_nice:       //nice all processes below a certain memory capacity
                        ret = setpriority(PRIO_PROCESS, i, -20);   //nice all of user by uid (paramater)
                        if (ret == -1)  // if setpriority failed
                            return SyscallErr; 
                        break;
                    case at_kill:       //kill all processes above a certain memory capacity
                        ret = kill(i, SIGKILL);
                        if(ret == -1)
                            return SyscallErr
                        break;
                    case at_susp:       //suspend all processes above a certain memory capacity
                        ret = kill(i, SIGSTOP);
                        if(ret == -1)
                            return SyscallErr
                        break;
        
                    default:
                        return -2;
        
                }
        
    
    
    
                break;
            case pt_path:
                if(){      //if current working directory of pidDirName is action->param.pathName  
                    switch(action->actionType){
                        case at_nice:       //nice all processes in a particular current working directory
                            ret = setpriority(PRIO_PROCESS, i, -20);   //nice all of user by uid (paramater)
                            if (ret == -1)  // if setpriority failed
                                return SyscallErr; 
                            break;
                        case at_kill:       //kill all processes in a particular current working directory
                            ret = kill(i, SIGKILL);
                            if(ret == -1)
                                return SyscallErr
                            break;
                        case at_susp:       //suspend all processes in a particular current working directory
                            ret = kill(i, SIGSTOP);
                            if(ret == -1)
                                return SyscallErr
                            break;
            
                        default:
                            return -2;
            
                    }
                }else
                    continue;
                        
    
    
    
                break;
            default:
                return -6;
        }
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
