#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define pi 3.14159265

typedef struct{
    int id;
    char name[51];
    char address[51];
    char telnum[21];
    char longitude[21];
    char latitude[21];
}defib;

void comma2dot(char *sample)
{
    for (int i=0; i<strlen(sample); i++)
    {
        if (sample[i] == ',')
        {
            sample[i] = '.';
            break;
        }
    }
}

int main()
{
    char LON[51];
    scanf("%s", LON);
    comma2dot(LON);
    double lon = strtod(LON, NULL)*pi/180;
    char LAT[51];
    scanf("%s", LAT);
    comma2dot(LAT);
    double lat = strtod(LAT, NULL)*pi/180;
    int N;
    scanf("%d", &N); 
    defib defibrilators[N];
    double radians[N][2];
    
    fgetc(stdin);
    for (int i = 0; i < N; i++) 
    {
        int p=0;
        char id[5];
        char DEFIB[257];
        fgets(DEFIB, 257, stdin);
        fprintf(stderr, "%s\n", DEFIB);
        
        sscanf(DEFIB, "%d[^;];", &defibrilators[i].id);
        sprintf(id, "%d", defibrilators[i].id);
        p = strlen(id)+1;
        sscanf(DEFIB+p, "%[^;];",  defibrilators[i].name);
        p = p + strlen(defibrilators[i].name)+1;
        sscanf(DEFIB+p, "%[^;];",  defibrilators[i].address);
        p = p + strlen(defibrilators[i].address)+1;
        sscanf(DEFIB+p, "%[^;];",  defibrilators[i].telnum);
        p = p + strlen(defibrilators[i].telnum)+1;
        sscanf(DEFIB+p, "%[^;];",  defibrilators[i].longitude);
        p = p + strlen(defibrilators[i].longitude)+1;
        comma2dot(defibrilators[i].longitude);
        radians[i][0] = strtod(defibrilators[i].longitude, NULL)*pi/180;
        sscanf(DEFIB+p, "%[^;];",  defibrilators[i].latitude);
        comma2dot(defibrilators[i].latitude);
        radians[i][1] = strtod(defibrilators[i].latitude, NULL)*pi/180;
    }
    double closest = 999999;
    int index;
    double d[N];
    for (int i=0; i<N; i++)
    {
        double x = (radians[i][0] - lon) * cos(lat/2 + radians[i][1]/2);
        double y = radians[i][1] - lat;
        d[i] = sqrt(x*x+y*y)*637;
        if (d[i] <= closest)
        {
            closest = d[i];
            index = i;
        }
    }
    printf("%s", defibrilators[index].name);

    return 0;
}