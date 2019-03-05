#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int n; // the number of temperatures to analyse
    scanf("%d", &n); fgetc(stdin);
    char temps[257]; // the n temperatures expressed as integers ranging from -273 to 5526
    fgets(temps, 257, stdin); // the n temperatures expressed as integers ranging from -273 to 5526
    if (n==0){
        printf("0\n");}
        else{
    int gradusy[n], i;
    char *space;
    for(i=0; i<n; i++){
        if(i==0){
        gradusy[i] = strtol(temps,&space,10);} 
        else if (i==n-1){
            gradusy[i] = strtol(space,NULL,10);}
            else
            gradusy[i] = strtol(space,&space,10);
    }
    
    int result;
    
    result = gradusy[0];
    for(i=0;i<n;i++){
        if (abs(result) > abs(gradusy[i])){
            result = gradusy[i];}
    }
    
    for(i=0;i<n;i++){
        if(abs(result) == abs(gradusy[i])){
            if(gradusy[i] > 0){
                result = gradusy[i];
            }
        }
    }
    printf("%d\n", result);
        }

    return 0;
}