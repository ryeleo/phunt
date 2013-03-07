// XXX Check that there are no off-by-one issues or anything
static int readLine(int fd, char *retLine, int retLineLength){
    int ret;
    int bytesInLine;
    int bytesRead;

    // assure retLine is not null
    if (retLine == NULL)
        return -2;

    // Read as as we are allowed to given the provided buffer
    bytesRead = read(fd, line, retLineLength);
    if (bytesRead == -1)
        return -1; //XXX is this on okay practice, to use -1 when my convention says to use -2?
    if (bytesRead == 0)
        return 0;  // indicate that we are at the end of the file

    // Find the newline, and replace it with the null terminator
    for ( bytesInLine=0 ; line[bytesInLine] != '\n' ; bytesInLine++ );
    if (bytesInLine == retLineLength)   // The buffer offered was not big enough for the line
        return -1; //XXX is this on okay practice, to use -1 when my convention says to use -2?
    else
        line[bytesInLine] = '\0';

    // Realign with where the end-of-line was found
    lseek(fd, -(bytesRead-bytesInLine), SEEK_CUR);

    return bytesInLine;
}
