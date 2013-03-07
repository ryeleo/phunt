#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

#define LINE_LENGTH 128

int main(int argc, char **argv){
    char *fileName = "testutil.txt";
    char line[LINE_LENGTH];

    int ret, fd;

    printf("===\nRunning Test Set for util.c.\n===\n\n");

    ///// Open file, attribute it to log->fd
    ret = open(fileName, O_RDWR | O_APPEND | O_CREAT, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (ret == -1)
        printf("Could not open file: %s\n", fileName);
    else
        fd = ret;
    
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);

    return 0;
}
