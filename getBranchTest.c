#include <stdio.h>

int *getChildren(int arr[3][3]) { 

    int i; int j; static int children[10][3][3]; int zeroCount = -1; int zeroInfo[10][3]; int p, q, r, t,s;   
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (arr[i][j] == 0) {
                zeroCount++; 
                zeroInfo[zeroCount][0] = zeroCount; 
                zeroInfo[zeroCount][1] = i; 
                zeroInfo[zeroCount][2] = j; 
                
            }
        }
    }
    for (i = 0; i <= zeroCount; i++) {
        arr[zeroInfo[i][1]][zeroInfo[i][2]] = 9;
        for (p = 0; p < 3; p++) {
            for (q = 0; q < 3; q++) {
                children[i][p][q] = arr[p][q];
            }
        }
        arr[zeroInfo[i][1]][zeroInfo[i][2]] = 0;
    }
    //printf("first el: %d\n", children[2][1][0]);
    /*for(p=0;p<=zeroCount;p++)
	{
		for(q=0;q<3;q++)
		{
			for(r=0;r<3;r++)
			{
				printf("%d ", children[p][q][r]);
				if(r==2)
				{
					printf("\n");
				}
			}
		}
		printf("\n");
	}*/
    return children;
}

int main() 
{          
    int arr[3][3] = 
        {
         {0, 0, 0},
         {0, 0, 0}, 
         {0, 0, 0}
        };
    int *childPointer;
    childPointer = getChildren(arr);
    while (*childPointer != 0) {
        printf("%d", *childPointer);
        childPointer++;
    }
    return 0;
}