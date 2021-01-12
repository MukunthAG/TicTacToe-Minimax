#include <stdio.h>
int min(int a, int b) {return (a > b) ? b : a;} 
int max(int a, int b) {return (a > b) ? a : b;}
int _2Dto1D(int x, int y) {
    int i, j; int count = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == x && j == y) return count; else count++;
        }
    }
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
}
int scoreEval(int ourArr[3][3]) {

    int i, j; int count; 
    int zeroCount = 0; // To DRAW when zeroes run out
    for (i = 0; i < 3; i++) { // Row wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[i][j-1] == ourArr[i][j]) count++;
        }
        if (count == 2 && ourArr[i][0] != 0) return 1; 
        count = 0; // Reset count after each scan for a row
    }
    for (i = 0; i < 3; i++) { // Coloumn wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[j-1][i] == ourArr[j][i]) count++;
        }
        if (count == 2 && ourArr[0][i] != 0) return 1;  
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
    if (ourArr[i][i] == ourArr[i+1][i+1] && ourArr[i+1][i+1] == ourArr[i+2][i+2] && ourArr[i][i] != 0) return 1;

    else if (ourArr[2][0] == ourArr[1][1] && ourArr[1][1] == ourArr[0][2] && ourArr[1][1] != 0) return 1;

    // Return Draw condition
    else if (zeroCount == 0) return 0;

    else return -1;
}
int minimax(int depth, int ourArr[3][3], int maximizer) {
    static int children[10][3][3];
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
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = 9;
        for (p = 0; p < 3; p++) {
            for (q = 0; q < 3; q++) {
                children[m][p][q] = ourArr[p][q];
            }
        }
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = 0;
    }
    static int i,j,eval,maxScore,minScore;
    //printf("eval: %d, maxScore: %d, minScore: %d", eval, maxScore, minScore);
    static int trackPosition;
    static int score; 
    score = scoreEval(ourArr);
    //printf(", score: %d\n", score);
    if (depth == 0 || score != -1) {
        //printf("score: %d\n", score);
        return score;
    } 
    if (maximizer == 9) {
        maxScore = -10;
        for (i = 0; i <= zeroCount; i++) {
            eval = minimax(depth - 1, children[i], 1);
            maxScore = max(maxScore, eval);
        }
        return maxScore;
    }
    if (maximizer == 1) {
        minScore = 10;
        for (j = 0; j <= zeroCount; j++) {
            eval = minimax(depth - 1, children[j], 9);
            minScore = min(minScore, eval);
        }
        return minScore;
    }
}


int main () {
  int cSet[3][3] = { 
      {0, 0, 1},
      {1, 9, 1}, 
      {9, 0, 0} 
    };
  minimax (8, cSet, 9);
}

// Output to be sent to main
    //int out[2] = {1, 2};
    //c[0] = out[0];
    //c[1] = out[1];