#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int person;
    int id;
    struct node *next;
}node;

node* front = NULL;
node* rear = NULL;

long int memoProfit[50000] = {NULL};
node* memoEndId[50000] = {NULL};

void Enqueue(int x, int id) 
{
	node* temp = (node*)malloc(sizeof(node));
	temp->person = x;
	temp->id = id;
	temp->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

void Dequeue() 
{
	node* temp = front;
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}
	Enqueue(temp->person, temp->id);
}

void specialDequeue(int startId) 
{
    node *tmp = memoEndId[startId];
	rear->next = front;
	front = tmp->next;
	tmp->next = NULL;
	rear = tmp;
}

int main()
{
    int L; //place number
    int C; //number per day
    int N; // number of groups
    scanf("%d%d%d", &L, &C, &N);
    for (int i=0; i<N; i++)
    {
        int Pi;
        scanf("%d", &Pi);
        Enqueue(Pi, i);
    }
    
    long int profit=0;
    
    for (int i=0; i<C; i++)
    {
        int tmpN = 0;
        int tmpL = L;
        int startId;
        unsigned long long int stepProfit = 0;
        
        if (memoProfit[front->id] != NULL)
        {
            profit += memoProfit[front->id];
            specialDequeue(front->id);
        }else 
        {
            startId = front->id;
            while (tmpL >= front->person && tmpN < N)
            {
                tmpL -= front->person;
                stepProfit += front->person;
                memoEndId[startId] = front;
                Dequeue();
                tmpN++;
            }
            profit += stepProfit;
            memoProfit[startId] = stepProfit;
        }
    }
    printf("%ld", profit);
    return 0;
}