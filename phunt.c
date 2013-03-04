#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define MAX_OPT_LEN 256
const enum error = {
    IndexError = -2,
    Error = -1
};

const char *strError();

const char *strError();


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



#ifdef DEBUG
    printf("===\nRunning %s in Debug mode.\n===\n\n", argv[0]);
#endif



    ////////// Usage & Parse parameters
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


    ////////// Initialize log and config file
    ret = initConfig(configFileName);
    if (ret == -1)
    {
        printf("Unable to initialize based on configuration file: %s\n", configFileName);
        exit(0);
    }
    ret = initLog(logFileName);
    if (ret == -1)
    {
        printf("Unable to initialize based on log file: %s\n", configFileName);
        exit(0);
    }
      

    exit(0);
}//END main



int writeToLog(char *message, int log_fd)
{
}



int initConfig()
{
}



int initLog()
{
}



static void usage(char **argv)
{
    printf("Usage: ");
    if (argv != NULL && argv[0] != NULL)
        printf("%s [-l <log_file>] [-c <config_file>] [-d]\n", argv[0]);
    else
        printf("phunt [-l <log_file>] [-c <config_file>] [-d]\n");
}
