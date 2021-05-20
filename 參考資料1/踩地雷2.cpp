//  https://stackoverflow.com/questions/65151922/mine-sweeper-algorithm-in-c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define COLS_1 8
#define ROWS_1 8
void printBoard(char arr[][ROWS_1]); // gets a minesweeper board and prints it 
void boardInit(char arr[][ROWS_1]); // initializing a board with 'X's.
void gameOn(int col, int row, char arr[][ROWS_1], char arr2[][ROWS_1]); // gets coordinates from the user, and gets 2 arrays: a hidden board
                                                                        // with the bombs in it, and a board the user can see. 
                                                                        // the function uses other functions in order to get the game going.
int welcomeUser(); // welcome message
void minePlacer(char arr[][ROWS_1], int arrLength); // gets an empty board and mines it.
int cordChecker(int col, int row); // gets column and row from user. Returns 1 if valid and 0 if not. (0<=x<=7 are valid options)
int mineCounter(int col, int row, char arr[][ROWS_1]);  // gets an array and a coordinate, and counts the nearby mines.
void youLose(char arr[][ROWS_1]); // prints the hidden board and delivers a you lose message.
void printNumMines(char arr[][ROWS_1], char arr2[][ROWS_1], int col, int row); // printing the number of mines surrounding a cell.

int main()
{
    int userChoice, row, col;
    userChoice = welcomeUser();
    srand(time(NULL));
    srand(time(NULL));
    while (userChoice != 1)
    {
        if (userChoice == 0)
            break;
        userChoice = welcomeUser();
    }
    if (userChoice == 1)
    {
        char arr[COLS_1][ROWS_1];                   // Creating the hidden board (the one with bombs)
        char arr2[COLS_1][ROWS_1];                  // Creating the board the user will see
        boardInit(arr);                             // initializing both boards with 'X'
        boardInit(arr2);
        minePlacer(arr, ROWS_1);                    // mining the hidden board
        printBoard(arr2);
        printf("Please enter your move, column and row:\n"); 
        scanf("%d%d", &col, &row);
        gameOn(col, row, arr, arr2);
    }
}

void minePlacer(char arr[][ROWS_1], int arrLength)
{
    int i;
    if (arrLength == ROWS_1)
    {
        for (i = 0; i < ROWS_1; i++)
            arr[i][rand() % (ROWS_1-1)] = '*';
    }
}
int cordChecker(int col, int row)
{
    if (col == -1) // If the user wants to win fast
    {
        return 10;
    }
        if ((col >= COLS_1 || col < 0) || (row >= ROWS_1 || row < 0))              // user chose invalid coordinates
            return 0;
        else if ((col < COLS_1 - 1 && col >= 1) && (row < ROWS_1 - 1 && row >= 1)) // checking if the coordinates are not on boundaries.
            return 1;
        else if (col == 0 && (row != 0 && row != ROWS_1 - 1))                      // user chose (0,x) 0<x<7 
            return 2;
        else if ((col != 0 && col != COLS_1 - 1) && row == 0)                      // user chose (x,0) 0<x<7 
            return 3;
        else if (col == 0 && row == 0)                                             // user chose (0,0)
            return 4;
        else if (col == COLS_1 - 1 && row == ROWS_1 - 1)                           // user chose (7,7)
            return 5;
        else if (col == COLS_1 - 1 && (row != ROWS_1 - 1 && row != 0))             // user chose (7,x) 0<x<7 
            return 6;
        else if ((col != COLS_1 - 1 && row != 0) && row == ROWS_1 - 1)             // user chose (x,7) 0<x<7 
            return 7;
        else if (col == COLS_1 - 1 && row == 0)                                    // user chose (7,0)
            return 8;
        else if (col == 0 && row == ROWS_1 - 1)                                    // user chose (0,7)
            return 9;


}

