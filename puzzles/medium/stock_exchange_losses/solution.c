#include <stdio.h>
#include <limits.h>

int main()
{
    int n;
    scanf("%d", &n);
    int prev = INT_MAX, max = INT_MIN, loss = 0;
    for (int i=0; i<n; i++) 
    {
        int v;
        scanf("%d", &v);
        if (v > max)
        {
            max = v;
        }
        if (loss > (v - max))
        {
            loss = v - max;
        }
        prev = v;
    }
    printf("%d", loss);
    return 0;
}