// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
#include "util.h"
#include <stdlib.h>
#include <unistd.h>

int readLine(int fd, char *retLine, int retLineLength){
    int bytesInLine;
    int bytesRead;

    // assure retLine is not null
    if (retLine == NULL)
        return NullParamErr;
    if (retLineLength < 0)
        return NumErr;

    // Read as as we are allowed to given the provided buffer
    bytesRead = read(fd, retLine, retLineLength);
    if (bytesRead == -1)
        return IOErr;  // indicate we had IO error
    if (bytesRead == 0)
        return EndOfFileErr;  // indicate that we are at the end of the file

    // Find the newline, and replace it with the null terminator
    for ( bytesInLine=0 ; retLine[bytesInLine] != '\n' && bytesInLine < retLineLength ; bytesInLine++ );
    retLine[bytesInLine] = '\0';
    if (bytesInLine >= retLineLength)   // The buffer offered was not big enough for the line
        return BufferSizeErr;

    // Realign with where the end-of-line was found
    lseek(fd, -(bytesRead-bytesInLine-1), SEEK_CUR);

    return bytesInLine;
}



const char *strError(int errorCode){
    char *errString = NULL;
    switch(errorCode){
        case IOError:
            errString = errorStrings[-IOErr];
            break;
        case IOError:
        default:
            break;
    }
    return errString;
}
