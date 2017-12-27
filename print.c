#include <stdio.h>
#include "constants.h"
#include "print.h"

void printBoards(Cell Main[ROWS][COLUMNS], Cell Mark[ROWS][COLUMNS])
{
    char c;
    int i, j;

    printf("\nMain board\t\tMark board\n");
    for (i = 0; i < ROWS; i++) {
        // Printing rows
        if (i + 1 < 10)
            printf("%d ", i + 1);
        else
            printf("%d", i + 1);
        // Printing main board
        for (j = 0; j < COLUMNS; j++)
            printf("%c ", Main[i][j].type);
        printf("\t");
        // Printing mark board
        for (j = 0; j < COLUMNS; j++)
            printf("%c ", Mark[i][j].type);
        printf("\n");
    }
    // Printing columns
    printf("  ");
    for (c = 'A'; c < 'A' + COLUMNS; c++)
       printf("%c ", c);
    printf("\t");
    for (c = 'A'; c < 'A' + COLUMNS; c++)
       printf("%c ", c);
    printf("\n\n");
}

void printMain(Cell Main[ROWS][COLUMNS])
{
    char c;
    int i, j;

    printf("\nMain board\n");
    for (i = 0; i < ROWS; i++) {
        // Printing rows
        if (i + 1 < 10)
            printf("%d ", i + 1);
        else
            printf("%d", i + 1);
        // Printing main board
        for (j = 0; j < COLUMNS; j++)
            printf("%c ", Main[i][j].type);
        printf("\n");
    }
    // Printing columns
    printf("  ");
    for (c = 'A'; c < 'A' + COLUMNS; c++)
       printf("%c ", c);
    printf("\n\n");
}
