#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin, *fout;

typedef struct node
{
    char name[50];
    int amount;
    float price;
    int dateOfManufacturing;
    int dateOfExpiration;
    struct node* right;
    struct node* left;
} NodeT;

NodeT *createNode(char name[], float price, int amount, int dateMan, int dateExp)
{
    NodeT* p;
    p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->name, name);
        p->price = price;
        p->amount = amount;
        p->dateOfExpiration = dateExp;
        p->dateOfManufacturing = dateMan;
        p->left=p->right=NULL;
    }
    return p;
}

NodeT *insert (NodeT* root, char name[], float price, int amount, int dateMan, int dateExp)
{

    if(root==NULL)
        root=createNode(name, price, amount, dateMan, dateExp);
    else
    {
        if(strcmp(name, root->name)<0)
            root->left=insert(root->left, name, price, amount, dateMan, dateExp);
        else if(strcmp(name, root->name)>0)
            root->right=insert(root->right, name, price, amount, dateMan, dateExp);
        else
            printf("Product named %s already exists\n", name);
    }
    return root;
}

NodeT* findMin(NodeT* node)
{
    if(node==NULL)
    {
        printf("No element in tree");
        return NULL;
    }
    if(node->left)
        return findMin(node->left);
    else
        return node;

}

NodeT* delNode (NodeT* node, char name[])
{
    if(node==NULL)
    {
        printf("Product named %s not found\n", name);
    }
    else if(strcmp(name,node->name)<0)
    {
        node->left=delNode(node->left, name);
    }
    else if(strcmp(name,node->name)>0)
    {
        node->right=delNode(node->right, name);
    }
    else
    {
        if(node->right && node->left)
        {
            NodeT *temp=findMin(node->right);
            strcpy(node->name,temp->name);
            node->right=delNode(node->right, temp->name);
        }
        else
        {
            NodeT *temp=node;
            if(node->left==NULL)
                node=node->right;
            else if (node->right==NULL)
                node=node->left;
            free(temp);
        }

    }
    return node;
}

NodeT *find (NodeT *root, char name[])
{
    NodeT *p;
    if(root==NULL)
        return NULL;
    p=root;
    while(p!=NULL)
    {
        if(strcmp(p->name,name)==0)
            return p;
        else if(strcmp(name,p->name)<0)
            p=p->left;
        else
            p=p->right;
    }
    return NULL;
}

NodeT *replace(NodeT *root, char name[], char replace[], float price, int amount, int dateMan, int dateExp)
{
    NodeT *p=find(root, name);
    if(p)
    {
        strcpy(p->name, replace);
        p->price=price;
        p->amount=amount;
        p->dateOfExpiration=dateExp;
        p->dateOfManufacturing=dateMan;
    }
    else
        printf("Product %s doesn't exist\n", name);
    return p;
}

int rows()
{
    FILE* f=fopen("text.in", "r");
    char c;
    int n=0;
    while((c=fgetc(f))!=EOF)
        if(c=='\n')
            n++;
    return n;
}

NodeT *ec;
NodeT *root;

void preorder ( NodeT *p, int level, FILE* fout)
{
    int i;
    if(p != NULL)
    {
        fprintf(fout, "%s\n",p->name);
        preorder(p->left, level+1, fout);
        preorder(p->right, level+1, fout);
    }
}

int main()
{
    fin = fopen("text.in", "r");
    fout = fopen("text.out", "w");
    NodeT *p;
    char name[50], rep[50], aux[50];
    int amount;
    float price;
    int dateExp;
    int dateMan;
    char c;
    int n=rows();
    int i;
    int date;
    printf("Insert today's date (yyyymmdd): ");
    scanf("%d", &date);
    for(i=1; i<=n; i++)
    {
        c=fgetc(fin);
        switch(c)
        {
        case 'i':
        {
            fscanf(fin, "%s%f %d %d %d", &name, &price, &amount, &dateMan, &dateExp);
            root=insert(root, name, price, amount, dateMan, dateExp);
            if(dateExp < date)
                ec=insert(ec, name, price, amount, dateMan, dateExp);
            break;

        }
        case 'd':
        {
            fscanf(fin, "%s", &name);
            root=delNode(root, name);
            break;
        }
        case 'u':
        {
            fscanf(fin, "%s%s%f %d %d %d", &name, &rep, &price, &amount, &dateMan, &dateExp);
            root=replace(root, name, rep, price, amount, dateMan, dateExp);
            break;
        }
        default:
            printf("Invalid input on row %d\n", i);
            break;
        }
        c=fgetc(fin); //for \n at the end of the row
    }
fprintf(fout, "Expired products:\n");
preorder(ec, 0, fout);
    return 0;
}
