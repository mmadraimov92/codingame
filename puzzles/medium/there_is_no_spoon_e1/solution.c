#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char map[32][32];

int check_horizontal(int j, int i, int width)
{
    for (j=j+1;j<width;j++)
    {
        if (map[i][j] == '0')
        {
            return j;
        }
    }
    return -1;
}

int check_vertical(int i, int j, int height)
{
    fprintf(stderr, "\narg [i][j] = %d%d ", i, j);
    for (i=i+1;i<height;i++)
    {
        fprintf(stderr, "char - %c ", map[i][j]);
        if (map[i][j] == '0')
        {
            fprintf(stderr, "found i = %d", i);
            return i;
        }
    }
    return -1;
}

int main()
{
    int width; // the number of cells on the X axis
    scanf("%d", &width);
    int height; // the number of cells on the Y axis
    scanf("%d", &height); 
    fgetc(stdin);
    //char map[height][width+1];
    
    for (int i = 0; i < height; i++) 
    {
        fgets(map[i], 32, stdin);
    }
    
    for (int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if (map[i][j] == '0')
            {
                printf("%d %d ", j,i);
                int index = check_horizontal(j,i,width);
                if (index == -1)
                {
                    printf("%d %d ", -1, -1);
                }
                else
                {
                    printf("%d %d ", index, i);
                }
                
                index = check_vertical(i,j,height);
                fprintf(stderr, "index = %d", index);
                if (index == -1)
                {
                    printf("%d %d ", -1, -1);
                }
                else
                {
                    printf("%d %d ", j, index);
                }
                printf("\n");
            }
        }
    }
    return 0;
}