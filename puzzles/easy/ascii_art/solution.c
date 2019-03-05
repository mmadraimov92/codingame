#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char dict[27] = "abcdefghijklmnopqrstuvwxyz?";
    int dictnum[27];
    for(int i=0;i<27;i++)
    {
        dictnum[i] = i+1;
    }
    
    int L;
    scanf("%d", &L);
    int H;
    scanf("%d", &H); 
    fgetc(stdin);
    char T[257];
    fgets(T, 257, stdin);
    for (int i=0;T[i];i++)
    {
        T[i] = tolower(T[i]);
    }
    for (int i = 0; i < H; i++) 
    {
        int check = 0;
        char ROW[1025];
        fgets(ROW, 1025, stdin);
        
        for(int k=0;k<strlen(T)-1;k++)
        {
            for(int j=0;j<27;j++)
            {
                if(dict[j] == T[k])
                {
                    for(int x=(dictnum[j]-1)*L; x<dictnum[j]*L;x++)
                    {
                        printf("%c", ROW[x]);
                    }
                }
            }
            if (isalpha(T[k]) == 0)
            {
                for(int x=26*L;x<27*L;x++)
                {
                    printf("%c", ROW[x]);
                }
            }
        }
        
        printf("\n");
    }
    return 0;
}