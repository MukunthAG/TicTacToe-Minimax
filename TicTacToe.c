/*
A FEW SUGGESTIONS BEFORE READING, 
--> Run this game and get an idea on how it's built, avoid warnings from the compiler if any.
--> Learn and have a good grasp on how "recursion" works
--> You may need to familiarize yourself with the "minimax algorithm", I posted some useful links in the README.
*/
#include <stdio.h>

// A few global variables whose importance will be shown later
int positionHoldingMaxScore;
int coordinatesHoldingMaxScore[2];
int maxDepth;
int noOfCalls;

void printInstructions() { // Prints instructions at the start of the game
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

int min(int a, int b) { // Returns Min value of two numbers
    return (a > b) ? b : a;
}

int max(int a, int b) { // Returns Max value of two numbers
    return (a > b) ? a : b;
}

int depthCounter(int ourArr[3][3]) { /* Takes in an array made of 1(-->X), 9(-->O) and 0(-->#) to return the "depth" of the position, or
in other words total no. of zeroes(empty positions) */
    int i, j, depthCount = -1;
    for (i = 0; i < 3; i++) { 
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0) depthCount++; 
        }
    }
    return depthCount; 
}

int optimalCoordinates(int ourArr[3][3], int optimalPosition) { /* Returns the coordinates of the computer's choice by taking in the
optimal position(in the form of n'th zero) from the "minimax" function */
    int i,j; int count = -1;
    for (i = 0; i < 3; i++) {
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


int minimax(int depth, int ourArr[3][3], int player) { /* The Brain of the game, takes in the depth of the tree to reach, the 
current position(2D array) of game and the player(in our case its always "9" or "CPU"), whose score must be maximized */

    if (noOfCalls == 0) { // This preserves the original call's depth, irrespective of the stack memory
        noOfCalls++;
        maxDepth = depth;
    }

    /* The following piece of code calculates the score of our game(2D Array), depending upon whose likely to win, score is
    --> "-1" if the game can't be evaluated(the middle game)
    --> "-2" if the user is winning
    --> "+1" if the CPU is winning
    --> "+0" if neither is winning(Tie)
    */

    int score;
    int i, j; int count = 0; 
    int countOfZeros = 0; 
    score = -1;
    for (i = 0; i < 3; i++) { 
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0)  {
                countOfZeros++; 
            }
        }
    } 
    if (countOfZeros == 0) score = 0; // If no. of zeroes is zero, then the game is Tie. 
    for (i = 0; i < 3; i++) { // Row wise checking for any winning condition
        for (j = 1; j < 3; j++) {
            if (ourArr[i][j-1] == ourArr[i][j]) count++;
        }
        if (count == 2 && ourArr[i][0] != 0) {
            if (ourArr[i][0] == 9) {
                score = 1;
            }
            else if (ourArr[i][0] == 1) score = -2;
        } 
        count = 0; 
    }

    for (i = 0; i < 3; i++) { // Coloumn wise checking
        for (j = 1; j < 3; j++) {
            if (ourArr[j-1][i] == ourArr[j][i]) count++;
        }
        if (count == 2 && ourArr[0][i] != 0) {
            if (ourArr[0][i] == 9 ) score = 1;
            else if (ourArr[0][i] == 1) score = -2;
        }  
        count = 0; 
    }
    
    i = 0; 

    // Diagonal wise checking, NEED IMPROVEMENT! It does the job for now.

    if (ourArr[i][i] == ourArr[i+1][i+1] && ourArr[i+1][i+1] == ourArr[i+2][i+2] && ourArr[i][i] != 0) {
            if (ourArr[i][i] == 9) score = 1;
            else if (ourArr[i][i] == 1) score = -2;
        }

    else if (ourArr[2][0] == ourArr[1][1] && ourArr[1][1] == ourArr[0][2] && ourArr[1][1] != 0) {
            if (ourArr[1][1] == 9) score = 1;
            else if (ourArr[1][1] == 1) score = -2;
        } 

    //END of evaluation part, by this time, the games score is decided, unless it is an end game(game over position), the score is -1.

    /* There is 3 parts in the following piece of code,
    --> Creating the possibility arrays called "children".
    --> Iterating through each "child" and use recursion to forcefully reach the depth of the tree and pull up from there.
    --> Returning the n'th child, or n'th zero, corresponding to maximum score.
    */

    int children[10][3][3]; 
    int m; int w; int zeroCount = -1; int zeroInfo[10][3]; int p, q;

    for (m = 0; m < 3; m++) { // Storing the zeroInformation, It would be used to cook our children
        for (w = 0; w < 3; w++) {
            if (ourArr[m][w] == 0) {
                zeroCount++; 
                zeroInfo[zeroCount][0] = zeroCount; 
                zeroInfo[zeroCount][1] = m; 
                zeroInfo[zeroCount][2] = w; 
            }
        }
    }

    for (m = 0; m <= zeroCount; m++) { // Cooking the children from the parent array
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = player;
        for (p = 0; p < 3; p++) {
            for (q = 0; q < 3; q++) {
                children[m][p][q] = ourArr[p][q];
            }
        }
        ourArr[zeroInfo[m][1]][zeroInfo[m][2]] = 0;
    }

    int k,y; // Sorry for not being conventional ;)

    int evalMax, evalMin, maxScore,minScore; // Important variables

    if (depth == 0 || score != -1) { // As you can understand if you followed my suggestions, this is the base value for our recursion
        return score;
    }

    if (player == 9) {
        maxScore = -10; //maxScore Initializer, conventionaly taken to -Infinity, here -10 is sufficient 
        for (k = 0; k <= zeroCount; k++) {
            evalMax = minimax(depth - 1, children[k], 1); // Testing all of its children
            if (evalMax > maxScore && depth == maxDepth) {          
                positionHoldingMaxScore = k; 
                /* 
                This is the reason why we had the first if statement, this makesures that the 
                "positionHoldingMaxScore" (in global scope) gets updated only when the depth is equal to the maximum depth of
                the tree.
                */
            }
            maxScore = max(maxScore, evalMax);
        }
        return maxScore;
    }

    if (player == 1) {
        minScore = 10;
        for (y = 0; y <= zeroCount; y++) {
            evalMin = minimax(depth - 1, children[y], 9);
            minScore = min(minScore, evalMin);
        }
        return minScore;
    }
 
}

