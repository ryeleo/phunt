// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "util.h"
#include "action.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    struct Action 
        nice_mem_action,
        nice_usr_action,
        nice_pth_action,
        kill_mem_action,
        kill_usr_action,
        kill_pth_action,
        susp_mem_action,
        susp_usr_action,
        susp_pth_action;

    printf("===\nRunning Test Set for Action.\n===\n\n");

    printf("Testing initialization of actions...\n");
    // test initAction
    initAction(at_nice, pt_mem,     "128", &nice_mem_action);
    initAction(at_nice, pt_user,    "User433", &nice_usr_action);
    initAction(at_nice, pt_path,    "/tmp/testing", &nice_pth_action);
    initAction(at_kill, pt_mem,     "400", &kill_mem_action);
    initAction(at_kill, pt_user,    "mal", &kill_usr_action);
    initAction(at_kill, pt_path,    "/tmp/testing", &kill_pth_action);
    initAction(at_susp, pt_mem,     "300", &susp_mem_action);
    initAction(at_susp, pt_user,    "mal", &susp_usr_action);
    initAction(at_susp, pt_path,    "/tmp/testing", &susp_pth_action);

    // print one of each action for sanity check
    printf("actionType: %d paramType: %d param: %d\n", nice_mem_action.actionType, nice_mem_action.paramType, nice_mem_action.param.memoryCap);
    printf("actionType: %d paramType: %d param: %d\n", kill_usr_action.actionType, kill_usr_action.paramType, kill_usr_action.param.uid);
    printf("actionType: %d paramType: %d param: %s\n", susp_pth_action.actionType, susp_pth_action.paramType, susp_pth_action.param.pathName);
    printf("Done with initialization of actions...\n");



    // test take action
    printf("Testing taking of actions...\n");
    takeAction(&nice_mem_action);
    takeAction(&nice_usr_action);
    takeAction(&nice_pth_action);
    takeAction(&kill_mem_action);
    takeAction(&kill_usr_action);
    takeAction(&kill_pth_action);
    takeAction(&susp_mem_action);
    takeAction(&susp_usr_action);
    takeAction(&susp_pth_action);
    printf("Done taking of actions...\n");
    



    // test freeAction
    printf("Testing freeing of actions...\n");
    freeAction(&nice_mem_action);
    freeAction(&nice_usr_action);
    freeAction(&nice_pth_action);
    freeAction(&kill_mem_action);
    freeAction(&kill_usr_action);
    freeAction(&kill_pth_action);
    freeAction(&susp_mem_action);
    freeAction(&susp_usr_action);
    freeAction(&susp_pth_action);
    printf("Done freeing actions...\n");

    return 0; 
}
