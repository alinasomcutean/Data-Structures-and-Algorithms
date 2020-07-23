#include <stdio.h>
#include <stdlib.h>
#include "profit.h"
#include "maxim.h"

FILE *fin, *fout;

/*float maxim(float v[], int first, int last)
{
    float M = 0;
    while(first <= last)
    {
        if(v[first] > M)
            M = v[first];
        first++;
    }
    return M;
}

float profit(float v[], int first, int last)
{
    int i = 0;
    float profit = 0;
    float M;
    for(i = first; i < last; i++)
    {
        M = maxim(v,i,last-1);
        if(M > v[i])
        {
            profit = profit + M - v[i];
        }
    }
    return profit;
}*/


int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    int i,n;
    fscanf(fin, "%d", &n);
    float v[n];
    for(i = 0; i< n; i++)
        fscanf(fin, "%f", &v[i]);

    fprintf(fout,"%f ", profit(v,0,n));
    return 0;
}
