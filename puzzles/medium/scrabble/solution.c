#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct{
    int totalvalue;
    char word[8];
    int wordOrder;
}possibleWords;

typedef struct dict
{
    int value;
    char ch;
    bool endofWord;
    int wordOrder;
    struct dict *nextLetter[26];
}dict;

dict *level[7], *head;
possibleWords finalAnswer = {0,"", INT_MAX};

void initialize(dict *tmp)
{
    for (int i=0; i<26; i++)
    {
        tmp->nextLetter[i] = NULL;
    }
}

dict* addNode(dict *last, int value, char ch, int *counter, int *wordOrder)
{
    int index;
    if (ch == '\n')
    {
        last->endofWord = true;
        last->wordOrder = *wordOrder;
        (*wordOrder)++;
        return head;
    }else
    {
        index = ch - 'a'; //position in alphabet - 1
        if (last->nextLetter[index] != NULL)
        {
            last = last->nextLetter[index];
            return last;
        }else
        {
            dict *tmp;
            tmp = (dict*)malloc(sizeof(dict));
            initialize(tmp);
            
            tmp->value = value;
            tmp->ch = ch;
            
            last->nextLetter[index] = tmp;
            last = tmp;
            (*counter)++;
            return last;
        }
    }   
}

void checkDict(dict *last, char letterPool[8], int wordlevel)
{
    char tmpPool[8]="";
    for (int i=0; i<strlen(letterPool); i++)
    {
        strcpy(tmpPool, letterPool);
        int index = tmpPool[i] - 'a';
        if (last->nextLetter[index] != NULL)
        {
            last = last->nextLetter[index];
            level[wordlevel] = last;
            if(last->endofWord == true)
            {
                getWord(wordlevel);
            }
            tmpPool[i] = tmpPool[strlen(tmpPool)-1];
            tmpPool[strlen(tmpPool)-1] = '\0';
            
            checkDict(last, tmpPool, wordlevel+1);
            if (wordlevel == 0)
            {
                last = head;
            }else 
            {
                last = level[wordlevel-1];
            }
        }
    }
    return;
}

void getWord(int wordlevel)
{
    int sumvalue=0, i;
    
    for (i=0; i<=wordlevel; i++)
    {
        sumvalue += level[i]->value;
    }
    if (sumvalue >= finalAnswer.totalvalue)
    {
        if (sumvalue == finalAnswer.totalvalue)
        {
            if (level[i-1]->wordOrder > finalAnswer.wordOrder)
            {
                return;
            }
        }
        i=0;
        for (i=0; i<=wordlevel; i++)
        {
            finalAnswer.word[i] = level[i]->ch;
        }
        finalAnswer.wordOrder = level[i-1]->wordOrder;
        finalAnswer.totalvalue = sumvalue;
        finalAnswer.word[wordlevel+1] = '\0';       
    }
    return;
}

int main()
{
    int counter=0;
    int wordOrder = 1;
    dict *last;
    head = (dict*)malloc(sizeof(dict));
    initialize(head);
    int N, value;
    int wordlevel=0;
    
    scanf("%d", &N); fgetc(stdin);
    for (int i = 0; i < N; i++) 
    {
        last = head;
        char W[31];
        fgets(W, 31, stdin);
        if (strlen(W) > 8)
        {
            continue;
        }
        for(int i=0; i<strlen(W);i++)
        {
            if (W[i] == 'e' || W[i] == 'a' || W[i] == 'i' || W[i] == 'o' || W[i] == 'n' || W[i] == 'r' || W[i] == 't' || W[i] == 'l' || W[i] == 's' || W[i] == 'u')
            {
                value = 1;
            }else if (W[i] == 'd' || W[i] == 'g')
            {
                value = 2;
            }else if (W[i] == 'b' || W[i] == 'c' || W[i] == 'm' || W[i] == 'p')
            {
                value = 3;
            }else if (W[i] == 'f' || W[i] == 'h' || W[i] == 'v' || W[i] == 'w' || W[i] == 'y')
            {
                value = 4;
            }else if (W[i] == 'k')
            {
                value = 5;
            }else if (W[i] == 'j' || W[i] == 'x')
            {
                value = 8;
            }else 
            {
                value = 10; // for 'q' and 'z'
            }
            last = addNode(last,value,W[i], &counter, &wordOrder);
        }
    }
    char LETTERS[9];
    fgets(LETTERS, 9, stdin);
    LETTERS[strlen(LETTERS)-1] = '\0';
    checkDict(head, LETTERS, wordlevel);
    printf("%s\n", finalAnswer.word);
    return 0;
}