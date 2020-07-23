#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;
int n;

int max(int a, int b, int c)
{
    if(a >= b && a >= c)
        return a;
    if(b >= a && b >= c)
        return b;
    if(c >= a && c >= b)
        return c;
}

int maxSum(int v[], int last)
{
    if(last > 1)
    {
        int mid = last/2;
        int i;
        int sumLeft = maxSum(v, mid);
        int sumRight = maxSum(v + mid, last - mid);
        int maxLeftSum = v[mid-1];
        int leftSum = v[mid-1];
        for(i = mid-2; i >= 0; i--)
        {
            leftSum = leftSum + v[i];
            if(maxLeftSum < leftSum)
                maxLeftSum = leftSum;
        }
        int maxRightSum = v[mid];
        int rightSum = v[mid];
        for(i = mid+1; i<= last; i++)
        {
            rightSum = rightSum + v[i];
            if(maxRightSum < rightSum)
                maxRightSum = rightSum;
        }
        if(maxLeftSum > sumLeft)
            sumLeft = maxLeftSum;
        if(maxRightSum > sumRight)
            sumRight = maxRightSum;
        return max(sumLeft, sumRight, maxLeftSum + maxRightSum);
    }
    return -9999;
}

int main()
{

    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");

    fscanf(fin, "%d", &n);
    int v[n];
    for(int i = 0; i < n; i++)
        fscanf(fin, "%d", &v[i]);

    fprintf(fout, "%d", maxSum(v,n-1));
    return 0;
}
