#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    scanf("%d", &surfaceN);
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        scanf("%d%d", &landX, &landY);
    }

    // game loop
    while (1) 
    {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        scanf("%d%d%d%d%d%d%d", &X, &Y, &hSpeed, &vSpeed, &fuel, &rotate, &power);
        if (Y < 1650)
        {
            printf("0 4\n");
        }
        else if (Y < 2200)
        {
            printf("0 3\n");
        }
        else if (Y < 2300)
        {
            printf("0 2\n");
        }
        else if (Y < 2450)
        {
            printf("0 1\n");
        }
        else printf("0 0\n");
       
    }

    return 0;
}