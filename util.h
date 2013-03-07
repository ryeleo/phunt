// 2013 - Ryan Leonard <ryan.leonard71@gmail.com>
/*
Description: Read a line from the file specified by fd, and assure that the file 
offset reflects the number of characters returned.

Return: Number of characters returned in retLine on success,
*/
static int readLine(int fd, char *retLine, int retLineLength);