int printGame(int ourArr[3][3]) {  // Prints the game, but now with naughts and crosses ;)
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
    
int scoreEval(int ourArr[3][3]) { /* Basically the same kind of thing which happened at the start of minimax, now returns a value. I faced
some issues of using the return value of this function inside the minimax */

    int i, j; int count = 0; 
    int zeroCount = 0;

    for (i = 0; i < 3; i++) { 
        for (j = 1; j < 3; j++) {
            if (ourArr[i][j-1] == ourArr[i][j]) count++;
        }
        if (count == 2 && ourArr[i][0] != 0) return 1; 
        count = 0; 
    }

    for (i = 0; i < 3; i++) { 
        for (j = 1; j < 3; j++) {
            if (ourArr[j-1][i] == ourArr[j][i]) count++;
        }
        if (count == 2 && ourArr[0][i] != 0) return 1;  
        count = 0; 
    }

    for (i = 0; i < 3; i++) { 
        for (j = 0; j < 3; j++) {
            if (ourArr[i][j] == 0)  {
                zeroCount++; 
            }
        }
    } 

    i = 0;
    
    if (ourArr[i][i] == ourArr[i+1][i+1] && ourArr[i+1][i+1] == ourArr[i+2][i+2] && ourArr[i][i] != 0) return 1;

    else if (ourArr[2][0] == ourArr[1][1] && ourArr[1][1] == ourArr[0][2] && ourArr[1][1] != 0) return 1;

    else if (zeroCount == 0) return 0;

    else return -1;
}

int main() {
    printInstructions();
    int depth;
    int optimalPosition;
    int x, y; // User input coordinates 
    int i, j; 
    int temp = -1; // Decides whether the game should proceed
    int cSet[3][3];  // Our coordinate set(game array)

    for (i = 0; i < 3; i++) { // Define all the elements of our array to be 0 initially
        for (j = 0; j < 3; j++) {
            cSet[i][j] = 0;
        }
    }

    while (temp == -1) { // Game will be over when this while loop breaks
        noOfCalls = 0;

        // Scan for coordinates and set it to be 1 (user input)
        
        printf("You choose : ");
        scanf("%d %d", &x, &y);  
        if (cSet[x][y] == 0) cSet[x][y] = 1; 
        else {
            printf("Refer to the Instructions. Enter a valid Input!\n");
            printf("You choose : ");
            scanf("%d %d", &x, &y);  
        }
        printGame(cSet); // User turn
        temp = scoreEval(cSet);
        if (temp == 1) {
            printf("YOU WIN! If you see this message, then you found a bug in my code, consider contributing! ;)\n");
            break;
        }
        else if (temp == 0) {
            printf("DRAW!\n");
            break;
        }

        // Preparing to launch minimax,

        depth = depthCounter(cSet);
        int maximScore; // Used for debugging, of no use now.
        i = 0; 
        while (i == 0) {
            maximScore = minimax(depth + 1, cSet, 9); // Updates "positionHoldingMaxScore"
            optimalCoordinates(cSet, positionHoldingMaxScore); // Updates coordinates from "positionHolding MaxScore"
            int cX = coordinatesHoldingMaxScore[0];
            int cY = coordinatesHoldingMaxScore[1];
            if (cSet[cX][cY] != 1 && cSet[cX][cY] != 9) { // This is a protection by any means if you change the code, nothing disastrous happens.
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
