#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_GHOST 28
#define MAX_BUSTER 5

struct Entity{
    int xCor;
    int yCor;
    int value;
    int state;
    bool capture;
};

struct TrackingSystem{
    bool gobase;
    int ghostId;
    int ghostX;
    int ghostY;
    int opId;
    int opX;
    int opY;
};

typedef struct checkpoints{
    struct checkpoint{
        bool status;
        int xCor[2]; // [0] baseUP true
        int yCor[2]; // [1] baseUP false
    }checkpoint[5];
}checkpoints;

struct Entity *ghostList[MAX_GHOST];
struct Entity *myBusterList[MAX_BUSTER];
struct Entity *opBusterList[MAX_BUSTER];
int stunCounter[MAX_BUSTER] = {0};

checkpoints check4two[2] = {{false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10}}};

checkpoints check4three[3] = {{false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{143,15},{73,14},false,{},{},false,{},{},false,{},{},false,{},{}}};

checkpoints check4four[4] = {{false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10}},
                            {false,{15,140},{72,10},false,{143,10},{78,10}}};

checkpoints check4five[5] = {{false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10},false,{143,10},{10,72},false,{66,100},{10,70},false,{143,10},{77,11}},
                            {false,{15,140},{72,10},false,{143,10},{78,10}},
                            {false,{15,140},{72,10},false,{143,10},{78,10}}};

double distCord(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x1-x2), 2) + pow((y1-y2), 2));
}

bool stunChecker(int busterId, bool used, bool turn)
{
    if (turn == true)
    {
        for (int i=0; i<MAX_BUSTER; i++)
        {
            if (stunCounter[i] > 0)
            {
                stunCounter[i] -= 1;
            }
        }
    }
    if (used == true)
    {
        fprintf(stderr, "%d used stun\n", busterId);
        stunCounter[busterId] = 20;
    }
    if (stunCounter[busterId] <= 0)
    {
        return true;
    }else
    {
        fprintf(stderr, "%d recahrging stun %d\n", busterId, stunCounter[busterId]);
        return false;
    }
}

struct TrackingSystem checkTarget(int busterId)
{
    double ghostDistance = 9999;
    struct TrackingSystem target = {false, -1,-1,-1,-1,-1,-1};

    if (myBusterList[busterId]->state == 1)
    {
        target.gobase = true;
        target.ghostId = myBusterList[busterId]->value;
        return target;
    }

    for (int i=0; i<MAX_GHOST; i++)
    {
        if (ghostList[i] != NULL)
        {
            if (ghostDistance >= distCord(myBusterList[busterId]->xCor, myBusterList[busterId]->yCor, ghostList[i]->xCor, ghostList[i]->yCor)
            && 3000>distCord(myBusterList[busterId]->xCor, myBusterList[busterId]->yCor, ghostList[i]->xCor, ghostList[i]->yCor))
            {
                ghostDistance = distCord(myBusterList[busterId]->xCor, myBusterList[busterId]->yCor, ghostList[i]->xCor, ghostList[i]->yCor);
                target.ghostId = i;
                target.ghostX = ghostList[i]->xCor;
                target.ghostY = ghostList[i]->yCor;
            }
        }
    }

    double opDistance = 9999;
    for (int i=0; i<MAX_BUSTER; i++)
    {
        if (opBusterList[i] != NULL)
        {
            if ( opDistance >= distCord(myBusterList[busterId]->xCor, myBusterList[busterId]->yCor, opBusterList[i]->xCor, opBusterList[i]->yCor)
            && 3000 >= distCord(myBusterList[busterId]->xCor, myBusterList[busterId]->yCor, opBusterList[i]->xCor, opBusterList[i]->yCor)
            && (opBusterList[i]->state == 1 || opBusterList[i]->state == 3))
            {
                opDistance = distCord(myBusterList[busterId]->xCor, myBusterList[busterId]->yCor, opBusterList[i]->xCor, opBusterList[i]->yCor);
                target.opId = i;
                target.opX = opBusterList[i]->xCor;
                target.opY = opBusterList[i]->yCor;
            }
        }
    }
    fprintf(stderr,"%d -> buster id=%d, ghost id=%d\n", busterId, target.opId, target.ghostId);
    return target;
}

