#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;
int n;

typedef struct people
{
    int age;
    int salary;
    char x;
}peopleT;

void order (peopleT x[n])
{
    int i,j;
    peopleT aux;
    for(i = 0; i < n-1; i++)
    {
        for(j = i+1; j < n; j++)
            if(x[i].salary > x[j].salary)
        {
            aux = x[i];
            x[i] = x[j];
            x[j] = aux;
        }
    }
}

int min(peopleT x[n], peopleT y[n])
{
    int sum = 0;
    int i,j;
    for(i = 0; i < n/2; i++)
    {
        sum = sum + x[i].salary;
        x[i].x = 'c';
        for(j = 0; j < n; j++)
        {
            if(y[j].x == 'u' && y[j].age < x[i].age)
            {
                sum = sum + y[j].salary;
                y[j].x = 'c';
                break;
            }
        }
    }
    return sum;
}

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    fscanf(fin, "%d", &n);

    peopleT e[n];
    peopleT c[n];

    int i;
    for(i = 0; i < n; i++)
    {
        fscanf(fin, "%d %d", &e[i].salary, &c[i].salary);
        e[i].age = c[i].age = i;
        e[i].x = c[i].x = 'u';
    }

    order(e);
    order(c);

    /*for(i = 0; i < n; i++)
    {
        printf("%d %d %c\n", e[i].age, e[i].salary, e[i].x);

    }
    for(i = 0; i < n; i++)
    {
        printf("%d %d %c\n", c[i].age, c[i].salary, c[i].x);

    }*/

    printf("%d", min(e, c));
    return 0;
}
