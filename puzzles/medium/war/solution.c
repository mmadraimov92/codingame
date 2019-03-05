#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node {
	char card;
	struct Node* next;
};

struct Node* front[2] = {NULL, NULL};
struct Node* rear[2] = {NULL, NULL};

char deck[] = "234567891JQKA";

// To Enqueue a string
void Enqueue(char x, int i) 
{
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
	temp->card = x; 
	temp->next = NULL;
	if(front[i] == NULL && rear[i] == NULL){
		front[i] = rear[i] = temp;
		return;
	}
	rear[i]->next = temp;
	rear[i] = temp;
}

// To Dequeue a string
void Dequeue(int i) 
{
	struct Node* temp = front[i];
	if(front == NULL) 
	{
		return 'E';
	}
	if(front[i] == rear[i]) 
	{
		front[i] = rear[i] = NULL;
	}
	else 
	{
		front[i] = front[i]->next;
	}
	free(temp);
}

char* Front(int i) 
{
	if(front[i] == NULL) 
	{
		return 'E';
	}
	return front[i]->card;
}

int battle(char cardp1[52], char cardp2[52], int *num1, int *num2)
{   
    int winner;
    int index[2];
    
    if (Front(0) == 'E' || Front(1) == 'E')
    {
        printf("PAT");
        return -1;
    }
    cardp1[(*num1)++] = Front(0);
    cardp2[(*num2)++] = Front(1);
    
    Dequeue(0);
    Dequeue(1);
 
    for(int i=0; i<strlen(deck);i++)
    {
        if(deck[i] == cardp1[(*num1)-1])
        {
            index[0] = i;
        }
        if(deck[i] == cardp2[(*num2)-1])
        {
            index[1] = i;
        }
    }
    
    if (index[0] == index[1])
    {
        for(int i=0; i<3;i++)
        {
            cardp1[(*num1)++] = Front(0);
            cardp2[(*num2)++] = Front(1);
            if (Front(0) == 'E' || Front(1) == 'E')
            {
                printf("PAT");
                return -1;
            }
            Dequeue(0);
            Dequeue(1);
        }
        winner = battle(cardp1, cardp2, num1, num2);
        return winner;
    }
    else if(index[0] > index[1])
    {
        for(int i=0; i<(*num1);i++)
        {
            Enqueue(cardp1[i], 0);
        }
        for(int i=0; i<(*num2);i++)
        {
            Enqueue(cardp2[i], 0);
        }
        winner = 1;
        return winner;
    }
    else if(index[0] < index[1])
    {
        for(int i=0; i<*num1;i++)
        {
            Enqueue(cardp1[i], 1);
        }
        for(int i=0; i<*num2;i++)
        {
            Enqueue(cardp2[i], 1);
        }
        winner = 2;
        return winner;
    }
    
}

int main()
{
    int n; // the number of cards for player 1
    int gameround = 0, winner;
    
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        char card[4]; // the n cards of player 1
        scanf("%s", card);
        Enqueue(card[0], 0);
    }
    int m; // the number of cards for player 2
    scanf("%d", &m);
    for (int i = 0; i < m; i++) 
    {
        char card[4]; // the m cards of player 2
        scanf("%s", card);
        Enqueue(card[0], 1);
    }
    while(1)
    {
        int num1 = 0, num2 = 0;
        char cardp1[52], cardp2[52];
        winner = battle(cardp1, cardp2, &num1, &num2);
        gameround++;
        if(Front(0) == 'E' || Front(1) == 'E')
        {
            break;
        }
    }
    if(winner != -1)
    {
        printf("%d %d", winner, gameround);
    }
    return 0;
}