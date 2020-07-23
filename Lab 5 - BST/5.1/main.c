#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char key;
    struct node *left, *right;

} NodeT;

NodeT *root;

NodeT* createnode(char givenkey)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->key=givenkey;
        p->left=p->right=NULL;
    }
    return p;
}

NodeT *insertnode (NodeT *root, char key, FILE *fout)
{
    if(root==NULL)
        root=createnode(key);
    else
    {
        if (key<root->key)
            root->left=insertnode(root->left, key, fout);
        else if (key>root->key)
            root->right=insertnode(root->right, key, fout);
        else
            fprintf(fout, "Node with key %c already exists", key);
    }
    return root;
}

void preorder(NodeT *p, int level, FILE *fout)
{
    int i;
    if(p!=NULL)
    {
        for (i=0; i<=level; i++)
            fprintf(fout, " ");
        fprintf(fout, "%c\n", p->key);
        preorder(p->left, level+1, fout);
        preorder(p->right, level+1, fout);
    }
}

void postorder(NodeT *p, int level, FILE *fout)
{
    int i;
    if(p!=NULL)
    {
        postorder(p->left, level+1, fout);
        postorder(p->right, level+1, fout);
        for (i=0; i<=level; i++)
            fprintf(fout, " ");
        fprintf(fout, "%c\n", p->key);

    }
}

void inorder(NodeT *p, int level, FILE *fout)
{
    int i;
    if(p!=NULL)
    {
        inorder(p->left, level+1, fout);
        for (i=0; i<=level; i++)
            fprintf(fout, " ");
        fprintf(fout, "%c\n", p->key);
        inorder(p->right, level+1, fout);
    }
}

NodeT* findMin(NodeT* node, FILE *fout)
{
    if(node==NULL)
    {
        fprintf(fout, "No element in tree");
        return NULL;
    }
    if(node->left)
        return findMin(node->left, fout);
    else
        return node;

}

NodeT* findMax(NodeT* node, FILE *fout)
{
    if(node==NULL)
    {
        fprintf(fout, "No element in tree");
        return NULL;
    }
    if(node->right)
        return findMax(node->right, fout);
    else
        return node;

}

NodeT* delNode (NodeT* node, char key, FILE *fout)
{
    if(node==NULL)
    {
        fprintf(fout, "Element not found");
    }
    else if(key<node->key)
    {
        node->left=delNode(node->left, key, fout);
    }
    else if(key>node->key)
    {
        node->right=delNode(node->right, key, fout);
    }
    else
    {
        if(node->right && node->left)
        {
            NodeT *temp=findMin(node->right, fout);
            node->key=temp->key;
            node->right=delNode(node->right, temp->key, fout);
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

NodeT *find (NodeT*root, char key)
{
    NodeT *p;
    if(root==NULL)
        return NULL;
    p=root;
    while(p!=NULL)
    {
        if(p->key==key)
            return p;
        else if(key<p->key)
            p=p->left;
        else
            p=p->right;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    fin=fopen(argv[1],"r");
    fout=fopen(argv[2],"w");
    NodeT *p;
    char s, c, x;
    int i;
    while((s=fgetc(fin))!=EOF)
    {
        c=fgetc(fin);
        x=fgetc(fin);
        switch(s)
        {
        case 'i':
        {
            root=insertnode(root, c, fout);
            break;
        }
        case 'd':
        {
            root=delNode(root, c, fout);
            break;
        }
        case 'f':
        {
            p=find(root, c);
            if(p==NULL)
                fprintf(fout, "Node not found\n");
            else
                fprintf(fout, "Node found\n");
            break;
        }
        case 't':
        {
            if(c=='p')
                preorder(root, 0, fout);
            else if(c=='P')
                postorder(root, 0, fout);
            else if(c=='i')
                inorder(root, 0, fout);
            else
                fprintf(fout, "Error\n");
            fprintf(fout, "\n");
            break;
        }
        case 'g':
        {
            if(c=='m')
            {
                p=findMin(root, fout);
                if(p==NULL)
                    fprintf(fout, "Tree empty\n");
                else
                    fprintf(fout, "The minimum val is %c\n", p->key);
                break;
            }
            if(c=='M')
            {
                p=findMax(root, fout);
                if(p==NULL)
                    fprintf(fout, "Tree empty\n");
                else
                    fprintf(fout, "The maximum val is %c\n", p->key);
                break;
            }
        }
        }
    }
    return 0;
}
