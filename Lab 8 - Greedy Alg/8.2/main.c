#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;
int nrOfActivities;

typedef struct activity
{
    int start_time;
    int finish_time;
}ActivityT;

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");
    fscanf(fin, "%d", &nrOfActivities);

    ActivityT event[nrOfActivities];
    for(int i = 1; i <= nrOfActivities; i++)
    {
        fscanf(fin, "%d", &event[i].start_time);
        fscanf(fin, "%d", &event[i].finish_time);
    }

    ActivityT e[nrOfActivities];
    int max = 0, i,k=1;

    for( i = 1; i <= nrOfActivities; i++)
    {
        if(event[i].finish_time - event[i].start_time > max)
        {
            max = i;
        }
    }

    e[1] = event[max];

    for(i = 1; i <= nrOfActivities; i++)
    {
        if(event[i].finish_time <= e[1].start_time || event[i].start_time >= e[1].finish_time)
        {
            e[++k] = event[i];
        }
    }
    for(i = 1; i <=k; i++)
        fprintf(fout, "%d %d\n", e[i].start_time, e[i].finish_time);

    return 0;
}
