#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    char qChar[256];

    if (argc != 2){
        printf("Usage: suckMem <amount-of-memory-in-MB>\n");
        return 0;
    }
    
    if (NULL == malloc(atoi(argv[1]) * 1024 * 1024)){
        printf("Shit went wrongggg\n");
        return 0;
    }

    printf("Type in 'q' to quit!\n");
    do{
        scanf("%s\n", qChar);
    }while (strncmp("q",qChar) != 0);


    return 0;
}
