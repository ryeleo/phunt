// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
/*
Description: Read a line from the file specified by fd, and assure that the file 
offset reflects the number of characters returned.

Return: Number of characters returned in retLine on success, -4 on ioError, -5 
if provided buffer is not sufficiant size to get next line, note however that
the buffer will be the full size of retLine provided and the file seeking should
manage, so -5 indicats simply read again.
*/
int readLine(int fd, char *retLine, int retLineLength);
