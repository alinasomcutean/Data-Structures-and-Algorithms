#include <stdio.h>
#include <stdlib.h>

void delete_char(char x[2000], int pos)
{
    int i;
    for(i = pos; i < strlen(x); i++)
    {
        strcpy(x[i], x[i+1]);
    }
}
