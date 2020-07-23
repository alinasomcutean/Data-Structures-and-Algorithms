#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int nr_aparition;
    char word[100];
    struct node* next;
    struct node* prev;
} NodeT;

typedef struct header
{
    int count;
    NodeT* first;
    NodeT* last;
} ListT;

void createEmptyList(ListT** listPtr)
{
    if(listPtr)
    {
        (*listPtr)->count = 0;
        (*listPtr)->first = NULL;
        (*listPtr)->last = NULL;
    }
}

NodeT* createNode(char x[100])
{
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->word, x);
        p->nr_aparition = 0;
        p->next = p->prev = NULL;
    }
    return p;
}

int insertInOrder(ListT** listPtr, char x[100])
{
    NodeT* p, * q, * q1;
    q = (*listPtr)->first;
    q1 = NULL;
    p = createNode(x);
    if((*listPtr) == NULL)
    {
        (*listPtr)->first = (*listPtr)->last = p;
        p->prev = p->next = NULL;
        p->nr_aparition++;
    }
    else
    {
        while(q && (strcmp(q->word, p->word ) < 0))
        {
            q1 = q;
            q = q->next;
        }
        if(q && strcmp(q->word, x) == 0)
        {
            q->nr_aparition++;
        }
        else
        {
            if(q1 == NULL)
            {
                p->next = (*listPtr)->first;
                (*listPtr)->first->prev = p;
                (*listPtr)->first = p;
            }
            else
                if(q)
            {
                p->next = q;
                p->prev = q1;
                q1->next = p;
                q->prev = p;
            }
            else
            {
                p->next = q;
                p->prev = q1;
                q1->next = p;
                (*listPtr)->last = p;
            }
        }
        (*listPtr)->count++;
    }
}
FILE * fin, * fout;

void writeA(ListT* listPtr, FILE *fout)
{
    NodeT* p = listPtr->first;
    while(p != NULL)
    {
        fprintf(fout, "%s:%d\n", p->word, p->nr_aparition);
        p = p->next;
    }
}

void writeD(ListT* listPtr, FILE *fout)
{
    NodeT* p = listPtr->last;
    while(p != NULL)
    {
        fprintf(fout, "%s:%d\n", p->word, p->nr_aparition);
        p = p->prev;
    }
}

int main()
{

    fin = fopen("fin.in", "r");
    fout = fopen("fin.out", "w");

    if(fin== NULL)
    {
        perror("not found input");
        exit(-1);
    }

    if(fout== NULL)
    {
        perror("not found");
        exit(-1);
    }

    ListT* list;
    list = (ListT*)malloc(sizeof(ListT));
    char x[1000];
    createEmptyList(&list);

    while(fscanf(fin, "%s", x) != EOF)
    {
        insertInOrder(&list, x);
    }

    writeA(list, fout);
    fprintf(fout, "\n");
    writeD(list, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}
