#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "ship.h"
#include "print.h"

void flush()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int read(char *str, int size)
{
    char *pos = NULL;

    if (fgets(str, size, stdin) != NULL) {
        pos = strchr(str, '\n');
        if (pos != NULL)
            *pos = '\0';
        else
            flush();
        return 1;
    } else {
        flush();
        return 0;
    }
}

int tens(char coordinates[4])
{
    int i;
    for (i = 0; i < 10; i++) {
        if ((int) (coordinates[2] - '0') == i)
            return 1;
    }
    return 0;
}

int testCoordinates(char start[4], Cell Main[ROWS][COLUMNS])
{
    int i, row, column, result = 0;
    char c;

    // Check column
    for (c = 'A'; c < 'A' + COLUMNS; c++) {
        if (start[0] == c)
            result = 1;
    }
    // Check row
    if (result == 1) {
        result = 0;
        for (i = 1; i < ROWS + 1; i++) {
            if (tens(start)) {
                if ((int) (start[1] - '0') == i / 10 && (int) (start[2] - '0') == i % 10)
                    result = 1;
            } else {
                if ((int) (start[1] - '0') == i)
                    result = 1;
            }
        }
    }
    // Check if cell empty
    if (result == 1) {
        result = 0;
        if (tens(start)) {
            row = ((int) (start[1] - '0') * 10) + (int) (start[2] - '0') - 1;
            column = convertColumnToInt(start[0]);
        } else {
            row = (int) (start[1] - '0') - 1;
            column = convertColumnToInt(start[0]);
        }
        if (Main[row][column].type != '-') {
            printf("\t\tError: a ship already exists at this position.\n");
            result = 0;
        } else {
            result = 1;
        }
    }

    return result;
}

void coordinates(char *start, Cell Main[ROWS][COLUMNS])
{
    int result;
    do { // Start coordinates
        printf("\tEnter start coordinates (Ex: A1) : ");
        read(start, 4);
        result = testCoordinates(start, Main); // Check validity
    } while(result == 0);
}

int selectDirection(Cell Main[ROWS][COLUMNS], char *direction, char *start, int size)
{
    int i, result;
    int row, column;
    do { // Start coordinates
        result = 0;
        printf("\tVertical or horizontal (v/h) : ");
        read(direction, 2);
        if (direction[0] == 'v' || direction[0] == 'h')
            result = 1;
    } while(result == 0);

    // Check if the ship don't overflow of array
    if (direction[0] == 'v') {
        if (tens(start)) {
            row = ((int) (start[1] - '0') * 10) + (int) (start[2] - '0');
            if (row + size - 1 > ROWS) {
                printf("\t\tError: the ship overflow the array.\n");
                return 0;
            } else {
                result = 1;
            }
        } else {
            if ((int) (start[1] - '0') + size - 1 > ROWS) {
                printf("\t\tError: the ship overflow the array.\n");
                return 0;
            } else {
                result = 1;
            }
        }
    } else if (direction[0] == 'h') {
        if (start[0] + size - 1 > 'A' + COLUMNS - 1) {
            printf("\t\tError: the ship overflow the array.\n");
            return 0;
        } else {
            result = 1;
        }
    }
    // Check if the ship don't overcome another ship
    if (direction[0] == 'v') {
        if (tens(start)) {
            row = ((int) (start[1] - '0') * 10) + (int) (start[2] - '0') - 1;
        } else {
            row = (int) (start[1] - '0') - 1;
        }
        column = convertColumnToInt(start[0]);
        for (i = row; i < row + size; i++) {
            if (Main[i][column].type != '-') {
                printf("\t\tError: a ship already exists at this position.\n");
                return 0;
            }
        }
        result = 1;
    } else if (direction[0] == 'h') {
        if (tens(start)) {
            row = ((int) (start[1] - '0') * 10) + (int) (start[2] - '0') - 1;
        } else {
            row = (int) (start[1] - '0') - 1;
        }
        column = convertColumnToInt(start[0]);
        for (i = column; i < column + size; i++) {
            if (Main[row][i].type != '-') {
                printf("\t\tError: a ship already exists at this position.\n");
                return 0;
            }
        }
        result = 1;
    }

    return result;
}

int convertColumnToInt(char column)
{
    int i = 0;
    char c;
    for (c = 'A'; c < 'A' + COLUMNS; c++) {
        if (column == c)
            break;
        i++;
    }
    return i;
}

void createShip(int size, char type, char start[4], char direction[2], Cell Main[ROWS][COLUMNS])
{
    int i, row, column;
    for (i = 0; i < size; i++) {
        if (direction[0] == 'v') {
            column = convertColumnToInt(start[0]);
            if (tens(start))
                row = ((int) (start[1] - '0') * 10) + (int) (start[2] - '0') + i;
            else
                row = (int) (start[1] - '0') + i;
            Main[row - 1][column].type = type;
            if (i + 1 < size)
                Main[row - 1][column].next = &Main[row][column];
            if (i > 0)
                Main[row - 1][column].prev = &Main[row - 2][column];
        } else if (direction[0] == 'h') {
            column = convertColumnToInt(start[0]) + i;
            if (tens(start))
                row = ((int) (start[1] - '0') * 10) + (int) (start[2] - '0') - 1;
            else
                row = (int) (start[1] - '0') - 1;
            Main[row][column].type = type;
            if (i + 1 < size)
                Main[row][column].next = &Main[row][column + 1];
            if (i > 0)
                Main[row][column].prev = &Main[row][column - 1];
        }
    }
}

void initShips(Cell Main[ROWS][COLUMNS])
{
    int i, result;
    char start[4] = {(int) NULL}; // Don't forget the \0 at the end of an array
    char direction[2];

    // Ships initialization
    printf("---------------------- Ships initialization ----------------------\n");
    // Carrier initialization
    printf("%d carrier of size %d :\n", CARRIER_NB, CARRIER_SIZE);
    for (i = 0; i < CARRIER_NB; i++) {
        do { // Enter start coordinates, check validity
            coordinates(start, Main);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, direction, start, CARRIER_SIZE);
        } while (result == 0);
        // Create new ship
        createShip(CARRIER_SIZE, 'C', start, direction, Main);
        printMain(Main);
    }
    // Battleship initialization
    printf("%d battleship of size %d :\n", BATTLESHIP_NB, BATTLESHIP_SIZE);
    for (i = 0; i < BATTLESHIP_NB; i++) {
        do { // Enter start coordinates, check validity
            coordinates(start, Main);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, direction, start, BATTLESHIP_SIZE);
        } while (result == 0);
        // Create new ship
        createShip(BATTLESHIP_SIZE, 'B', start, direction, Main);
        printMain(Main);
    }
    // Sumarine initialization
    printf("%d submarine of size %d :\n", SUBMARINE_NB, SUBMARINE_SIZE);
    for (i = 0; i < SUBMARINE_NB; i++) {
        do { // Enter start coordinates, check validity
            coordinates(start, Main);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, direction, start, SUBMARINE_SIZE);
        } while (result == 0);
        // Create new ship
        createShip(SUBMARINE_SIZE, 'S', start, direction, Main);
        printMain(Main);
    }
    // Destroyer initialization
    printf("%d destroyer of size %d :\n", DESTROYER_NB, DESTROYER_SIZE);
    for (i = 0; i < DESTROYER_NB; i++) {
        do { // Enter start coordinates, check validity
            coordinates(start, Main);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, direction, start, DESTROYER_SIZE);
        } while (result == 0);
        // Create new ship
        createShip(DESTROYER_SIZE, 'D', start, direction, Main);
        printMain(Main);
    }
}

