#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // game loop
    while (1) {
        int mountainH[8], max=0, index;
        for (int i = 0; i < 8; i++) 
        {
            cin >> mountainH[i]; cin.ignore();
            if (max<=mountainH[i])
            {
                max = mountainH[i];
                index = i;
            }
        }
        cout << index << endl;
    }
}