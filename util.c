// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
// 2013 - James Ingalls <james.ingalls@gmail.com>

#include "util.h"
#include <pwd.h>
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

// getUidFromUser returns the uid given a username
int getUidFromUser(char *uname){
    struct passwd *passwd;
    passwd = getpwnam(uname);
    if (passwd == NULL)
        return -2; 
    else
        return (int) passwd->pw_uid;
}


char *errorStrings[11] = {
    "",
    "Memory Error; had an issue mallocing a block of memory.",
    "Null Pointer Parameter Error; there was a pointer passed as NULL when it needs to hold a value.",
    "Code Error; XXX this should never happen, soz.",
    "IO Error; verify file descriptors and calls to read/write/open/close.",
    "Buffer Size Error; a buffer of insufficiant size was provided.",
    "End of File Error; not really an error, just means that we reached the end of the file.", 
    "Parse File Error; had issues parsing a file, verify all input files to this program.",
    "Syscall Error; error occured when utalizing a system call.",
    "Number Error; a number value was outside the realm of acceptable values.",
    "C-Library Call Error; issue occured inside of one of the clib calls."
};
char *strError(int errorCode){
    char *errString = NULL;
    if (errorCode <= 0 && errorCode >= -10)
        errString = errorStrings[-errorCode];
    return errString;
}
