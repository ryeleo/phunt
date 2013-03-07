// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>


int initActionList(char *fileName, struct ActionList *actionList){
}



int nextAction(struct ActionList *actionList){
    // Make sure that params aren't null
    if (actionList == NULL || actionList.next == NULL)
        return -2;

    ///// Simply update actionList to point to the next element.
    actionList = actionList.next;

    return 0;
}



int getAction(struct Action *retAction){
    
}
