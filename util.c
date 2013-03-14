// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "util.h"
#include <stdlib.h>
#include <unistd.h>

int readLine(int fd, char *retLine, int retLineLength){
    int bytesInLine;
    int bytesRead;

    // assure retLine is not null
    if (retLine == NULL)
        return -2;

    // Read as as we are allowed to given the provided buffer
    bytesRead = read(fd, retLine, retLineLength);
    if (bytesRead == -1)
        return -4;  // indicate we had IO error
    if (bytesRead == 0)
        return -6;  // indicate that we are at the end of the file

    // Find the newline, and replace it with the null terminator
    for ( bytesInLine=0 ; retLine[bytesInLine] != '\n' && bytesInLine < retLineLength ; bytesInLine++ );
    retLine[bytesInLine] = '\0';
    if (bytesInLine >= retLineLength)   // The buffer offered was not big enough for the line
        return -5;

    // Realign with where the end-of-line was found
    lseek(fd, -(bytesRead-bytesInLine-1), SEEK_CUR);

    return bytesInLine;
}



const char *strError(int errorCode){
    char *errString = NULL;
    switch(errorCode){
        case IOError:
            errString = errorStrings[4];
            break;
        case IOError:
        default:
            break;
    }
    return errString;
}
