#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 512

typedef struct node {
    bool exitGate;
    int address;
    struct node* next;
}node;

node* addNode (int N2, node *currentHead)
{
    node* newHead = (struct node*) malloc(sizeof(struct node));
   
    newHead->address = N2;
    newHead->next = currentHead;
   
    return newHead;
}

node* deleteNode (int N2, node *currentHead)
{
    node *traverse = currentHead;
    int count = 1;
    while (traverse->address != N2)
    {
        traverse = traverse->next;
        count++;
    }
    fprintf(stderr,"count is %d\n", count);
    node *tmp = traverse->next;
    if (count == 1)
    {
        return traverse->next;
    }else
    {
        node* prev = currentHead;
        for (int i=1; i<count-1; i++)
        {
            prev = prev->next;
        }
        prev->next = tmp;
        return currentHead;
    }
}

void bfsVirus (node *adjacency_list[MAX], int virus, int N)
{
    int level[N+1], parent[N+1];
    int par, lev=0, flag = 1, foundGate = 0, gate;
    node* traverse;
    for (int j=0; j<=N; j++)
    {
        parent[j] = -1;
        level[j] = -1;
    }
    
    level[virus] = lev;
    
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < N; ++i) 
        {
            if (level[i] == lev) 
            {
                flag = 1;
                traverse = adjacency_list[i];
                par = i;
  
                while (traverse != NULL)
                {
                    if (level[traverse->address] != -1)
                    {
                        traverse = traverse->next;
                        continue;
                    }
                    level[traverse->address] = lev + 1;
                    parent[traverse->address] = par;
                    if (traverse->exitGate == true)
                    {
                        gate = traverse->address;
                        foundGate = 1;
                        fprintf(stderr,"found gate = %d parent %d\n", gate, parent[gate]);
                        break;
                    }
                    traverse = traverse->next;
                }
            }
        }
        if (foundGate == 1)
        {
            break;
        }
        ++lev;
    }
    for (int i=0; i<N; i++)
    {
        fprintf(stderr,"node %d parent is %d\n", i, parent[i]);
    }
    printf("%d %d\n", parent[gate], gate);
    adjacency_list[gate] = deleteNode(parent[gate], adjacency_list[gate]);
    adjacency_list[parent[gate]] = deleteNode(gate, adjacency_list[parent[gate]]);
}

int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    scanf("%d%d%d", &N, &L, &E);
    struct node *adjacency_list[N+1];
    for (int i=0; i<=N; ++i) {
        adjacency_list[i] = NULL;
    }
    
    for (int i=0; i<L; i++) {
        int N1, N2; // N1 and N2 defines a link between these nodes
        scanf("%d%d", &N1, &N2);
        //fprintf(stderr,"links %d - %d\n", N1, N2);
        adjacency_list[N1] = addNode(N2, adjacency_list[N1]);
        adjacency_list[N2] = addNode(N1, adjacency_list[N2]);
    }
    for (int i=0; i<E; i++) 
    {
        int EI; // the index of a gateway node
        scanf("%d", &EI);
        fprintf(stderr,"Exit gate %d\n", EI);
        node* traverse = adjacency_list[EI];
        while (traverse != NULL)
        {
            node* crawl = adjacency_list[traverse->address];
            while (crawl->address != EI)
            {
                crawl = crawl->next;
            }
            crawl->exitGate = true;
            traverse = traverse->next;
        }
    }
    
    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        scanf("%d", &SI);
        
        bfsVirus(adjacency_list, SI, N);
    }
    return 0;
}