#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char value;
    struct node *next[10];
}node;

node *head;

void initialize (node *tmp)
{
    for (int i=0; i<10; i++)
    {
        tmp->next[i] = NULL;
    }
    return;
}

node* addNode (node *last, char value, int *counter)
{
    int v = value - '0';
    if (last->next[v] != NULL)
    {
        last = last->next[v];
        return last;
    }else 
    {
        node *tmp = (node*)malloc(sizeof(node));
        initialize(tmp);
        tmp->value = value;
        last->next[v] = tmp;
        last = tmp;
        (*counter)++;
        return last;
    }
}

int main()
{
    head = (node*)malloc(sizeof(node));
    initialize(head);
    int N, counter = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) 
    {
        node *last = head;
        char telephone[21];
        scanf("%s", telephone);
        for (int i=0; i<strlen(telephone); i++)
        {
            last = addNode(last, telephone[i], &counter);
        }
    }
    printf("%d", counter);
    return 0;
}