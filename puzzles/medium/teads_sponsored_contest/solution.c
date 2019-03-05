#include <stdlib.h>
#include <stdio.h>
#define MAX 100000

struct Edge {
    int vertex;
    struct Edge * next;
};

struct Edge * AddEdge(struct Edge * currentHead, int newVertex)
{
    struct Edge * newHead
                 = (struct Edge *) malloc(sizeof(struct Edge));
  
    newHead->vertex = newVertex;
    newHead->next = currentHead;
  
    return newHead;
}

int BreadthFirstSearch(
                        struct Edge * adjacencyList[],
                        int vertices,
                        int level[],
                        int startVertex,
                        int option
                       )
{
    struct Edge * traverse;
    int i, lev, flag = 1, id;
    lev = 0;
    level[startVertex] = lev;
  
    while (flag) {
        flag = 0;
        for (i=0; i<=vertices; ++i)
        {
            if (level[i] == lev)
            {
                flag = 1;
                traverse = adjacencyList[i];
                while (traverse != NULL)
                {
                    if (level[traverse->vertex] != -1)
                    {
                        traverse = traverse->next;
                        continue;
                    }
                    level[traverse->vertex] = lev + 1;
                    id = traverse->vertex;
                    traverse = traverse->next;
                }
            }
        }
        ++lev;
    }
    if(option == 2)
    return lev-1;
    else
    return id;
}

int main()
{
    int edges; // the number of adjacency relations
    scanf("%d", &edges);
    int vertices = MAX;
    int max=0;
    
    struct Edge * adjacencyList[vertices + 1];
    
    for (int i=0; i<=vertices; ++i)
    {
        adjacencyList[i] = NULL;
    }
    
    for (int i=0; i<edges; i++)
    {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        if (xi>=yi)
        {
            if(max<xi)
            max = xi;
        }else if(max<=yi)
        {
            max = yi;
        }
        adjacencyList[xi] = AddEdge(adjacencyList[xi], yi);
        adjacencyList[yi] = AddEdge(adjacencyList[yi], xi);
    }
    vertices = max; // assigning max vertex id
    int level[vertices+1];
    for (int i=0; i<=vertices; ++i)
    {
        level[i] = -1;
    }
    int second = BreadthFirstSearch(adjacencyList, vertices, level, max, 1); // option one bfs, returns edge vertex id
    for (int i=0; i<=vertices; ++i)
    {
        level[i] = -1;
    }
    int diameter = BreadthFirstSearch(adjacencyList, vertices, level, second, 2); // option two bfs, returns diameter of graph
    fprintf(stderr,"diameter of graph is %d\n", diameter);
    printf("%d\n", diameter/2);
    return 0;
}