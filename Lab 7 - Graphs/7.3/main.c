#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;
int adjMatrix[100][100] = {0};

void printAdjMatrix(int nrOfNodes)
{
    int i;
    for(i = 1; i <= nrOfNodes; i++)
    {
        for(int j = 1; j <= nrOfNodes; j++)
        {
            fprintf(fout, "%d ", adjMatrix[i][j]);
        }
        fprintf(fout, "\n");
    }

}
int node;

int minimal(int nrOfNodes, int sourceNode)
{
    int cost = 100;
    for(int i = 1; i <= nrOfNodes; i++)
    {
        if(adjMatrix[sourceNode][i] < cost && adjMatrix[sourceNode][i] != 0)
            {
                cost = adjMatrix[sourceNode][i];
                node = i;
            }
    }
    return cost;
}

int path = 0, distance = 0, nodes[100] = {0}, dist[100] = {100};

void dijkstra(int nrOfNodes, int sourceNode)
{
    int cost;
    cost = minimal(nrOfNodes, sourceNode);
    while(cost != 100)
    {
        distance = distance + cost;
        nodes[path] = node;
        dist[path] = cost;
        path++;
        cost = minimal(nrOfNodes, node);
    }
}

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("input.out", "w");

    int n1,n2,n3,nrOfNodes = 0, sourceNode,i;
    while(fscanf(fin, "%d,%d=%d", &n1,&n2,&n3) != EOF)
    {
        adjMatrix[n1][n2] = n3;
        if(n1 > n2)
            nrOfNodes = n1;
        else
            nrOfNodes = n2;
    }
    sourceNode = n1;
    dijkstra(nrOfNodes, sourceNode);
    fprintf(fout, "%d ", distance);
    fprintf(fout, "%d-", sourceNode);
    for(i = 0; i < path-1; i++)
    {
        fprintf(fout, "%d-", nodes[i]);
    }
    fprintf(fout, "%d ", nodes[path-1]);
    fprintf(fout, "(%d,", dist[0]);
    for(i = 1; i < path-1; i++)
    {
        fprintf(fout, "%d,", dist[i]);
    }
    fprintf(fout, "%d)", dist[path-1]);
    return 0;
}
