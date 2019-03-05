#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXSHIP 3
#define MAXBARREL 26
#define MAXMINE 20
#define MAXCANNONBALL 20

typedef struct coord {
    int x;
    int y;
}Coord;

typedef struct cubecoord {
    int x;
    int y;
    int z;
}Cubecoord;

typedef struct barrel{
    Coord coord;
    int rum;
    bool targeted;
}Barrel;

typedef struct mine{
    Coord coord;
}Mine;

typedef struct cannonball{
    Coord coord;
    int owner;
    int impact;
}Cannonball;

typedef struct ship{
    Coord coord;
    int orientation;
    int speed;
    int health;
}Ship;

enum orientation {right, upright, upleft, left, downleft, downright};
int cannontime[] = {0,1,2,2,2,3,3,3,4,4,4};
     
Barrel barrellist[MAXBARREL];
Mine minelist[MAXMINE];
Ship myshiplist[MAXSHIP];
Ship enemyshiplist[MAXSHIP];
Cannonball cannonballlist[MAXCANNONBALL];

Cubecoord coord_to_cube (int x, int y)
{
    Cubecoord cube;
    cube.x = x-(y-(y&1))/2;
    cube.z = y;
    cube.y = (-1*cube.x)-cube.z;
    return cube;
}

Coord cube_to_coord(Cubecoord cube)
{
    Coord coord;
    coord.x = cube.x+(cube.z-(cube.z&1))/2;
    coord.y = cube.z;
    return coord;
}

int distance(Coord coord1, Coord coord2)
{
    Cubecoord cube1, cube2;
    //convert odd-r to cube
    cube1 = coord_to_cube(coord1.x, coord1.y);
    cube2 = coord_to_cube(coord2.x, coord2.y);
    
    return (abs(cube1.x-cube2.x)+abs(cube1.y-cube2.y)+abs(cube1.z-cube2.z))/2;
}

int cube_distance(Cubecoord cube1, Cubecoord cube2)
{   
    return (abs(cube1.x-cube2.x)+abs(cube1.y-cube2.y)+abs(cube1.z-cube2.z))/2;
}

Cubecoord increment_cube_coord (Cubecoord cube, int orient)
{
    if(orient == right)
    {
        cube.x++;
        cube.y--;
    }else if(orient == upright)
    {
        cube.x++;
        cube.z--;
    }else if(orient == upleft)
    {
        cube.y++;
        cube.z--;
    }else if(orient == left)
    {
        cube.y++;
        cube.x--;
    }else if(orient == downleft)
    {
        cube.x--;
        cube.z++;
    }else if(orient == downright)
    {
        cube.y--;
        cube.z++;
    }
    
    return cube;
}

Coord get_fire_coord (int enemyx, int enemyy, int speed, int enemyorient, int myx, int myy, int myorient)
{
    Cubecoord mycube, enemycube, mycannon;
    mycube = coord_to_cube(myx,myy);
    mycannon = increment_cube_coord(mycube, myorient);
    enemycube = coord_to_cube(enemyx,enemyy);

    for(int t=1; t<=4; t++) // t represents time
    {
        for (int i=1; i<=speed; i++)
        {
            enemycube = increment_cube_coord (enemycube, enemyorient);
        }
        int cubedist = cube_distance(mycannon, enemycube);
        if (t == cannontime[cubedist])
        {
            if(speed)
            {
                enemycube = increment_cube_coord (enemycube, enemyorient);
            }
            Coord firecoord = cube_to_coord(enemycube);
            return firecoord;
        }
    }
}

