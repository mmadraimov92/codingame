#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int W; // number of columns.
    int H; // number of rows.
    scanf("%d%d", &W, &H); fgetc(stdin);
    int map[H][W];
    for (int i = 0; i<H; i++) 
    {
        char LINE[201]; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        fgets(LINE, 201, stdin); // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        
        char *token;
        int j=0;
       /* get the first token */
       token = strtok(LINE, " ");
       
       /* walk through other tokens */
       while( token != NULL ) 
       {
            map[i][j] = atoi(token);
            j++;
            token = strtok(NULL, " ");
       }
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    scanf("%d", &EX);
    // game loop
    while (1) 
    {
        int XI, YI;
        char POS[6];
        scanf("%d%d%s", &XI, &YI, POS);
        
        switch(map[YI][XI])
        {
            case 1:
            case 3:
            case 7:
            case 8:
            case 9:
            case 12:
            case 13:
                printf("%d %d\n", XI, YI+1);
                break;
            case 2:
            case 6:
                if (strcmp(POS, "LEFT") == 0)
                {
                    printf("%d %d\n", XI+1, YI);
                }else if (strcmp(POS, "RIGHT") == 0)
                {
                    printf("%d %d\n", XI-1, YI);
                }else if (strcmp(POS, "TOP") == 0)
                {
                    printf("dead\n");
                }
                break;
            case 4:
            case 10:
                if (strcmp(POS, "TOP") == 0)
                {
                    printf("%d %d\n", XI-1, YI);
                }else if (strcmp(POS, "RIGHT") == 0)
                {
                    printf("%d %d\n", XI, YI+1);
                }else if (strcmp(POS, "LEFT") == 0)
                {
                    printf("dead\n");
                }
                break;
            case 5:
            case 11:
                if (strcmp(POS, "TOP") == 0)
                {
                    printf("%d %d\n", XI+1, YI);
                }else if (strcmp(POS, "LEFT") == 0)
                {
                    printf("%d %d\n", XI, YI+1);
                }
                break;
        }
    }
    return 0;
}