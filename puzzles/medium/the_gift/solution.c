#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int cmpfunc (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}

int main()
{
    int N, giftPrice, sum = 0, avg;
    scanf("%d%d", &N, &giftPrice);
    int budget[N];
    for (int i=0; i<N; i++) 
    {
        scanf("%d", &budget[i]);
        sum += budget[i];
    }
    qsort(budget, N, sizeof(int), cmpfunc);
    
    if (giftPrice > sum)
    {
        printf("IMPOSSIBLE\n");
    } else
    {
        avg = giftPrice/N;
        for (int i=0; i<N; i++)
        {
            if (i != N-1)
            {
                if (budget[i] < avg)
                {
                    printf("%d\n", budget[i]);
                    giftPrice -= budget[i];
                    avg = floor(giftPrice/(N-i-1));
                }else
                {
                    printf("%d\n", avg);
                    giftPrice -= avg;
                    avg = floor(giftPrice/(N-i-1));
                }
            }else
            {
                printf("%d", giftPrice);
            }
        }
    }
    return 0;
}