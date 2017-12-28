#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structures.h"
#include "print.h"
#include "board.h"
#include "ship.h"

int main()
{
    // Connect client to another client
        // Server process ...

    // Boards declaration
    // Player 1
    Cell Main1[ROWS][COLUMNS];
    Cell Mark1[ROWS][COLUMNS];
    // Player 2
    Cell Main2[ROWS][COLUMNS];
    Cell Mark2[ROWS][COLUMNS];

    // Fleet
    int fleet;
    int fleet1 = CARRIER_NB + BATTLESHIP_NB + SUBMARINE_NB + DESTROYER_NB;
    int fleet2 = CARRIER_NB + BATTLESHIP_NB + SUBMARINE_NB + DESTROYER_NB;
    // Result
    int result;
    // Count turn
    int turn = 0;
    // Each turn, Main/Mark change
    Cell (*playerMain)[ROWS][COLUMNS] = NULL;
    Cell (*playerMark)[ROWS][COLUMNS] = NULL;
    Cell (*enemyMain)[ROWS][COLUMNS] = NULL;
    // Coordinates
    int coordinates[2] = {0};

    // Boards initialization
    init(Main1);
    init(Mark1);

    init(Main2);
    init(Mark2);

    // Ships placement
    // Player 1
    printf("---------------------------- Player 1 : Initialization ----------------------------\n");
    refresh(Main1);
    setup(Main1);
    // Player 1
    printf("---------------------------- Player 2 : Initialization ----------------------------\n");
    refresh(Main2);
    setup(Main2);

    // Continue until one of the two players loses
    do {
        // Each in turn
        if (turn % 2 == 0) {
            printf("---------------------------- Turn of player 1 ----------------------------\n");
            fleet = fleet1;
            playerMain = &Main1;
            playerMark = &Mark1;
            enemyMain = &Main2;
        } else {
            printf("---------------------------- Turn of player 2 ----------------------------\n");
            fleet = fleet2;
            playerMain = &Main2;
            playerMark = &Mark2;
            enemyMain = &Main1;
        }
        // Printing boards
        print(*playerMain, *playerMark);

        // Select coordinates
        selectCoordinates(*playerMark, coordinates, "Error: You have already shot at this place.");
        // Check if ship is hit
        if ((*enemyMain)[coordinates[0]][coordinates[1]].type != '-') {
            (*playerMark)[coordinates[0]][coordinates[1]].type = 'x';
            (*enemyMain)[coordinates[0]][coordinates[1]].type = lower((*enemyMain)[coordinates[0]][coordinates[1]].type);
            // Check if ship is sunken
            result = check(*enemyMain, coordinates);
            if (result == 1)
                fleet--;
        } else {
            (*playerMark)[coordinates[0]][coordinates[1]].type = 'X';
        }
        // Printing boards
        print(*playerMain, *playerMark);
        if (turn % 2 == 0)
            fleet1 = fleet;
        else
            fleet2 = fleet;
        turn++;
    } while (fleet > 0);
    turn--;
    if (turn % 2 == 0)
        printf("Winner is player 1\n");
    else
        printf("Winner is player 2\n");

    return 0;
}
