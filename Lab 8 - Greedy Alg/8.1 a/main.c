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

    int maxim, pos, total_v = 0, total_w = 0, minim_w;

    while(total_w < W && n > 0)
    {
        maxim = v[1];
        pos = 1;
        minim_w = w[1];
        for(int i = 2; i <= n; i++)
        {
            if(v[i] > maxim)
            {
                maxim = v[i];
                pos = i;
                minim_w = w[pos];
            }
            if(v[i] == maxim)
            {
                if(w[i] < w[pos])
                    {
                        minim_w = w[i];
                        pos = i;
                    }
                    else
                        minim_w = w[pos];
            }
        }
        total_v = total_v + maxim;
        total_w = total_w + minim_w;
        for(int j = pos; j < n; j++)
        {
            v[j] = v[j+1];
            w[j] = w[j+1];
        }
        n--;
        if(total_w > W)
    {
        total_w = total_w - minim_w;
        total_v = total_v - maxim;
    }
    }



    fprintf(fout, "%d %d", total_w, total_v);
    return 0;
}
