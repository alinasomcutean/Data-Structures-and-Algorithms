#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;
int n, v[];

int find_top(int li, int ls)
{
    int lm;
    if(li > ls)
        return -1;
    else
    {
        lm = (li + ls)/2;
        if(v[lm] < v[lm+1])
        {
            find_top(lm, ls);
        }
        else if(v[lm] > v[lm+1])
        {
            return v[lm];
        }

    }
}

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    fscanf(fin, "%d", &n);

    int i;

    for(i = 0; i < n; i++)
        fscanf(fin, "%d ", &v[i]);

    printf("%d", find_top(0, n-1));

    return 0;
}
