#include "actionlist.h"
#include "action.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){
    char *fileName[1] = {
        "testactionlist.config"
    };

    int i, ret;
    struct ActionList actionList;
    struct Action action;

    printf("===\nRunning Test Set for ActionList.\n===\n\n");

    // Test how parsing a config file goes
    initActionList(fileName[0], &actionList);

    // Print all of the actions in the ActionList
    for(i=0 ; i < 10 ; i++){
        ret = getAction(&action, &actionList);
        printf("ret = %d\n", ret);
        ret = nextAction(&actionList);
        printf("ret = %d\n", ret);
        printf("%d, %d, %s\n", action.actionType, action.paramType, (char*)action.param.pathName);
    }

    // Lets see if the free function works
    // ret = freeActionList(&actionList);
    printf("ret = %d\n", ret);

    return 0; 
}
