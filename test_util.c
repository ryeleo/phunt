#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

#define LINE_LENGTH 128

int main(int argc, char **argv){
    char *fileName = "./testFiles/testutil.txt";
    char line[LINE_LENGTH];

    int i, ret, fd;

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
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);
    ret = readLine(fd, line, LINE_LENGTH);
    printf("ret = %d\n", ret);
    printf("line = %s\n", line);


    printf("Some Strerror testing.\n");
    for (i = 0 ; i >= -10 ; i--)
        printf("%s\n", strError(i));


    return 0;
}
