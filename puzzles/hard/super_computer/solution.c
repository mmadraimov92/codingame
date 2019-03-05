#include <stdio.h>

typedef struct {
    int J;
    int D;
}schedule;

int cmpfunc (const void * a, const void * b)
{
    schedule *listA = (schedule *)a;
    schedule *listB = (schedule *)b;
   return (listA->J - listB->J);
}

int main()
{
    int N, i;
    scanf("%d", &N);
    schedule list[N];
    for (int i=0; i<N; i++)
    {
        scanf("%d%d", &list[i].J, &list[i].D);
    }
    qsort(list, N, sizeof(schedule), cmpfunc);
    schedule prev = {0,0};
    int count = 0;
    for (i=0; i<N; ++i)
    {
        if (prev.J+prev.D <= list[i].J)
        {
            ++count;
            prev = list[i];
        }else
        {
            if(prev.D + prev.J >= list[i].D + list[i].J)
            {
                prev = list[i];
            }
        }
    }
        
    printf("%d", count);
    return 0;
}