#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rando() {
    int r; 
    srand(time(NULL));
    r = rand()%3;
    return r;
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

int gameOver(int ourArr[3][3]) {
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

        // Scan for coordinates and set it to be 1 (user input)
        printf("You choose : ");
        scanf("%d %d", &x, &y);  cSet[x][y] = 1;
        printGame(cSet); // User turn
        temp = gameOver(cSet);
        if (temp == 1) {
            printf("YOU WIN!\n");
            break;
        }
        else if (temp == 0) {
            printf("DRAW!\n");
            break;
        }

        /* Random CPU Input (will be modified later, 
        we will build a function for it)*/
        i = 0; 
        while (i == 0) {
            int cX = rando(); int cY = rando();
            //printf("%d %d", cX, cY);
            if (cSet[cX][cY] != 1 && cSet[cX][cY] != 9) { 
                printf("Computer chose: %d %d\n", cX, cY);
                cSet[cX][cY] = 9;
                i++; // Alt for break
            }
            else continue;
        }

        printGame(cSet); // CPU turn 
        temp = gameOver(cSet);
        if (temp == 1) {
            printf("COMPUTER WIN!\n");
            break;
        }    
    }
    return 0;
}