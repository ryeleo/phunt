#include "log.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int initLog(char *fileName, char *prefixMessage, struct Log *log){
    int ret;

    // Verify passed parameters
    if (log == NULL || fileName == NULL || prefixMessage == NULL)
        return -2;

    ///// Copy fileName to log->fileName
    strncpy(log->fileName, fileName, MAX_STRLEN_FILENAME);
    log->prefix[MAX_STRLEN_PREFIX-1] = '\0'; 


    ///// Copy prefixMessage to log->prefix
    strncpy(log->prefix, prefixMessage, MAX_STRLEN_PREFIX);
    log->prefix[MAX_STRLEN_PREFIX-1] = '\0'; 


    ///// Open log file, attribute it to log->fd
    ret = open(fileName, O_RDWR | O_APPEND | O_CREAT, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (ret == -1)
        return -4;
    else
        log->log_fd = ret;

    return 0;
}



int closeLog(struct Log *log){
    int ret;

    // Verify passed parameters
    if (log == NULL)
        return -2;

    ///// Close log file
    ret = close(log->log_fd);
    if (ret == -1)
        return -4;

    return 0;
}



int writeMessage(char *message, struct Log *log){
    int ret;
    time_t t;
    struct tm tm;
    char strTime[MAX_STRLEN_TIME];
    char logMessage[MAX_STRLEN_LOGMESSAGE];

    // Verify passed parameters
    if (message == NULL || log == NULL)
        return -2;

    ///// Get time 
    // Get the time that this message will be recorded to be logged at
    t = time(NULL); 
    tm = *localtime(&t);
    ret = snprintf(strTime, MAX_STRLEN_TIME, "%02d/%02d/%02d %02d:%02d:%02d ", tm.tm_year +
            1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    strTime[MAX_STRLEN_TIME-1] = '\0';
    if (ret < 0)
        return -1;


    ///// Compile the logMessage (time + prefix + ": " + message)
    ret = snprintf(logMessage, MAX_STRLEN_LOGMESSAGE, "%s %s: %s\n", strTime,
            log->prefix, message);
    logMessage[MAX_STRLEN_LOGMESSAGE-2] = '\n'; // Assures that even in the worst case we still
    logMessage[MAX_STRLEN_LOGMESSAGE-1] = '\0'; // are safe with string manipulation
    if (ret < 0)
        return -1;

    
    ///// print the logMessage to file
    ret = write(log->log_fd, logMessage, strlen(logMessage));
    if (ret == -1)
        return -4;
    return 0;
}
