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
    init(Main);
    init(Mark);

    // Printing boards
    print(Main, Mark);

    // Ships placement
    setup(Main);

    // Printing boards
    print(Main, Mark);

    // Game starts

    // Types of message :
    //  - Coordinates
    //  - hit or not
    //  - win / lose

    return 0;
}
