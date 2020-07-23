#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;
int adjMatrix[100][100];

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

int main()
{
    fin = fopen("input.in", "r");
    fout = fopen("output", "w");

    char c[10];
    int allNodes[100], node, nrNodes = 0, x,y, subNodes[100], sNodes = 0, sNode;
    fscanf(fin, "%s", &c);
    while(fscanf(fin, " %d", &node) > 0)
    {
        allNodes[nrNodes] = node;
        nrNodes++;
    }
    fscanf(fin, "%s", &c);
    while(fscanf(fin, " (%d %d)", &x, &y) == 2)
    {
        adjMatrix[x][y] = 1;
        adjMatrix[y][x] = 1;
    }
    fscanf(fin, "%s", &c);
    while(fscanf(fin, " %d ", &sNode) != EOF)
    {
        subNodes[sNodes] = sNode;
        sNodes++;
    }
    fprintf(fout, "Arcs ");
    int i,j;
    for( i = 0; i < sNodes-1; i++)
    {
        for( j = i+1; j < sNodes; j++)
        {
            if(adjMatrix[subNodes[i]][subNodes[j]] == 1)
                fprintf(fout, "(%d %d) ", subNodes[i], subNodes[j]);
        }
    }
    return 0;
}
