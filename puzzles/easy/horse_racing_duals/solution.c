#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int compare(const void *p, const void *q) 
{
    int x = *(const int *)p;
    int y = *(const int *)q;

    if (x < y)
        return 1;
    else if (x > y)
        return -1;

    return 0;
}

int main()
{
    int N;
    int d = INT_MAX;
    scanf("%d", &N);
    int horses[N];
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &horses[i]);
    }
    
    qsort(horses, N, sizeof(int), compare);
    
    for (int i=0; i<N-1; i++)
    {
        if (d > horses[i]-horses[i+1])
        {
            d = horses[i]-horses[i+1];
        }
    }
    printf("%d", d);
    return 0;
}