#include "log.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){
    static char *lines[10] = {
        "This is the first message.",
        "Message number 2!",
        "3",
        "4",
        "5",
        "",
        "Message # 6 was blank!",
        "This is 7",
        "Message number 8 is increadably long to see how we really handle this situation, if it is not graceful we might see a segfault, but more likely this message will just get cut off a little bit early. Not the most graceful, but I feel that it is probably the best that we can to and still be a small code base.",
        "Finally, good 'ol message 9"
    };
    char *prefix[2] = {
        "Testing_Logs",
        "Testing_Logs_WithREAllyReallyReallWayTooLongPrefixThatHopefullyNobodyWillEverUse"
    };
    char *fileName[3] = {
        "testlog_stackLog.txt",
        "testlog_heapLog.txt",
        "testlog_longstuff.txt"
    };

    int i, ret;
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


    // Test HeapLog
    h_log = malloc(sizeof(struct Log));
    if (h_log == NULL){
        printf("Unable to malloc log, not our problem, just try again.");
        exit(0);
    }
    log_p = h_log;
    initLog(fileName[1], prefix[0], log_p);
    for(i = 0 ; i < 4 ; i++)
        writeMessage(lines[i], log_p);
    closeLog(log_p); 
    free(h_log);
    printf("Finished testing Log on heap: %s\n", fileName[1]);


    // Test another heap log with increadably long messages and filename and prefix
    h_log = malloc(sizeof(struct Log));
    if (h_log == NULL){
        printf("Unable to malloc log, not our problem, just try again.");
        exit(0);
    }
    log_p = h_log;
    ret = initLog(fileName[2], prefix[1], log_p);
    printf("ret = %d\n", ret);
    for(i = 0 ; i < 10 ; i++){
        ret = writeMessage(lines[i], log_p);
        printf("ret = %d\n", ret);
    }
    ret = closeLog(log_p); 
    printf("ret = %d\n", ret);
    free(h_log);
    printf("Finished testing Log on heap with massive strings: %s\n", fileName[2]);
    
    exit(0);
}
