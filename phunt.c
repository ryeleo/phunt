// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
// 2013 - James Ingalls <james.ingalls@gmail.com>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_OPT_LEN 256

#define printError(errorCode) do( printf("Error: %s -- %s:%d\n    Message:", __FILE__, __func__, __LINE__, strError(errorCode)); )while{0};
/*
Description: Prints the usage to user
*/
static void usage(char **argv);



/* 
    Main should do all initialization and interaction with the user. It should
    also in the case of the request of running as a daemon, be forked and moved 
    to the appropriate environment. E.g. change current directory, changed
    parent process to the init process, etc...
    -- Heavy Lifting --
    Initialize_everything;
    if (-d) daemonize();
    while
*/
int main(int argc, char **argv){

    int 
        i,              // general purpose iterator
        ret,            // general-purpose/error-checking return value
        byteCount,      // used to hold the number of bytes when buffering writes/sends
        isDaemon = 0;   // flag to indicate that this program will execute as a daemon

    char
        logFileName[MAX_OPT_LEN] = "/var/log/phunt.log",    // Filename of log to append to while running this process
        configFileName[MAX_OPT_LEN] = "/etc/phunt.conf";    // Filename of configuration for running this process

    struct Log log;
    struct ActionList *actionList;



#ifdef DEBUG
    printf("===\nRunning %s in Debug mode.\n===\n\n", argv[0]);
#endif


    ///// Usage & Parse parameters
    // Parse options provided at CL
    while ((ret = getopt(argc, argv, "l:c:d")) != -1)
    {
        switch (ret)
        {
            case 'l':
                strncpy(logFileName, optarg, MAX_OPT_LEN);
                logFileName[MAX_OPT_LEN-1] = '\0';
                break;
            case 'c':
                strncpy(configFileName, optarg, MAX_OPT_LEN);
                configFileName[MAX_OPT_LEN-1] = '\0';
                break;
            case 'd':
                isDaemon = 1;
                break;
            default:
                usage(argv);
                exit(0);
        }
    }


    ///// Initialize log and actionList
    // initialize the actionList
    ret = initActionList(configFileName, &actionList);
    if (ret < 0){
        printError(ret);
        exit(0);
    }

    struct Log log, *log_p;
    struct Log *h_log;

    printf("===\nRunning Test Set for Logging System.\n===\n\n");

    // Test stack log and 
    log_p = &log;
    initLog(fileName[0], prefix[0], log_p);
    for(i = 0 ; i < 4 ; i++)
        writeMessage(lines[i], log_p);
    closeLog(log_p); 
    printf("Finished testing Log on stack: %s\n", fileName[0]);

    // Print all of the actions in the ActionList
    // Notice that this is the general way to iterate through the list
    struct ActionList *pal = p_actionList;
    struct Action *p_action;
    do{
        ///// Get the next action in the list
        ret = getAction(&p_action, &pal);
        if (ret < 0){
            printError(ret);
            exit(0);
        }
        // Incrament our list to the next action
        ret = nextAction(&pal);
        if (ret < 0){
            printError(ret);
            exit(0);
        }

        ///// fulfil the next action
        ret = takeAction(p_action);
        if (ret < 0){
            printError(ret);
            exit(0);
        }

        printf("%d, %d, %d\n", p_action->actionType, p_action->paramType, p_action->param.uid);
    } while ( pal != p_actionList );

    // Clear up all of the memory used in the actionList
    ret = freeActionList(&p_actionList);
    if (ret < 0)
        printError(ret);



    exit(0);
}//END main


static void usage(char **argv)
{
    printf("Usage: ");
    if (argv != NULL && argv[0] != NULL)
        printf("%s [-l <log_file>] [-c <config_file>] [-d]\n", argv[0]);
    else
        printf("phunt [-l <log_file>] [-c <config_file>] [-d]\n");
}
