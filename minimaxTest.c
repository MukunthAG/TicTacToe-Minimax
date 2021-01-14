#include <stdio.h>
int positionHoldingMaxScore;
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
int scoreEval(int ourArr[3][3]) {

    int i, j; int count; 
    int zeroCount = 0; // To DRAW when zeroes run out
    for (i = 0; i < 3; i++) { // Row wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[i][j-1] == ourArr[i][j]) count++;
        }
        if (count == 2 && ourArr[i][0] != 0) {
            if (ourArr[i][0] == 9) return 1;
            else if (ourArr[i][0] == 1) return -2;
        } 
        count = 0; // Reset count after each scan for a row
    }
    for (i = 0; i < 3; i++) { // Coloumn wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[j-1][i] == ourArr[j][i]) count++;
        }
        if (count == 2 && ourArr[0][i] != 0) {
            if (ourArr[0][i] == 9 ) return 1;
            else if (ourArr[0][i] == 1) return -2;
        }  
        count = 0; // Reset count 
    }
    for (i = 0; i < 3; i++) { // Check for Draw
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0)  {
                zeroCount++; 
            }
        }
    } 

    i = 0;
    // Diagonal wise checking, NEED IMPROVEMENT!!, to be applicable for n x n matrix
    if (ourArr[i][i] == ourArr[i+1][i+1] && ourArr[i+1][i+1] == ourArr[i+2][i+2] && ourArr[i][i] != 0) {
            if (ourArr[i][i] == 9 ) return 1;
            else if (ourArr[i][i] == 1) return -2;
        }

    else if (ourArr[2][0] == ourArr[1][1] && ourArr[1][1] == ourArr[0][2] && ourArr[1][1] != 0) {
            if (ourArr[1][1] == 9 ) return 1;
            else if (ourArr[1][1] == 1) return -2;
        }

    // Return Draw condition
    else if (zeroCount == 0) return 0;

    else return -1;
}
int minimax(int depth, int ourArr[3][3], int maximizer) {
    int children[10][3][3]; 
    //printf("%d", depth);
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
        // if (m == zeroCount) {
        //     //do not use [10][0][0]
        //     children[10][1][1] = zeroCount + 1;
        // }
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = 0;
    }
    int i,j;
    int eval,maxScore,minScore;
    int g, h;
    int score; 
    score = scoreEval(ourArr);
    //printf("%d", score);
    if (depth == 0 || score != -1) {
        // if (depth == 0) {
        //     printf("score: %d\t", score);
        //     if (score == 0 || score == -2) {
                // for (g = 0; g < 3; g++) {
                //     for (h = 0; h < 3; h++) {
                //         printf("%d ", ourArr[g][h]);
                //     }
                //     printf("\n\t\t");
                // }
                // printf("\n");   
        //     }
        // }
        return score;
    } 
    if (maximizer == 9) {
        maxScore = -10;
        for (i = 0; i <= zeroCount; i++) {
            eval = minimax(depth - 1, children[i], 1);
            maxScore = max(maxScore, eval);
            //printf("depth : %d, maxScore : %d\n", depth, maxScore);
        }
        //printf("maxScore : %d, depth : %d\n\n", maxScore, depth);
        return maxScore;
    }
    if (maximizer == 1) {
        minScore = 10;
        for (j = 0; j <= zeroCount; j++) {
            eval = minimax(depth - 1, children[j], 9);
            minScore = min(minScore, eval);
            if (depth == 5) {printf("j : %d, eval : %d\n", j, eval);
            for (g = 0; g < 3; g++) {
                    for (h = 0; h < 3; h++) {
                        printf("%d ", children[j][g][h]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        if (depth == 5) {
            positionHoldingMaxScore = j;
            printf("%d %d\t", j, minScore);
            for (g = 0; g < 3; g++) {
                    for (h = 0; h < 3; h++) {
                        printf("%d ", ourArr[g][h]);
                    }
                    printf("\n\t");
                }
                printf("\n");  
        }
        return minScore;
    }
}

int main () {
    int cSet[3][3] = { 
      {9, 0, 1},
      {0, 1, 0}, 
      {0, 0, 0} 
    };
    int pos;
    /*pos = */minimax(6, cSet, 9);
    ///printf("%d", pos);
}

//build ur tree!!!