#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structures.h"
#include "print.h"
#include "board.h"
#include "ship.h"

int main()
{
    // Boards declaration
    Cell Main[ROWS][COLUMNS];
    Cell Mark[ROWS][COLUMNS];

    // Boards initialization
    initBoard(Main);
    initBoard(Mark);

    // Printing boards
    printBoards(Main, Mark);

    // Ships placement
    initShips(Main);

    // Printing boards
    printBoards(Main, Mark);

    // Game starts

    // Types of message :
    //  - Coordinates
    //  - hit or not
    //  - win / lose

    return 0;
}