void where2move(int bustersPerPlayer, int busterId, bool baseUP)
{
    switch (bustersPerPlayer)
    {
        case 2:
            for (int i=0; i<5; i++)
            {
                if(baseUP == false)
                {
                    if (myBusterList[busterId]->xCor == check4two[busterId].checkpoint[i].xCor[1]*100 && myBusterList[busterId]->yCor == check4two[busterId].checkpoint[i].yCor[1]*100)
                    {
                        if ((i == 4 && busterId == 0) || (i == 1 && busterId == 1))
                        {
                            fprintf(stderr, "id=%d reached end\n", busterId);
                        }else
                        {
                            check4two[busterId].checkpoint[i].status = true;
                            fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                        }
                    }
                }
                else if (myBusterList[busterId]->xCor == check4two[busterId].checkpoint[i].xCor[0]*100 && myBusterList[busterId]->yCor == check4two[busterId].checkpoint[i].yCor[0]*100)
                {
                    if ((i == 4 && busterId == 0) || (i == 1 && busterId == 1))
                    {
                        fprintf(stderr, "id=%d reached end\n", busterId);
                    }else
                    {
                        check4two[busterId].checkpoint[i].status = true;
                        fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                    }
                }
            }
            if (baseUP == false)
            {
                for (int i=0; i<5; i++)
                {
                    if (check4two[busterId].checkpoint[i].status == false)
                    {
                        printf("MOVE %d %d\n", check4two[busterId].checkpoint[i].xCor[1]*100, check4two[busterId].checkpoint[i].yCor[1]*100);
                        break;
                    }
                }
            }
            else for (int i=0; i<5; i++)
            {
                if (check4two[busterId].checkpoint[i].status == false)
                {
                    printf("MOVE %d %d\n", check4two[busterId].checkpoint[i].xCor[0]*100, check4two[busterId].checkpoint[i].yCor[0]*100);
                    break;
                }
            }break;
        case 3:
            for (int i=0; i<5; i++)
            {
                if(baseUP == false)
                {
                    if (myBusterList[busterId]->xCor == check4three[busterId].checkpoint[i].xCor[1]*100 && myBusterList[busterId]->yCor == check4three[busterId].checkpoint[i].yCor[1]*100)
                    {
                        if ((i == 4 && (busterId == 0 || busterId == 1)) || (i == 0 && busterId == 2))
                        {
                            fprintf(stderr, "id=%d reached end\n", busterId);
                        }else
                        {
                            check4three[busterId].checkpoint[i].status = true;
                            fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                        }
                    }
                }
                else if (myBusterList[busterId]->xCor == check4three[busterId].checkpoint[i].xCor[0]*100 && myBusterList[busterId]->yCor == check4three[busterId].checkpoint[i].yCor[0]*100)
                {
                    if ((i == 4 && (busterId == 0 || busterId == 1)) || (i == 0 && busterId == 2))
                    {
                        fprintf(stderr, "id=%d reached end\n", busterId);
                    }else
                    {
                        check4three[busterId].checkpoint[i].status = true;
                        fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                    }
                }
            }
            if (baseUP == false)
            {
                for (int i=0; i<5; i++)
                {
                    if (check4three[busterId].checkpoint[i].status == false)
                    {
                        printf("MOVE %d %d\n", check4three[busterId].checkpoint[i].xCor[1]*100, check4three[busterId].checkpoint[i].yCor[1]*100);
                        break;
                    }
                }
            }
            else for (int i=0; i<5; i++)
            {
                if (check4three[busterId].checkpoint[i].status == false)
                {
                    printf("MOVE %d %d\n", check4three[busterId].checkpoint[i].xCor[0]*100, check4three[busterId].checkpoint[i].yCor[0]*100);
                    break;
                }
            }break;
        case 4:
            for (int i=0; i<5; i++)
            {
                if(baseUP == false)
                {
                    if (myBusterList[busterId]->xCor == check4four[busterId].checkpoint[i].xCor[1]*100 && myBusterList[busterId]->yCor == check4four[busterId].checkpoint[i].yCor[1]*100)
                    {
                        if ((i == 4 && (busterId == 0 || busterId == 1)) || (i == 1 && (busterId == 2 || busterId == 3)))
                        {
                            fprintf(stderr, "id=%d reached end\n", busterId);
                        }else
                        {
                            check4four[busterId].checkpoint[i].status = true;
                            fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                        }
                    }
                }
                else if (myBusterList[busterId]->xCor == check4four[busterId].checkpoint[i].xCor[0]*100 && myBusterList[busterId]->yCor == check4four[busterId].checkpoint[i].yCor[0]*100)
                {
                    if ((i == 4 && (busterId == 0 || busterId == 1)) || (i == 1 && (busterId == 2 || busterId == 3)))
                    {
                        fprintf(stderr, "id=%d reached end\n", busterId);
                    }else
                    {
                        check4four[busterId].checkpoint[i].status = true;
                        fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                    }
                }
            }
            if (baseUP == false)
            {
                for (int i=0; i<5; i++)
                {
                    if (check4four[busterId].checkpoint[i].status == false)
                    {
                        printf("MOVE %d %d\n", check4four[busterId].checkpoint[i].xCor[1]*100, check4four[busterId].checkpoint[i].yCor[1]*100);
                        break;
                    }
                }
            }
            else for (int i=0; i<5; i++)
            {
                if (check4four[busterId].checkpoint[i].status == false)
                {
                    printf("MOVE %d %d\n", check4four[busterId].checkpoint[i].xCor[0]*100, check4four[busterId].checkpoint[i].yCor[0]*100);
                    break;
                }
            }break;
        case 5:
             for (int i=0; i<5; i++)
            {
                if(baseUP == false)
                {
                    if (myBusterList[busterId]->xCor == check4five[busterId].checkpoint[i].xCor[1]*100 && myBusterList[busterId]->yCor == check4five[busterId].checkpoint[i].yCor[1]*100)
                    {
                        if ((i == 4 && (busterId == 0 || busterId == 1 || busterId == 2)) || (i == 1 && (busterId == 4 || busterId == 3)))
                        {
                            fprintf(stderr, "id=%d reached end\n", busterId);
                        }else
                        {
                            check4five[busterId].checkpoint[i].status = true;
                            fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                        }
                    }
                }
                else if (myBusterList[busterId]->xCor == check4five[busterId].checkpoint[i].xCor[0]*100 && myBusterList[busterId]->yCor == check4five[busterId].checkpoint[i].yCor[0]*100)
                {
                    if ((i == 4 && (busterId == 0 || busterId == 1 || busterId == 2)) || (i == 1 && (busterId == 4 || busterId == 3)))
                    {
                        fprintf(stderr, "id=%d reached end\n", busterId);
                    }else
                    {
                        check4five[busterId].checkpoint[i].status = true;
                        fprintf(stderr, "id=%d reached checkpoint\n", busterId);
                    }
                }
            }
            if (baseUP == false)
            {
                for (int i=0; i<5; i++)
                {
                    if (check4five[busterId].checkpoint[i].status == false)
                    {
                        printf("MOVE %d %d\n", check4five[busterId].checkpoint[i].xCor[1]*100, check4five[busterId].checkpoint[i].yCor[1]*100);
                        break;
                    }
                }
            }
            else for (int i=0; i<5; i++)
            {
                if (check4five[busterId].checkpoint[i].status == false)
                {
                    printf("MOVE %d %d\n", check4five[busterId].checkpoint[i].xCor[0]*100, check4five[busterId].checkpoint[i].yCor[0]*100);
                    break;
                }
            }break;
    }
    return;
}

