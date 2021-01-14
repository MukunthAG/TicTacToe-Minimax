#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int positionHoldingMaxScore;
int coordinatesHoldingMaxScore[2];
int maxDepth;
int noOfCalls;

void printInstructions() {
    char yORn;
    printf("Hi welcome to this repo, this is a tic-tac-toe AI(uses minimax algorithm) written in C!\n\nPRESS ENTER TO CONTINUE\n");
    scanf("%c", &yORn);
    if (yORn) {
    printf("Below is the chart displaying positons of the valid inputs,\n\n");
    printf(" (0 0) (0 1) (0 2) \n (1 0) (1 1) (1 2) \n (2 0) (2 1) (2 2)\n");
    yORn = '\n';
    }
    printf("\nPRESS ENTER TO CONTINUE\n"); scanf("%c", &yORn);
    if (yORn)  
    printf("For Instance, if you need to put X in the center, the input must be '1 1'\n");
    printf("\nPRESS ENTER TO CONTINUE\n"); scanf("%c", &yORn);
    if (yORn) printf("GOOD LUCK!, you get the privilege to start first against AI ;)\n\n");
}
int min(int a, int b) {return (a > b) ? b : a;}
int max(int a, int b) {return (a > b) ? a : b;}

int depthCounter(int ourArr[3][3]) {
    int i,j; int depthCount = -1;
    for (i = 0; i < 3; i++) { // Check for Draw
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0)  depthCount++; 
        }
    }
    return depthCount; 
}

int optimalCoordinates(int ourArr[3][3], int optimalPosition) {
    int i,j; int count = -1;
    for (i = 0; i < 3; i++) { // Check for Draw
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0)  { 
                count++; 
                if (optimalPosition == count) {
                coordinatesHoldingMaxScore[0] = i;
                coordinatesHoldingMaxScore[1] = j;
                }
            }
        }
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
        }
        return minScore;
    }
}

int printGame(int ourArr[3][3]) {  
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0) printf("  #  ");
            if (ourArr[i][j] == 1) printf("  X  ");
            if (ourArr[i][j] == 9) printf("  O  ");
        }
        printf("\n");
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

int main() {
    printInstructions();
    int depth;
    int optimalPosition;
    int x, y; // User input coordinates 
    int i, j; // Increment variables to be used elsewhere
    int temp = -1; // Decides whether the game should proceed
    int cSet[3][3];  // Our coordinate set
    // Define all the elements of our array to be 0 initially
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cSet[i][j] = 0;
        }
    }

    // Game will be over when this while loop breaks

    while (temp == -1) {
        noOfCalls = 0;

        // Scan for coordinates and set it to be 1 (user input)
        
        printf("You choose : ");
        scanf("%d %d", &x, &y);  
        if (cSet[x][y] == 0) cSet[x][y] = 1; else {
            printf("Refer to the Instructions. Enter a valid Input!\n");
            printf("You choose : ");
            scanf("%d %d", &x, &y);  
        }
        printGame(cSet); // User turn
        temp = scoreEval(cSet);
        if (temp == 1) {
            printf("YOU WIN! If you see this message, then you found a bug in my algorithm ;)\n");
            break;
        }
        else if (temp == 0) {
            printf("DRAW!\n");
            break;
        }
        depth = depthCounter(cSet);
        int pos;
        i = 0; 
        while (i == 0) {
            pos = minimax(depth + 1, cSet, 9);
            optimalCoordinates(cSet, positionHoldingMaxScore);
            int cX = coordinatesHoldingMaxScore[0];
            int cY = coordinatesHoldingMaxScore[1];
            if (cSet[cX][cY] != 1 && cSet[cX][cY] != 9) { 
                printf("Computer chose: %d %d\n", cX, cY);
                cSet[cX][cY] = 9;
                i++; 
            }
            else continue;
        }

        printGame(cSet); // CPU turn 
        temp = scoreEval(cSet);
        if (temp == 1) {
            printf("COMPUTER WIN!\n");
            break;
        }    
    }
    return 0;
}