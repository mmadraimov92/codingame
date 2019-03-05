#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    scanf("%d%d%d%d%d%d%d%d", &nbFloors, &width, &nbRounds, &exitFloor, &exitPos, &nbTotalClones, &nbAdditionalElevators, &nbElevators);
    int elevatorPos[nbElevators];
    for (int i = 0; i < nbElevators; i++)
    {
        int elevatorFloor;
        scanf("%d", &elevatorFloor);
        scanf("%d", &elevatorPos[elevatorFloor]);
    }
    for (int i=0; i<nbElevators; i++)
    {
        fprintf(stderr, "elev pos = %d floor = %d\n", elevatorPos[i], i);
    }
    
    bool left = false, right = true; //direction of clones
    bool plusone = false;
    int i=0;
    // game loop
    while (1) {
        int cloneFloor, tmpFloor; // floor of the leading clone
        int clonePos, tmpPos; // position of the leading clone on its floor
        char direction[11]; // direction of the leading clone: LEFT or RIGHT
        scanf("%d%d%s", &cloneFloor, &clonePos, direction);
        fprintf(stderr, "clone = f%d pos%d\n", cloneFloor, clonePos);
        if (cloneFloor == -1)
        {
            printf("WAIT\n");
            continue;
        }
        if (plusone == true)
        {
            printf("WAIT\n");
            plusone = false;
            continue;
        }
        if (cloneFloor == exitFloor)
        {
            fprintf(stderr, "exit pos = %d\n", exitPos);
            fprintf(stderr, "right = %s", right?"true":"false");
            if (exitPos > clonePos && left == true)
            {
                printf("BLOCK\n");
                left = false;
                right = true;
                plusone = true;
                continue;
            }
            if (exitPos >= clonePos && right == true)
            {
                printf("WAIT\n");
                continue;
            }
            if (exitPos <= clonePos && left == true)
            {
                printf("WAIT\n");
                continue;
            }
            if (exitPos < clonePos && right == true)
            {
                printf("BLOCK\n");
                right = false;
                left = true;
                plusone = true;
                continue;
            }
        }else
        {
            fprintf(stderr, "elev = pos%d\n", elevatorPos[cloneFloor]);
            fprintf(stderr, "right = %s", right?"true":"false");
            
            if (elevatorPos[cloneFloor] > clonePos && left == true)
            {
                printf("BLOCK\n");
                left = false;
                right = true;
                plusone = true;
                continue;
            }
            if (elevatorPos[cloneFloor] >= clonePos && right == true)
            {
                printf("WAIT\n");
                continue;
            }
            if (elevatorPos[cloneFloor] <= clonePos && left == true)
            {
                printf("WAIT\n");
                continue;
            }
            if (elevatorPos[cloneFloor] < clonePos && right == true)
            {
                printf("BLOCK\n");
                right = false;
                left = true;
                plusone = true;
                continue;
            }
        }
    }

    return 0;
}