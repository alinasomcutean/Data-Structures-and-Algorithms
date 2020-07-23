#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char id;
    struct node* pLeft;
    struct node* pRight;
}nodeT;

FILE *fin, *fout;

nodeT* buildTree()
{
    char c;
    fscanf(fin, "%c", &c);
    if(c == '*')
        return NULL;
    nodeT* pNew = (nodeT*)malloc(sizeof(nodeT));
    pNew->id = c;
    pNew->pLeft = buildTree();
    pNew->pRight = buildTree();
    return pNew;
}

void showTreePreorder(nodeT* pNode, int level)
{
    if(pNode == NULL)
        return ;
    fprintf(fout, "%*s%c\n", 3*level, "", pNode->id);
    showTreePreorder(pNode->pLeft, level+1);
    showTreePreorder(pNode->pRight, level+1);
}

void showTreeInorder(nodeT* pNode, int level)
{
    if(pNode == NULL)
        return ;
    showTreeInorder(pNode->pLeft, level+1);
    fprintf(fout, "%*s%c\n", 3*level, "", pNode->id);
    showTreeInorder(pNode->pRight, level+1);
}

void showTreePostorder(nodeT* pNode, int level)
{
    if(pNode == NULL)
        return ;
    showTreePostorder(pNode->pLeft, level+1);
    showTreePostorder(pNode->pRight, level+1);
    fprintf(fout, "%*s%c\n", 3*level, "", pNode->id);
}

void deleteTree(nodeT* pNode)
{
    if(pNode == NULL)
        return 0;
    deleteTree(pNode->pLeft);
    deleteTree(pNode->pRight);
}

int height(nodeT* pNode)
{
    if(pNode == NULL)
        return 0;
    int leftHeight = height(pNode->pLeft);
    int rightHeight = height(pNode->pRight);
    if(leftHeight>rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int nrLeaves(nodeT* pNode)
{
    if(pNode == NULL)
        return 0;
    if(pNode->pLeft == NULL && pNode->pRight == NULL)
        return 1;
    else
        return nrLeaves(pNode->pLeft)+nrLeaves(pNode->pRight);
}

nodeT* findNode(nodeT* pNode, char id)
{
    if(pNode == NULL)
        return NULL;
    if(pNode->id == id)
        return pNode;

    nodeT* ptrNode;
    ptrNode = findNode(pNode->pLeft, id);
    if(ptrNode != NULL)
        return ptrNode;

    return findNode(pNode->pRight, id);
}
void swap(nodeT* pNode)
{
    if(pNode == NULL)
        return ;
    nodeT* aux;
    aux = pNode->pLeft;
    pNode->pLeft = pNode->pRight;
    pNode->pRight = aux;
}

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.in", "w");

    nodeT* pRoot = NULL;
    pRoot = buildTree();

    nodeT* find;
    char c = 'b';
    //fscanf(fin, "%c", &c);

    find = findNode(pRoot, c);
    if(find == NULL)
        fprintf(fout, "Not found");
    else
        swap(pRoot);

    fprintf(fout, "Preorder listing\n");
    showTreePreorder(pRoot, 0);
    fprintf(fout, "\nInorder listing\n");
    showTreeInorder(pRoot, 0);
    fprintf(fout, "\nPostorder listing\n");
    showTreePostorder(pRoot, 0);

    //deleteTree(pRoot);

    fprintf(fout,"\n%d", height(pRoot));
    fprintf(fout,"\n%d", nrLeaves(pRoot));

    return 0;
}
