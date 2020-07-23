#include <stdio.h>
#include <stdlib.h>
#include "maxim.h"
#include "profit.h"

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
}
