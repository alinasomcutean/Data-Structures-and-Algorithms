#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

int main()
{
    int n, W;
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &W);

    int w[n], v[n];
    for(int i = 1; i <= n; i++)
    {
        fscanf(fin, "%d %d", &w[i], &v[i]);
    }

    int ok = 1,aux;
    while(ok)
    {
        ok = 0;
        for(int i = 1; i < n; i++)
            if(v[i] < v[i+1])
        {
            aux = v[i];
            v[i] = v[i+1];
            v[i+1] = aux;
            aux = w[i];
            w[i] = w[i+1];
            w[i+1] = aux;
            ok = 1;
        }
    }

    int weight_max = 0, val_max = 0,x,y;
    for(int i = 1; i <= n; i++)
    {
        if(weight_max < W)
        {
            weight_max = weight_max + w[i];
            val_max = val_max + v[i];
        }
        if(weight_max > W)
        {
            x = weight_max - W;;
            weight_max = W;
            y = (x*v[i])/w[i];
            val_max = val_max - y;
        }
    }

    fprintf(fout, "%d %d", weight_max, val_max);
    return 0;
}
