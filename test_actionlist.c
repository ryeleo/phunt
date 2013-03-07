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
    for(){
        getAction(&action, );
        nextAction();
        printf();
    }

     
}