void taskManager (int bustersPerPlayer, bool baseUP, int move)
{
    int baseX = 0, baseY = 0;
    if (baseUP == false)
    {
        baseX = 16000;
        baseY = 9000;
    }
    fprintf(stderr,"move = %d\n", move);
    for (int i=0; i<bustersPerPlayer; i++)
    {
        char *where;
        struct TrackingSystem target;
        target = checkTarget(i);
        // ==================================================== GOING BASE =======================================================================
        if (target.gobase == true)
        {
            if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, baseX, baseY) >= 1600)
            {
                printf("MOVE %d %d\n", baseX, baseY);
            }else
            {
                printf("RELEASE\n");
            }
        }
        //=============================================== NO GHOST, CHECK BUSTER STATE 1 OR 3 ====================================================
        else if (target.ghostId == -1)
        {
            if (baseUP == false)
            {
                if (target.opId != -1)
                {
                    if(stunChecker(i,false,false) == true
                    && 1760 >= distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, opBusterList[target.opId]->xCor, opBusterList[target.opId]->yCor))
                    {
                        printf("STUN %d\n", target.opId);
                        stunChecker(i,true,false);
                    }else printf("MOVE %d %d\n", target.opX, target.opY);
                }else
                {
                    where2move(bustersPerPlayer,i,baseUP);
                }
            }else if (target.opId != -1)
                {
                    if(stunChecker(i,false,false) == true
                    && 1760 >= distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, opBusterList[target.opId]->xCor, opBusterList[target.opId]->yCor))
                    {
                        printf("STUN %d\n", target.opId + bustersPerPlayer);
                        stunChecker(i,true,false);
                    }else printf("MOVE %d %d\n", target.opX, target.opY);
                }else
                {
                    where2move(bustersPerPlayer,i,baseUP);
                }
        }
        //================================================ TARGETIN GHOST AND OPPONENT BUSTERS ====================================================
        else
        {
            if (baseUP == false)
            {
                if (target.opId != -1)
                {
                    if(stunChecker(i,false,false) == true
                    && 1760 >= distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, opBusterList[target.opId]->xCor, opBusterList[target.opId]->yCor))
                    {
                        printf("STUN %d\n", target.opId);
                        stunChecker(i,true,false);
                    }else if (stunChecker(i,false,false) == true
                    && 1760 < distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, opBusterList[target.opId]->xCor, opBusterList[target.opId]->yCor))
                    {
                        printf("MOVE %d %d\n", target.opX, target.opY);
                    }else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) < 900)
                    {
                        printf("MOVE %d %d\n", baseX, baseY);
                    }
                    else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) <= 1750)
                    {
                        printf("BUST %d\n", target.ghostId);
                        ghostList[target.ghostId]->capture = true;
                    }else printf("MOVE %d %d\n", target.ghostX, target.ghostY);
                }else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) < 900)
                {
                    printf("MOVE %d %d\n", baseX, baseY);
                }
                else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) <= 1750)
                {
                    printf("BUST %d\n", target.ghostId);
                    ghostList[target.ghostId]->capture = true;
                }else printf("MOVE %d %d\n", target.ghostX, target.ghostY);
            }
            else if (target.opId != -1)
            {
                if(stunChecker(i,false,false) == true
                && 1760 >= distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, opBusterList[target.opId]->xCor, opBusterList[target.opId]->yCor))
                {
                    printf("STUN %d\n", target.opId + bustersPerPlayer);
                    stunChecker(i,true,false);
                }else if (stunChecker(i,false,false) == true
                && 1760 < distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, opBusterList[target.opId]->xCor, opBusterList[target.opId]->yCor))
                {
                    printf("MOVE %d %d\n", target.opX, target.opY);
                }else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) < 900)
                {
                    printf("MOVE %d %d\n", baseX, baseY);
                }
                else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) <= 1750)
                {
                    printf("BUST %d\n", target.ghostId);
                    ghostList[target.ghostId]->capture = true;
                }else printf("MOVE %d %d\n", target.ghostX, target.ghostY);
            }
            else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) < 900)
            {
                printf("MOVE %d %d\n", baseX, baseY);
            }
            else if (distCord(myBusterList[i]->xCor, myBusterList[i]->yCor, target.ghostX, target.ghostY) <= 1750)
            {
                printf("BUST %d\n", target.ghostId);
                ghostList[target.ghostId]->capture = true;
            }else printf("MOVE %d %d\n", target.ghostX, target.ghostY);
        }
    }
    for (int i=0; i<MAX_GHOST; i++)
    {
        if (ghostList[i] !=NULL && ghostList[i]->capture == true)
        {
            ghostList[i] = NULL;
        }
    }
    stunChecker(-1, false, true);
    return;
}

