#include <stdio.h>
#include <stdlib.h>
#include "maxim.h"

float maxim(float v[], int first, int last)
{
    float M = 0;
    while(first <= last)
    {
        if(v[first] > M)
            M = v[first];
        first++;
        //printf("%f ", M);
    }
    return M;
}
