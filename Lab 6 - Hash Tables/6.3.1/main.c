#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 50

typedef struct cell
{
    char name[150];
    struct cell *next;
} NodeT;

NodeT *Bucket[B];

int f(char name[150]) //f is the sum of the ascii characters because each (full) different name should have a different sum
{
    int s=0, l, i;
    l=strlen(name);
    for(i=0; i<l; i++)
        s=s+name[i];
    return (s%B);
}

NodeT* fillnode(char s[150])
{
    NodeT* p=(NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->name, s);
        p->next=NULL;
    }
    return p;
}

void insert (NodeT* Bucket[B], char s[150])
{
    NodeT* p=(NodeT*) malloc(sizeof(NodeT));
    int q;
    p=fillnode(s);
    int h;
    h=f(s);
    if(Bucket[h]==NULL)
    {

        Bucket[h]=p;
        p->next=NULL;
    }
    else
        {
            q=findnode(Bucket, p->name);
            if(q==0)
            {
                p->next=Bucket[h];
                Bucket[h]=p;
            }
            else
            printf("Node with name %s already exists at a different location", p->name);
            }
    return p;
}

int findnode(NodeT* Bucket[B], char s[150])
{
    int h=f(s);
    NodeT* p;
    p=Bucket[h];
    while(p != NULL)
    {
        if(strcmp(p->name, s) == 0)
            return h;
        p = p->next;
    }
    return 0;
}


void list(NodeT* Bucket[B], FILE *fout)
{
    NodeT *p = NULL;
    int i;
    for(i = 0; i < B; i++)
    {
        p = Bucket[i];
        fprintf(fout,"%d: ", i);
        while(p != NULL)
        {
            fprintf(fout,"%s ", p->name);
            p = p->next;
        }
        fprintf(fout,"\n");
    }
    fprintf(fout,"\n");
}
void deletenode(NodeT *Bucket[B], char s[150])
{
    int h = f(s);
    NodeT *p = NULL;
    p = Bucket[h];
    NodeT *temp = NULL;
    if(strcmp(p->name, s) == 0)
    {
        Bucket[h] = p->next;
        free(p);
    }
    else
    {
        while(p != NULL)
        {
            if(strcmp(p->name, s) == 0)
            {
                temp->next = p->next;
                free(p);
            }
            temp = p;
            p = p->next;
        }
    }
}
int main()
{
    FILE *fin, *fout;
    fin=fopen("input.in", "r");
    fout=fopen("output.out", "w");
    int i;
    char c;
    char s[150];
    for (i=0; i<B; i++)
        Bucket[i]=NULL;
    while((c=fgetc(fin))!=EOF)
    {
        switch(c)
        {
        case 'i':
        {
            fgets(&s, 150, fin);
            insert(Bucket, s);
            break;
        }
        case 'd':
        {
            fgets(&s, 150, fin);
            deletenode(Bucket, s);
            break;
        }
        case 'f':
        {
            fgets(&s, 150, fin);
            int x=findnode(Bucket, s);
            if(x!=0)
                fprintf(fout, "yes, found at index %d\n", x);
            else
                fprintf(fout, "not found\n");
            break;
        }
        case 'l':
        {
            list(Bucket, fout);
            break;
        }
        }
    }
    return 0;
}