int main()
{
    for (int i=0; i<MAX_GHOST; i++)
    {
        ghostList[i] = NULL;
    }

    bool baseUP = true;//position of base
    int bustersPerPlayer; // the amount of busters you control
    scanf("%d", &bustersPerPlayer);
    int ghostCount; // the amount of ghosts on the map
    scanf("%d", &ghostCount);
    int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right
    scanf("%d", &myTeamId);
    if (myTeamId == 1)
    {
        baseUP = false;
    }
    int move = 0;
    // game loop
    while (1)
    {
        for (int i=0; i<MAX_BUSTER; i++)
        {
            opBusterList[i] = NULL;
            myBusterList[i] = NULL;
        }
        int entities; // the number of busters and ghosts visible to you
        scanf("%d", &entities);
        for (int i=0; i<entities; i++)
        {
            int entityId; // buster id or ghost id
            int x, y; // position of this buster / ghost
            int entityType; // the team id if it is a buster, -1 if it is a ghost.
            int state; // For busters: 0=idle, 1=carrying a ghost.
            int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.
            scanf("%d%d%d%d%d%d", &entityId, &x, &y, &entityType, &state, &value);
            fprintf(stderr, "id=%d x=%d y=%d type=%d state=%d value=%d\n", entityId, x ,y, entityType, state, value);
            if (baseUP == false)
            {
                if (entityType == 1)
                {entityType = 0;}
                else if (entityType == 0)
                {entityType = 1;}
            }
            if (entityType == -1)
            {
                if (ghostList[entityId] == NULL)
                {
                    ghostList[entityId] = (struct Entity*)malloc(sizeof(struct Entity));
                }
                ghostList[entityId]->xCor = x;
                ghostList[entityId]->yCor = y;
                ghostList[entityId]->state = state;
                ghostList[entityId]->capture = false;
            }else if (entityType == 0)
            {
                if (baseUP == false)
                {
                    entityId -= bustersPerPlayer;
                }
                if (myBusterList[entityId] == NULL)
                {
                    myBusterList[entityId] = (struct Entity*)malloc(sizeof(struct Entity));
                }
                myBusterList[entityId]->xCor = x;
                myBusterList[entityId]->yCor = y;
                myBusterList[entityId]->value = value;
                myBusterList[entityId]->state = state;
            }else
            {
                if (baseUP == true)
                {
                    entityId -= bustersPerPlayer;
                }
                if (opBusterList[entityId] == NULL)
                {
                    opBusterList[entityId] = (struct Entity*)malloc(sizeof(struct Entity));
                }
                opBusterList[entityId]->xCor = x;
                opBusterList[entityId]->yCor = y;
                opBusterList[entityId]->value = value;
                opBusterList[entityId]->state = state;
            }
        }
        move += 2;
        taskManager(bustersPerPlayer,baseUP, move);
    }
    return 0;
}