int main()
{
    while (1)
    {
        int nobarrel = true;
        int myShipCount; // the number of remaining ships
        scanf("%d", &myShipCount);
        int entityCount; // the number of entities (e.g. ships, mines or cannonballs)
        scanf("%d", &entityCount);
        
        int barrelindex = 0, mineindex = 0, myshipindex = 0, enemyshipindex = 0, cannonballindex = 0;
        
        for (int i = 0; i < entityCount; i++)
        {
            int entityId;
            char entityType[11];
            int x, y, arg1, arg2, arg3,arg4;
            scanf("%d%s%d%d%d%d%d%d", &entityId, entityType, &x, &y, &arg1, &arg2, &arg3, &arg4);
            //fprintf(stderr,"%d %s %d %d ori=%d, sp=%d\n",entityId, entityType, x, y, arg1, arg2);
            
            if(strcmp(entityType, "SHIP") == 0)
            {
                if (arg4 == 1)
                {
                    myshiplist[myshipindex].coord.x = x;
                    myshiplist[myshipindex].coord.y = y;
                    myshiplist[myshipindex].orientation = arg1;
                    myshiplist[myshipindex].speed = arg2;
                    myshiplist[myshipindex].health = arg3;
                    myshipindex++;
                }else
                {
                    enemyshiplist[enemyshipindex].coord.x = x;
                    enemyshiplist[enemyshipindex].coord.y = y;
                    enemyshiplist[enemyshipindex].orientation = arg1;
                    enemyshiplist[enemyshipindex].speed = arg2;
                    enemyshiplist[enemyshipindex].health = arg3;
                    enemyshipindex++;
                }
            }
            if(strcmp(entityType, "MINE") == 0)
            {
                minelist[mineindex].coord.x = x;
                minelist[mineindex].coord.y = y;
                mineindex++;
            }
            if(strcmp(entityType, "CANNONBALL") == 0)
            {
                cannonballlist[cannonballindex].coord.x = x;
                cannonballlist[cannonballindex].coord.y = y; 
                cannonballlist[cannonballindex].owner = arg1;
                cannonballlist[cannonballindex].impact = arg2;
                cannonballindex++;
            }
            if(strcmp(entityType, "BARREL") == 0)
            {
                nobarrel = false;
                barrellist[barrelindex].coord.x = x;
                barrellist[barrelindex].coord.y = y;
                barrellist[barrelindex].rum = arg1;
                barrellist[barrelindex].targeted = false;
                barrelindex++;
            }
        }

        for (int i = 0; i < myShipCount; i++)
        {
            int barrelx, barrely, enemyx, enemyy, closestbarrel = INT_MAX, closestenemy = INT_MAX, targetbarrelindex, targetenemyindex;
            
            if(nobarrel)
            {
                for (int j=0; j < enemyshipindex; j++)
                {
                    if(closestenemy >= distance(myshiplist[i].coord, enemyshiplist[j].coord))
                    {
                        enemyx = enemyshiplist[j].coord.x;
                        enemyy = enemyshiplist[j].coord.y;
                        closestenemy = distance(myshiplist[i].coord, enemyshiplist[j].coord);
                        targetenemyindex = j;
                    }
                }
                if(closestenemy <= 7)
                {
                    Coord firecoord = get_fire_coord (enemyx, enemyy, enemyshiplist[targetenemyindex].speed, enemyshiplist[targetenemyindex].orientation, myshiplist[i].coord.x, myshiplist[i].coord.y, myshiplist[i].orientation);
                    fprintf(stderr,"Aiming at %d %d\n",firecoord.x,firecoord.y);
                    if(firecoord.x > 0 && firecoord.y > 0)
                    {
                        printf("FIRE %d %d\n",firecoord.x,firecoord.y);
                    }else
                    {
                        printf("WAIT\n");
                    }
                }else
                {
                    printf("MOVE %d %d\n",enemyx,enemyy);
                }
            }
            else
            {
                for (int j=0; j < barrelindex; j++) //chosing closest barrel
                {
                    if(closestbarrel >= distance(myshiplist[i].coord, barrellist[j].coord) && !barrellist[j].targeted)
                    {
                        barrelx = barrellist[j].coord.x;
                        barrely = barrellist[j].coord.y;
                        closestbarrel = distance(myshiplist[i].coord, barrellist[j].coord);
                        targetbarrelindex = j;
                    }
                }
                barrellist[targetbarrelindex].targeted = true;
                
                for (int j=0; j < enemyshipindex; j++) //chosing closest enemy
                {
                    if(closestenemy >= distance(myshiplist[i].coord, enemyshiplist[j].coord))
                    {
                        enemyx = enemyshiplist[j].coord.x;
                        enemyy = enemyshiplist[j].coord.y;
                        closestenemy = distance(myshiplist[i].coord, enemyshiplist[j].coord);
                        targetenemyindex = j;
                    }
                }
                if(closestenemy <= 7)
                {
                    Coord firecoord = get_fire_coord (enemyx, enemyy, enemyshiplist[targetenemyindex].speed, enemyshiplist[targetenemyindex].orientation, myshiplist[i].coord.x, myshiplist[i].coord.y, myshiplist[i].orientation);
                    fprintf(stderr,"Aiming at %d %d\n",firecoord.x,firecoord.y);
                    if(firecoord.x > 0 && firecoord.y > 0)
                    {
                        printf("FIRE %d %d\n",firecoord.x,firecoord.y);
                    }else
                    {
                        printf("WAIT\n");
                    }
                }else
                {
                    printf("MOVE %d %d\n",barrelx,barrely);
                }
            }
        }
    }

    return 0;
}
