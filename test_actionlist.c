// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "actionlist.h"
#include "action.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){
    char *fileName[1] = {
        "./testFiles/testactionlist.config"
    };

    int ret;
    struct ActionList *p_actionList;

    printf("===\nRunning Test Set for ActionList.\n===\n\n");

    // Test how parsing a config file goes
    ret = initActionList(fileName[0], &p_actionList);
    if (ret < 0)
        printf("motherfuckin issues!\n");

    // Print all of the actions in the ActionList
    // Notice that this is the general way to iterate through the list
    struct ActionList *pal = p_actionList;
    struct Action *p_action;
    do{
        ret = getAction(&p_action, &pal);
        if (ret < 0)
            printf("motherfuckin issues!\n");

        ret = nextAction(&pal);
        if (ret < 0)
            printf("motherfuckin issues!\n");

        printf("%d, %d, %d\n", p_action->actionType, p_action->paramType, p_action->param.uid);
    } while ( pal != p_actionList );

    // Lets see if the free function works
    ret = freeActionList(&p_actionList);
    if (ret < 0)
        printf("motherfuckin issues!\n");

    return 0; 
}
