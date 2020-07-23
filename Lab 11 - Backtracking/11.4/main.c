#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char cfg[30];
    int spacePos;
    int cost;
    struct Node* pNext;
    struct Node* pPrev;
    struct Node* pParent;
} Node;

int n = 3;

void printSol(struct Node* p)
{
    if(p == NULL)
        return;
    printSol(p->pParent);
    printf("%s\n", p->cfg);
}

int main()
{
    struct Node* root;
    root =  (struct Node*)malloc(sizeof(struct Node));
    strcpy(root->cfg, "aaa bbb");
    root->spacePos = n;
    root->cost =n;
    root->pPrev = root->pNext = root->pParent = NULL;

    struct Node* pLiveNodes = root;
    struct Ndoe* pDeadNodes = NULL;

    struct Node* i;
    while(i)
    {
        i = getLCNode(pLiveNodes);
    }
    return 0;
}
