/* 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
   2013 - James Ingalls <james.ingalls@gmail.com>
action.c provides an implmentation of a process manager based on the /proc/ 
filesystem. This is also based on the idea of taking an "action" on a subset of
processes that have a certain "attribute." The attributes are currently as
follows:
-Path: processes using ths provided path as CWD
-User: processes with the provided user
-Memory Usage: processes with the memory ceiling (in MB)

The actions that can be taken on the above stated items are:
-nice
-suspend
-kill
*/

#define MAX_STRLEN_FILENAME 256

// Defines the types of actions that can be taken
typedef action_t short;
#define at_kill 0
#define at_susp 1
#define at_nice 2

// Defines the types of parameters that may be passed
typedef param_t short;
#define pt_user 0
#define pt_path 1
#define pt_mem  2

struct Action{
    action_t actionType;
    param_t paramType;
    union{
        char *pathName;
        int uid;
        int memoryCap; // in kiloBytes
    }; //parameter passed
};



/*
This will simply initialize all of the fields in the action struct.
//XXX To map users to UID, use /etc/passwd

type: The type of action which will be taken.
param: Depending on the type, this will be parsed accordingly.
Return: 0 upon success,
*/
int initAction(action_t at, param_t pt, void *param, struct Action *action);



/*
Description: Given an action, enforce that action.
Note: We have to keep this method as low overhead as possible. This should also 
be reflected in any methods that takeAction calls.

Additionally, to 
enforce that we never reach an accidental infinite loop, get a snapshot of the 
/proc/ filesystem
takeAction will be very regularly called so assuring that there is greatest
efficiancy here is of interest. This function will have to look at the /proc
filesystem every time it runs.
-Is there any way to have this set-up with persistant open filedescriptors with
RO Access
*/
int takeAction(struct Action *action);
