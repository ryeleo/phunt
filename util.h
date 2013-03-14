// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
/*
Description: Read a line from the file specified by fd, and assure that the file 
offset reflects the number of characters returned.

Return: Number of characters returned in retLine on success, -4 on ioError, -5 
if provided buffer is not sufficiant size to get next line, note however that
the buffer will be the full size of retLine provided and the file seeking should
manage, so -5 indicats simply read again. -6 indicates end of file
*/
#ifndef __UTIL_H__
#define __UTIL_H__

/*
Description: Reads a line from a file and places it into retLine.

fd: FileDescriptor of the file to be read from.
retLine: Returned line as read from file, will be null terminated except in the
    case that there was too many characters in the line to fit in retLine.
retLineLength: The length of retLine, assures no Buffer Overflow.

Return: Number of characters in line upon success, 
-2 if incorrect parameters passed, 
-4 if IO Error when reading from file, 
-5 if buffer provided is not sufficiant length to hold the line, 
-6 if we reached the end of file
*/
int readLine(int fd, char *retLine, int retLineLength);


/*
Description: Takes an error code and returns a pointer to a const char * which
represents the message the error code is trying to print. See the defines below
the function decleration to see valid errorCodes, as well as the printed
strings.

errorCode: The error code to print

Return: A const char * to the string representing the error code,
NULL if errorCode does not exist
*/
const inline char *strError(int errorCode);
const char *errorString[] = {
    "",
    "IO Error has occured, verify all file descriptors",
}
#define NoneErr
#define MemErr -1
#define NullParamErr -2
#define CodeErr -3
#define IOError -4
#define 

#define MAX_STRLEN_ERROR 256

#endif//__UTIL_H__
