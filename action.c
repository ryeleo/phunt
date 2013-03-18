// 2013 - James Ingalls <james.ingalls@gmail.com>
// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "action.h"
#include "log.h"
#include "util.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <signal.h>

// We must have a global log in order to takeAction().
struct Log *log;

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
            action->param.memoryCap = action->param.memoryCap * 1024;   //get the memory cap in kB
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
    int i,  // index of pid
        ret,    
        fd,
        procUid,
        procVmRSS;
    DIR *curDir;
    char pidDirName[MAX_STRLEN_FILENAME];
    char pidStatDirName[MAX_STRLEN_FILENAME];
    char line[MAX_STRLEN_LINE];
    char procCWD[MAX_STRLEN_FILENAME];
    char pidCWDDirName[MAX_STRLEN_FILENAME];


    // we actually initialize the value of i to 1 below
    i = 0;
    while(i < PID_MAX){        //until looked at every numbered directory not beginning with '0' in /proc 
        // walk through the /proc file structure until we find a valid pid
        i++;
        for (; i<PID_MAX; i++) {

            // put together the full path for a pid
            ret = snprintf(pidDirName, MAX_STRLEN_FILENAME, "/proc/%d", i);
            if (ret < 0)
                return CLibCallErr;

            curDir = opendir(pidDirName);   //get proc/pid

            if (curDir == NULL){            //no directory of that number
                if (ENOENT == errno)
                    continue;
                else
                    return IOErr;
            }else{  // There is a pid 'i'!
                ret = closedir(curDir); //Close the directory cause we don't need it open
                if (ret == -1)
                    return IOErr;   //if we couldn't close the directory
#ifdef DEBUG
                printf("Pid Path Chosen:    %s\n", pidDirName);
#endif//DEBUG
                break;
            }
        }

        switch(action->paramType){
            case pt_user:

                //get the actual location of status file of process with PID = i 
                ret = snprintf(pidStatDirName, MAX_STRLEN_FILENAME, "/proc/%d/%s", i, "status" );
                if (ret < 0)
                    return CLibCallErr;

                // open the status file
                ret = open(pidStatDirName, O_RDONLY);
                if (ret == -1)
                    return IOErr;
                else
                    fd = ret;

                // walk through the status file until we find the line that starts with "Uid:"
                while(1){
                    ret = readLine(fd, line, MAX_STRLEN_LINE);
                    if (ret < 0)
                        return IOErr;
                    ret = sscanf( line , "Uid: %d %*d %*d %*d", &procUid);
                    if ( ret != 1 ) // This means that we did NOT find the line
                        continue;
                    else{    // If we did find the correct line, the procUid from proc/i/status will be loaded into procUid
                        break;
                    }
                }

                // clear up system resources used in opening the file
                ret = close(fd);
                if (ret == -1)
                    return IOErr;
#ifdef DEBUG
                printf("UID:        %d\n", procUid);
                printf("Action_UID: %d\n", action->param.uid);
#endif//DEBUG
                // check if the procUid from the /proc/i/status file matches the action's param.uid
                if(action->param.uid == procUid){
                    switch(action->actionType){
                        case at_nice:    //nice all processes owned by a user
                            ret = setpriority(PRIO_PROCESS, i, -20);   //nice all of user by uid (parameter)
                            if (ret == -1)  // if setpriority failed
                                return SyscallErr; 
                            // XXX LOG
                            break;

                        case at_kill:       //kill all processes owned by a user
                            ret = kill(i, SIGKILL);
                            if(ret == -1)
                                return SyscallErr;
                            // XXX LOG
                            break;

                        case at_susp:       //suspend all processes owned by the user
                            ret = kill(i, SIGSTOP);
                            if(ret == -1)
                                return SyscallErr;
                            // XXX LOG
                            break;

                        default:
                            return -2;
                    }
                }else
                    continue;
    
    
                break;
            case pt_mem:    //crawl the /proc filesytem and read the memory values, then take action.
                //get the actual location of status file of process with PID = i 
                ret = snprintf(pidStatDirName, MAX_STRLEN_FILENAME, "/proc/%d/%s", i, "status" );
                if (ret < 0)
                    return CLibCallErr;

                // 
                ret = open(pidStatDirName, O_RDONLY);
                if (ret == -1)
                    return IOErr;
                else
                    fd = ret;

                // walk through the status file until we find the line that starts with "Uid:"
                while(1){
                    ret = readLine(fd, line, MAX_STRLEN_LINE);
                    if (ret < 0)
                        return IOErr;
                    ret = sscanf(line, "VmRSS: %d kB", &procVmRSS);
                    if ( ret != 1 ) // This means that we did NOT find the line
                        continue;
                    else    // If we did find the correct line, the procUid from proc/i/status will be loaded into procUid
                        break;
                }

                // clear up system resources used in opening the file
                ret = close(fd);
                if (ret == -1)
                    return IOErr;
#ifdef DEBUG
                printf("VmRSS:        %d\n", procVmRSS);
                printf("Action_Mem:   %d\n", action->param.memoryCap);
#endif//DEBUG

                switch(action->actionType){
                    case at_nice:       //nice all processes below a certain memory capacity
                        
                        if (procVmRSS <= action->param.memoryCap){

                            ret = setpriority(PRIO_PROCESS, i, -20);   //nice all of user by uid (parameter)
                            if (ret == -1)  // if setpriority failed
                                return SyscallErr; 
                            // XXX LOG
                        }

                        break;
                    case at_kill:       //kill all processes above a certain memory capacity
                        
                        if (procVmRSS > action->param.memoryCap){
                            ret = kill(i, SIGKILL);
                            if(ret == -1)
                                return SyscallErr;
                            // XXX LOG
                        }
                        break;
                    case at_susp:       //suspend all processes above a certain memory capacity
                        
                        if (procVmRSS > action->param.memoryCap){
                            ret = kill(i, SIGSTOP);
                            if(ret == -1)
                                return SyscallErr;
                            // XXX LOG
                        }
                        break;
        
                    default:
                        return -2;
        
                }
        
    
    
    
                break;
            case pt_path:
                ret = snprintf(pidCWDDirName, MAX_STRLEN_FILENAME, "/proc/%d/%s", i, "cwd" );
                if (ret < 0)
                    return CLibCallErr;

                ret = readlink(pidCWDDirName, procCWD, MAX_STRLEN_FILENAME );
                if (ret < 0 )
                    return CLibCallErr;
#ifdef DEBUG
                printf("CWS:          %s\n", procCWD);
                printf("Action_CWD:   %s\n", action->param.pathName);
#endif//DEBUG

                if(strncmp(procCWD, action->param.pathName, MAX_STRLEN_FILENAME) == 0){      //if current working directory of pidDirName is action->param.pathName  
                    switch(action->actionType){
                        case at_nice:       //nice all processes in a particular current working directory
                            ret = setpriority(PRIO_PROCESS, i, -20);   //nice all of user by uid (parameter)
                            if (ret == -1)  // if setpriority failed
                                return SyscallErr; 
                            // XXX LOG
                            break;
                        case at_kill:       //kill all processes in a particular current working directory
                            ret = kill(i, SIGKILL);
                            if(ret == -1)
                                return SyscallErr;
                            // XXX LOG
                            break;
                        case at_susp:       //suspend all processes in a particular current working directory
                            ret = kill(i, SIGSTOP);
                            if(ret == -1)
                                return SyscallErr;
                            // XXX LOG
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
