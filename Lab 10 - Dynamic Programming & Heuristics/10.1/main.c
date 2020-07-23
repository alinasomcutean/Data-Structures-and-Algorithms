#include <stdio.h>
#include <stdlib.h>
#include "insert.h"
#include "delete.h"
#include "replace.h"

FILE *fin, *fout;

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    int n;
    fscanf(fin, "%d", &n);
    int i;

    for(i = 0; i < n; i++)
    {
        char s1[2000], s2[2000];
        fscanf(fin, "%s %s", &s1, &s2);
        int x = 0, op = 0;
        while(x < strlen(s2))
        {
            if(s1[x] != s2[x])
            {
                replace_char(s1, s2, x);
                op++;
            }
            if(s1[x] != '\0' && s2[x] == '\0')
            {
                delete_char(s1, x);
                op++;
            }
            if(s1[x] == '\0' && s2[x] != '\0')
            {
                insert_char(s1, s2, x);
                op++;
            }
            x++;
        }
    fprintf(fout, "%d", op);
    }

    return 0;
}
