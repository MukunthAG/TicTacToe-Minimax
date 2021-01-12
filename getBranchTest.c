#include <stdio.h>

int getChildren(int arr[3][3]) {
    int i; int j; int children[10][3][3]; int zeroCount = -1; int zeroInfo[10][3]; int p, q, r, t,s;   
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (arr[i][j] == 0) {
                zeroCount++; // 3
                zeroInfo[zeroCount][0] = zeroCount; // 3
                zeroInfo[zeroCount][1] = i; // 2 
                zeroInfo[zeroCount][2] = j; // 0
                for (p = 0; p < 3; p++) printf("%d\n", zeroInfo[zeroCount][p]);
            }
        }
    }
    //printf("\n%d\n", zeroInfo[2][2]);
    for (i = 0; i <= zeroCount; i++) {
        arr[zeroInfo[i][1]][zeroInfo[i][2]] = 9;
        for (p = 0; p < 3; p++) {
            for (q = 0; q < 3; q++) {
                children[i][p][q] = arr[p][q];
            }
        }
        arr[zeroInfo[i][1]][zeroInfo[i][2]] = 0;
        for (t = 0; t < 3; t++) {
            for (s = 0; s < 3; s++) {
                printf("%d ", arr[t][s]);
            }
            printf("\n");
        }
    }
    printf("first el: %d\n", children[2][1][0]);
    for(p=0;p<=zeroCount;p++)
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
	}
}

int main() 
{          
    int arr[3][3] = 
        {
         {0, 0, 0},
         {0, 0, 0}, 
         {0, 0, 0}
        };
    
    getChildren(arr);

    return 0;
}