#include "log.h"

int initLog(char *fileName, char *prefixMessage, struct Log *log){
    int ret;

    ///// Copy fileName to log->fileName
    ///// Copy prefixMessage to log->prefix
    strncpy(,, MAX_STRLEN_PREFIX);


    ///// Open log file, attribute it to log->fd
    ret = open(fileName, O_RDWR | O_APPEND | O_CREAT, 
            S_IRUSR | S_IWUSER | S_IRGRP | S_IROTH);
    if (ret == -1)
        return -4;
    else
        log->log_fd = ret;
}



int writeMessage(char *message, struct Log *log){
    int ret;
    time_t time;
    struct tm tm;
    char strTime[MAX_STRLEN_TIME];
    char logMessage[MAX_STRLEN_LOGMESSAGE];

    ///// Get time 
    // Get the time that this message will be recorded to be logged at
    time = time(NULL); 
    tm = *localtime(*time);
    ret = snprintf(strTime, MAX_STRLEN_TIME, "%d/%d/%d %d:%d:%d ", tm.tm_year +
            1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    strTime[MAX_STRLEN_TIME-1] = '\0';
    if (ret < 0)
        return -1;


    ///// Compile the logMessage (time + prefix + ": " + message)
    ret = snprintf(logMessage, MAX_STRLEN_LOGMESSAGE, "%s %s: %s", strTime,
            log->prefix, message);
    logMessage[MAX_STRLEN_LOGMESSAGE-1] = '\0';
    if (ret < 0)
        return -1;

    
    ///// print the logMessage to file
    ret = write(log->log_fd, logMessage, MAX_STRLEN_LOGMESSAGE);
    if (ret == -1)
        return -4;
    return 0;
}
