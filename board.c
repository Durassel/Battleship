#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "board.h"

void init(Cell board[ROWS][COLUMNS])
{
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            board[i][j].type = '-';
            board[i][j].prev = NULL;
            board[i][j].next = NULL;
        }
    }
}
