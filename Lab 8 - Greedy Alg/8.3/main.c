#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

typedef struct work
{
    int t;
    float x,y,raport;
} worker;

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    int n,d;
    fscanf(fin, "%d %d", &n, &d);

    worker w[n];
    for(int i = 1; i <= n; i++)
    {
        fscanf(fin, "%d %f %f", &w[i].t, &w[i].x, &w[i].y);
        w[i].raport = (w[i].x)/(w[i].y);
    }

    float min_cost = 0;
    int ok = 1;
    worker aux;
    while(ok)
    {
        ok = 0;
        for(int i = 1; i < n; i++)
            if(w[i].raport < w[i+1].raport)
            {
                aux = w[i];
                w[i] = w[i+1];
                w[i+1] = aux;
                ok = 1;
            }
    }

    float units = 0;
    int i = 1;

    while(units < d && i <= n)
    {
        units = units + w[i].y;
        min_cost = min_cost + w[i].x;
        i++;
    }

    printf("%f", min_cost);

    return 0;
}