void printBoard(char arr[][ROWS_1])
{
    int i, j;
    printf("\n");
    printf("       0   1   2   3   4   5   6   7  \n");
    printf("   ___________________________________\n");
    for (i = 0; i < COLS_1; i++)
    {
        printf("   %d | ", i);
        for (j = 0; j < ROWS_1; j++)
        {
            printf("%c", arr[i][j]);
            printf(" | ");
        }
        printf("\n");

    }
    printf("   ___________________________________\n");
}
int welcomeUser()
{
    int userChoice;
    printf("Welcome to Minesweeper!\n\n");
    printf("Please choose one of the following options and enter its number:\n\n");
    printf("1 - for size 8X8\n\n");
    printf("2 - for size 12X12\n\n");
    printf("3 - for size 15X15\n\n");
    printf("4 - for custom size\n\n");
    printf("0 - Exit\n\n");
    scanf("%d", &userChoice);
    return userChoice;
}
void boardInit(char arr[][ROWS_1])
{
    int i, j;
    for (i = 0; i < COLS_1; i++)
    {
        for (j = 0; j < ROWS_1; j++)              // Creating a minesweeper board with "X"s.
        {
            arr[i][j] = 'X';
        }
    }


}
void gameOn(int col, int row, char arr[][ROWS_1], char arr2[][ROWS_1])
{
    int countSquares = 0, count = 0, temp = row;
    while (cordChecker(col, row) == 0)
    {
        printf("Invalid coordinates, please try again\n");
        scanf("%d%d", &col, &row);
    }
    while (cordChecker(col, row) != 0)
    {
        if ((arr2[col][row] != 'X')&&(col!=-1))
            printf("Invalid move, please enter another move!\n");
        if (col != -1)
        {
            if (arr[col][row] == '*')
            {
                youLose(arr);
                break;
            }
        }
        else if (countSquares >= 56)
        {
            printf("YOU WIN\n");
            break;
        }
        printNumMines(arr, arr2, col, row);
        printBoard(arr2);
        if (cordChecker(col, row) == 10)
        {
            int i, j;
            printf("\n");
            printf("       0   1   2   3   4   5   6   7  \n");
            printf("   ___________________________________\n");
            for (i = 0; i < COLS_1; i++)
            {
                printf("   %d | ", i);
                for (j = 0; j < ROWS_1; j++)
                {
                    if (count < temp)
                    {
                        if (arr[i][j] == '*')
                        {
                            printf("%c", arr2[i][j]);
                            printf(" | ");
                            
                        }
                        else
                        {
                            printNumMines(arr, arr2, i, j);
                            printf("%c", arr2[i][j]);
                            printf(" | ");
                            count++;
                        }
                    }
                    else
                    {

                            printf("%c", arr2[i][j]);
                            printf(" | ");
                            count++;
                    }
                    
                    

                }
                printf("\n");

            }
            printf("   ___________________________________\n");
            countSquares = countSquares+row;
            

        }
        
        countSquares++;
        if (countSquares > 56)
        {
            printf("YOU WIN\n");
            break;
        }
        printf("Please enter your move, column and row:\n");
        scanf("%d%d", &col, &row);
        temp = temp + row;
    }
}
void printNumMines(char arr[][ROWS_1], char arr2[][ROWS_1], int col, int row)
{
    if (mineCounter(col, row, arr) == 0)
        arr2[col][row] = ' ';
    else
        arr2[col][row] = (char)(mineCounter(col, row, arr) + '0');

}
void youLose(char arr[][ROWS_1])
{
    int i, j;
    printf("\n");
    printf("       0   1   2   3   4   5   6   7  \n");
    printf("   ___________________________________\n");
    for (i = 0; i < COLS_1; i++)
    {
        printf("   %d | ", i);
        for (j = 0; j < ROWS_1; j++)
        {   
            if ((arr[i][j] != '*') && mineCounter(i, j, arr) == 0)        // if the cell is not a mine and is not surrounded by mines, replace it with ' '
                arr[i][j] = ' ';
            else if (arr[i][j] != '*')                                    // if the cell is not a mine but surrounded by mines, count them
                arr[i][j] = (char)(mineCounter(i, j, arr) + '0');
            printf("%c", arr[i][j]);                                      // print the cell
            printf(" | ");  
        }
        printf("\n");
    }
    printf("   ___________________________________\n");
    printf("YOU LOSE\n");
}

int mineCounter(int col, int row, char arr[][ROWS_1])
{
    int mines = 0;
    switch (cordChecker(col, row))
    {
    case 1:

        // Checking the following directions: up, down, left, right
        if (arr[col - 1][row] == '*')
            mines++;
        if (arr[col + 1][row] == '*')
            mines++;
        if (arr[col][row - 1] == '*')
            mines++;
        if (arr[col][row + 1] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col - 1][row + 1] == '*')
            mines++;
        if (arr[col - 1][row - 1] == '*')
            mines++;
        if (arr[col + 1][row + 1] == '*')
            mines++;
        if (arr[col + 1][row - 1] == '*')
            mines++;

        return mines;

    case 2:

        // Checking the following directions: up, down, left, right
        if (arr[col][row - 1] == '*')
            mines++;
        if (arr[col][row + 1] == '*')
            mines++;
        if (arr[col + 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col + 1][row - 1] == '*')
            mines++;
        if (arr[col + 1][row + 1] == '*')
            mines++;
        return mines;

    case 3:

        // Checking the following directions: up, down, left, right
        if (arr[col][row + 1] == '*')
            mines++;
        if (arr[col - 1][row] == '*')
            mines++;
        if (arr[col + 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col + 1][row + 1] == '*')
            mines++;
        if (arr[col - 1][row + 1] == '*')
            mines++;
        return mines;

    case 4:

        // Checking the following directions: up, down, left, right
        if (arr[col][row + 1] == '*')
            mines++;
        if (arr[col + 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col + 1][row + 1] == '*')
            mines++;
        return mines;

    case 5:

        // Checking the following directions: up, down, left, right
        if (arr[col][row - 1] == '*')
            mines++;
        if (arr[col - 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col - 1][row - 1] == '*')
            mines++;
        return mines;

    case 6:

        // Checking the following directions: up, down, left, right
        if (arr[col][row - 1] == '*')
            mines++;
        if (arr[col][row + 1] == '*')
            mines++;
        if (arr[col - 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col - 1][row - 1] == '*')
            mines++;
        if (arr[col - 1][row + 1] == '*')
            mines++;

        return mines;

    case 7:

        // Checking the following directions: up, down, left, right
        if (arr[col][row - 1] == '*')
            mines++;
        if (arr[col - 1][row] == '*')
            mines++;
        if (arr[col + 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col + 1][row - 1] == '*')
            mines++;
        if (arr[col - 1][row - 1] == '*')
            mines++;
        return mines;

    case 8:

        // Checking the following directions: up, down, left, right
        if (arr[col][row + 1] == '*')
            mines++;
        if (arr[col - 1][row] == '*')
            mines++;

        // Checking diagonal directions

        if (arr[col - 1][row + 1] == '*')
            mines++;
        return mines;

    case 9:

        // Checking the following directions: up, down, left, right
        if (arr[col][row - 1] == '*')
            mines++;
        if (arr[col + 1][row] == '*')
            mines++;

        // Checking diagonal directions
        if (arr[col + 1][row - 1] == '*')
            mines++;
        return mines;

    }
}
