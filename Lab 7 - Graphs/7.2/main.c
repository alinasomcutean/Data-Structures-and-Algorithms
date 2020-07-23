#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

typedef struct node
{
    int key;
    struct node* next;
}NodeT;

int adjMatrix[100][100], mark[100], nrOfNodes;

typedef struct queue
{
    NodeT* first;
    NodeT* last;
    int count;
}QueueT;

typedef struct stack
{
    NodeT* first;
}StackT;

NodeT* createNode(int key)
{
    NodeT* que = (NodeT*)malloc(sizeof(NodeT));
    if(que)
    {
        que->key = key;
        que->next = NULL;
    }
    return que;
}

QueueT* createQueue()
{
    QueueT* que = (QueueT*)malloc(sizeof(QueueT));
    if(que)
    {
        que->first = NULL;
        que->last = NULL;
        que->count = 0;
    }
    return que;
}

StackT* createStack()
{
    StackT* stack;
    stack = (StackT*)malloc(sizeof(StackT));
    if(stack)
    {
        stack->first = NULL;
    }
    return stack;
}

void enqueue(QueueT** que, int key)
{
    NodeT* p;
    p = createNode(key);
    p->next = NULL;
    if((*que)->last != NULL)
    {
        (*que)->last->next = p;
    }
    else
    {
        (*que)->first = p;
    }
    (*que)->last = p;
    (*que)->count++;
}

int dequeue(QueueT** que)
{
    NodeT* p;
    if((*que)->first != NULL)
    {
        p = (*que)->first;
        (*que)->first = (*que)->first->next;
        (*que)->count--;
        if((*que)->first == NULL)
        {
            (*que)->last = NULL;
        }
        return p->key;
    }
    return 0;
}

enum {UNVISITED, VISITED};

void bfs(int nrOfNodes, int sourceNode)
{
    int mark[nrOfNodes]; ///for marking the visited nodes
    int node;
    QueueT *que = createQueue();
    int i;
    for(i = 0; i < nrOfNodes; i++)
    {
        mark[i] = UNVISITED;
    }
    mark[sourceNode] = VISITED;
    enqueue(&que, sourceNode);
    while(que->first != NULL)
    {
        int v = dequeue(&que);
        fprintf(fout, "%d ", v);
        ///int node;
        for(node = 0; node < nrOfNodes; node++)
        {
            if(adjMatrix[v][node] == 1)
                if(mark[node] == UNVISITED)
            {
                mark[node] = VISITED;
                ///printf("%d ", node);
                enqueue(&que, node);
            }
        }
    }
}

void dfs(int i)
{
    int j;
    fprintf(fout, "%d ", i);
    mark[i] = VISITED;
    for(j = 0; j < nrOfNodes; j++)
    {
        if(mark[j] == UNVISITED && adjMatrix[i][j] == 1)
           {
                dfs(j);
           }
    }
}

void printAdjMatrix(int nrOfNodes)
{
    int i;
    for(i = 0; i < nrOfNodes; i++)
    {
        for(int j = 0; j < nrOfNodes; j++)
        {
            fprintf(fout, "%d ", adjMatrix[i][j]);
        }
        fprintf(fout, "\n");
    }

}

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");
    char c[10];
    int sourceNode;
    int x,y;
    fscanf(fin, "%s", &c);
    fscanf(fin, "%d", &nrOfNodes);
    fscanf(fin, "%s", &c);
    while(fscanf(fin, " (%d %d)", &x, &y) == 2)
    {
        adjMatrix[x][y] = 1;
        adjMatrix[y][x] = 1;
    }
    fscanf(fin, "%d",&sourceNode);
    printAdjMatrix(nrOfNodes);
    fprintf(fout, "\n");
    bfs(nrOfNodes, sourceNode);
    fprintf(fout,"\n");
    for(int i = 0; i < nrOfNodes; i++)
        mark[i] = UNVISITED;
    dfs(sourceNode);
    return 0;
}
