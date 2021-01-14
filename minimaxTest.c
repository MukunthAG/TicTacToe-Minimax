#include <stdio.h>
int positionHoldingMaxScore;
int noOfCalls = 0;
int maxDepth;
int min(int a, int b) {return (a > b) ? b : a;} 
int max(int a, int b) {return (a > b) ? a : b;}
int _2Dto1D(int x, int y) {
    int i, j; int count = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == x && j == y) return count; else count++;
        }
    }
    return 0;
}
int _1Dto2D(int n, int c[]) {
    int i, j; int count = -1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            count++;
            if (count == n) {
                c[0] = i;
                c[1] = j;
            }
        }
    }
    return 0;
}
int printGame(int ourArr[3][3]) {  
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%4d", ourArr[i][j]);
        }
        printf("\n");
    }
}
int minimax(int depth, int ourArr[3][3], int maximizer) {
    //-------------------------------
    if (noOfCalls == 0) {
        noOfCalls++;
        maxDepth = depth;
    }
    int changeScore;
    int i, j; int count; 
    int countOfZeros = 0; // To DRAW when zeroes run out
    changeScore = -1;
    for (i = 0; i < 3; i++) { // Check for Draw
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0)  {
                countOfZeros++; 
            }
        }
    } 
    // changeScore = Draw condition
    if (countOfZeros == 0) changeScore = 0; 
    for (i = 0; i < 3; i++) { // Row wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[i][j-1] == ourArr[i][j]) count++;
        }
        if (count == 2 && ourArr[i][0] != 0) {
            if (ourArr[i][0] == 9) {
                changeScore = 1;
            }
            else if (ourArr[i][0] == 1) changeScore = -2;
        } 
        count = 0; // Reset count after each scan for a row
    }
    for (i = 0; i < 3; i++) { // Coloumn wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[j-1][i] == ourArr[j][i]) count++;
        }
        if (count == 2 && ourArr[0][i] != 0) {
            if (ourArr[0][i] == 9 ) changeScore = 1;
            else if (ourArr[0][i] == 1) changeScore = -2;
        }  
        count = 0; // Reset count 
    }
    
    i = 0;
    // Diagonal wise checking, NEED IMPROVEMENT!!, to be applicable for n x n matrix
    if (ourArr[i][i] == ourArr[i+1][i+1] && ourArr[i+1][i+1] == ourArr[i+2][i+2] && ourArr[i][i] != 0) {
            if (ourArr[i][i] == 9) changeScore = 1;
            else if (ourArr[i][i] == 1) changeScore = -2;
        }

    else if (ourArr[2][0] == ourArr[1][1] && ourArr[1][1] == ourArr[0][2] && ourArr[1][1] != 0) {
            if (ourArr[1][1] == 9) changeScore = 1;
            else if (ourArr[1][1] == 1) changeScore = -2;
        } 

    //---------------------------
    //if (/*depth == 0 || */changeScore == 1) {printGame(ourArr); printf("\n");}

    int children[10][3][3]; 
    int m; int w; int zeroCount = -1; int zeroInfo[10][3]; int p, q;   
    for (m = 0; m < 3; m++) {
        for (w = 0; w < 3; w++) {
            if (ourArr[m][w] == 0) {
                zeroCount++; 
                zeroInfo[zeroCount][0] = zeroCount; 
                zeroInfo[zeroCount][1] = m; 
                zeroInfo[zeroCount][2] = w; 
            }
        }
    }
    for (m = 0; m <= zeroCount; m++) {
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = maximizer;
        for (p = 0; p < 3; p++) {
            for (q = 0; q < 3; q++) {
                children[m][p][q] = ourArr[p][q];
            }
        }
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = 0;
    }
    int k,y;
    int evalMax, evalMin, maxScore,minScore; 
    if (depth == 0 || changeScore != -1) {
        return changeScore;
    } 
    if (maximizer == 9) {
        maxScore = -10;
        for (k = 0; k <= zeroCount; k++) {
            evalMax = minimax(depth - 1, children[k], 1);
            if (evalMax > maxScore && depth == maxDepth) {
                positionHoldingMaxScore = k;
            }
            maxScore = max(maxScore, evalMax);
        }
        return maxScore;
    }
    if (maximizer == 1) {
        minScore = 10;
        for (y = 0; y <= zeroCount; y++) {
            evalMin = minimax(depth - 1, children[y], 9);
            minScore = min(minScore, evalMin);
            if (depth == 7) {
                 int dep = 7;
            }
        }
        return minScore;
    }
}

int main () {
    int cSet[3][3] = { 
      {9, 0, 0},
      {1, 1, 0}, 
      {0, 0, 0} // returns the second zero!! Easy debug thing u can do really fast!!! 
    };
    int pos;
    pos = minimax(8, cSet, 9);
    printf("%d %d\n", pos, positionHoldingMaxScore);
}