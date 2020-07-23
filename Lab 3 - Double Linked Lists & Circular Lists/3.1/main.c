#include <stdio.h>
#include <stdlib.h>
#define NOT_FOUND -1


typedef struct node
{
    char name[20];
    struct node *next;
} child;

typedef struct header
{
    unsigned int capacity;
    int first;
    child *data;
} List;

List *createlist(int size)
{
    List *ptr=(List*)malloc(sizeof(List));
    if(ptr)
    {
        ptr->data=(child*)calloc(size, sizeof(child));
        if(ptr->data)
        {
            ptr->capacity=size;
            ptr->first=-1;
            for(int i=0; i<ptr->capacity - 1; i++)
                ptr->data[i].next=i+1;
        }
        ptr->data[ptr->capacity-1].next=NOT_FOUND;
    }
    else
    {
        free(ptr);
        ptr=NULL;
    }
    return ptr;
}

int nr;
int main()
{
    FILE *fin,*fout;
    fin=fopen("inf.in","r");
    fout=fopen("inf.out","w");

    fscanf(fin, "%d", &nr );
    printf(fout,"%d \n", nr);

    List *game;
    game=createlist(nr);

    int i, j;
    for(i=1; i<=nr; i++)
        fscanf(fin, "%s", game->data[i].name);

    int count;
    i=1;
    while(game->capacity>1)
    {
        count=1;
        while(count!=nr)
        {
            i++;
            count++;
            if(i>game->capacity)
                i=1;
        }
        for(j=i; j<game->capacity; j++)
            strcpy(game->data[j].name, game->data[j+1].name);
        game->capacity--;
        if(i>=game->capacity) i=1;
    }
    fprintf(fout,"%s", game->data[1].name);
//when a child leaves the game the counting starts again from the next one in the circle
    fclose(fin);
    fclose(fout);
    return 0;
}




