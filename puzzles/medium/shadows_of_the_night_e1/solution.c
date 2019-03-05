#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct direction {
    bool right;
    bool left;
    bool up;
    bool down;
};

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    scanf("%d%d", &W, &H);
    int N; // maximum number of turns before game over.
    scanf("%d", &N);
    int X0, X1, newX;
    int Y0, Y1, newY;
    scanf("%d%d", &X0, &Y0);
    struct direction now;
    bool initial = false;
    bool sw = false;
    // game loop
    while (1) 
    {
        now.right = now.left = now.up = now.down = false;
        char bombDir[4]; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        scanf("%s", bombDir);
        for (int i=0; i<strlen(bombDir); i++)
        {
            if (bombDir[i] == 'U')
            {
                now.up = true;
            }
            if (bombDir[i] == 'D')
            {
                now.down = true;
            }
            if (bombDir[i] == 'L')
            {
                now.left = true;
            }
            if (bombDir[i] == 'R')
            {
                now.right = true;
            }
        }
        if (initial)// next steps
        {
            if (now.right)
            {
                X0 = newX;
            }
            else if (now.left)
            {
                X1 = newX;
            }
            else 
            {
                X0 = newX;
                X1 = newX;
            }
            if (now.up)
            {
                Y1 = newY;
            }
            else if (now.down)
            {
                Y0 = newY;
            }
            else 
            {
                Y0 = newY;
                Y1 = newY;
            }
        }else // very first step
        {
            if (now.right)
            {
                X1 = W-1;
            }
            else if (now.left)
            {
                X1 = 0;
                X1 = X1^X0;
                X0 = X1^X0;
                X1 = X1^X0;
            }
            else 
            {
                X1 = X0;
            }
            if (now.up)
            {
                Y1 = 0;
                Y0 = Y0^Y1;
                Y1 = Y0^Y1;
                Y0 = Y0^Y1;
            }
            else if (now.down)
            {
                Y1 = H-1;
            }
            else 
            {
                Y1 = Y0;
            }
        }
        fprintf(stderr,"X0 = %d X1 = %d\nY0 = %d Y1 = %d\n",X0,X1,Y0,Y1);
        if(!sw)
        {
            newX = ceil((double)(X0+X1)/2);
            newY = ceil((double)(Y0+Y1)/2);
            sw = true;
        }else
        {
            newX = floor((double)(X0+X1)/2);
            newY = floor((double)(Y0+Y1)/2);
            sw = false;
        }
        printf("%d %d\n", newX, newY);
        initial = true;
    }
    return 0;
}