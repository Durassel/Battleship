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

int input(char *str, int size)
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

int multipleCoordinates(char coordinates[4])
{
    int i;
    for (i = 0; i < 10; i++) {
        if ((int) (coordinates[2] - '0') == i)
            return 1;
    }
    return 0;
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

int check(Cell Main[ROWS][COLUMNS], char coordinates[4])
{
    int i, row, column, result;
    char c;

    // Check column
    result = 0;
    for (c = 'A'; c < 'A' + COLUMNS; c++) {
        if (coordinates[0] == c)
            result = 1;
    }
    // Check row
    if (result == 1) {
        result = 0;
        for (i = 1; i < ROWS + 1; i++) {
            if (multipleCoordinates(coordinates)) {
                if ((int) (coordinates[1] - '0') == i / 10 && (int) (coordinates[2] - '0') == i % 10)
                    result = 1;
            } else {
                if ((int) (coordinates[1] - '0') == i)
                    result = 1;
            }
        }
    }
    // Check if cell empty
    if (result == 1) {
        result = 0;
        if (multipleCoordinates(coordinates)) {
            row = ((int) (coordinates[1] - '0') * 10) + (int) (coordinates[2] - '0') - 1;
            column = convertColumnToInt(coordinates[0]);
        } else {
            row = (int) (coordinates[1] - '0') - 1;
            column = convertColumnToInt(coordinates[0]);
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

void selectCoordinates(Cell Main[ROWS][COLUMNS], char coordinates[4])
{
    int result;
    do { // Start coordinates
        printf("\tEnter coordinates (Ex: A1) : ");
        input(coordinates, 4);
        result = check(Main, coordinates); // Check validity
    } while(result == 0);
}

int selectDirection(Cell Main[ROWS][COLUMNS], char coordinates[4], char direction[2], int size)
{
    int i, result;
    int row, column;
    do { // Start coordinates
        result = 0;
        printf("\tVertical or horizontal (v/h) : ");
        input(direction, 2);
        if (direction[0] == 'v' || direction[0] == 'h')
            result = 1;
    } while(result == 0);

    // Check if the ship don't overflow of array
    if (direction[0] == 'v') {
        if (multipleCoordinates(coordinates)) {
            row = ((int) (coordinates[1] - '0') * 10) + (int) (coordinates[2] - '0');
            if (row + size - 1 > ROWS) {
                printf("\t\tError: the ship overflow the array.\n");
                return 0;
            } else {
                result = 1;
            }
        } else {
            if ((int) (coordinates[1] - '0') + size - 1 > ROWS) {
                printf("\t\tError: the ship overflow the array.\n");
                return 0;
            } else {
                result = 1;
            }
        }
    } else if (direction[0] == 'h') {
        if (coordinates[0] + size - 1 > 'A' + COLUMNS - 1) {
            printf("\t\tError: the ship overflow the array.\n");
            return 0;
        } else {
            result = 1;
        }
    }
    // Check if the ship don't overcome another ship
    if (direction[0] == 'v') {
        if (multipleCoordinates(coordinates)) {
            row = ((int) (coordinates[1] - '0') * 10) + (int) (coordinates[2] - '0') - 1;
        } else {
            row = (int) (coordinates[1] - '0') - 1;
        }
        column = convertColumnToInt(coordinates[0]);
        for (i = row; i < row + size; i++) {
            if (Main[i][column].type != '-') {
                printf("\t\tError: a ship already exists at this position.\n");
                return 0;
            }
        }
        result = 1;
    } else if (direction[0] == 'h') {
        if (multipleCoordinates(coordinates)) {
            row = ((int) (coordinates[1] - '0') * 10) + (int) (coordinates[2] - '0') - 1;
        } else {
            row = (int) (coordinates[1] - '0') - 1;
        }
        column = convertColumnToInt(coordinates[0]);
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

void create(Cell Main[ROWS][COLUMNS], char coordinates[4], char direction[2], int size, char type)
{
    int i, row, column;
    for (i = 0; i < size; i++) {
        if (direction[0] == 'v') {
            column = convertColumnToInt(coordinates[0]);
            if (multipleCoordinates(coordinates))
                row = ((int) (coordinates[1] - '0') * 10) + (int) (coordinates[2] - '0') + i;
            else
                row = (int) (coordinates[1] - '0') + i;
            Main[row - 1][column].type = type;
            if (i + 1 < size)
                Main[row - 1][column].next = &Main[row][column];
            if (i > 0)
                Main[row - 1][column].prev = &Main[row - 2][column];
        } else if (direction[0] == 'h') {
            column = convertColumnToInt(coordinates[0]) + i;
            if (multipleCoordinates(coordinates))
                row = ((int) (coordinates[1] - '0') * 10) + (int) (coordinates[2] - '0') - 1;
            else
                row = (int) (coordinates[1] - '0') - 1;
            Main[row][column].type = type;
            if (i + 1 < size)
                Main[row][column].next = &Main[row][column + 1];
            if (i > 0)
                Main[row][column].prev = &Main[row][column - 1];
        }
    }
}

void setup(Cell Main[ROWS][COLUMNS])
{
    int i, result;
    char coordinates[4] = {(int) NULL}; // Don't forget the \0 at the end of an array
    char direction[2];

    // Ships initialization
    printf("---------------------- Ships initialization ----------------------\n");
    // Carrier initialization
    printf("%d carrier of size %d :\n", CARRIER_NB, CARRIER_SIZE);
    for (i = 0; i < CARRIER_NB; i++) {
        do { // Enter coordinates, check validity
            selectCoordinates(Main, coordinates);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, coordinates, direction, CARRIER_SIZE);
        } while (result == 0);
        // Create new ship
        create(Main, coordinates, direction, CARRIER_SIZE, 'C');
        refresh(Main);
    }
    // Battleship initialization
    printf("%d battleship of size %d :\n", BATTLESHIP_NB, BATTLESHIP_SIZE);
    for (i = 0; i < BATTLESHIP_NB; i++) {
        do { // Enter coordinates, check validity
            selectCoordinates(Main, coordinates);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, coordinates, direction, BATTLESHIP_SIZE);
        } while (result == 0);
        // Create new ship
        create(Main, coordinates, direction, BATTLESHIP_SIZE, 'B');
        refresh(Main);
    }
    // Sumarine initialization
    printf("%d submarine of size %d :\n", SUBMARINE_NB, SUBMARINE_SIZE);
    for (i = 0; i < SUBMARINE_NB; i++) {
        do { // Enter coordinates, check validity
            selectCoordinates(Main, coordinates);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, coordinates, direction, SUBMARINE_SIZE);
        } while (result == 0);
        // Create new ship
        create(Main, coordinates, direction, SUBMARINE_SIZE, 'S');
        refresh(Main);
    }
    // Destroyer initialization
    printf("%d destroyer of size %d :\n", DESTROYER_NB, DESTROYER_SIZE);
    for (i = 0; i < DESTROYER_NB; i++) {
        do { // Enter coordinates, check validity
            selectCoordinates(Main, coordinates);
            // Ask direction : vertical or horizontal
            result = selectDirection(Main, coordinates, direction, DESTROYER_SIZE);
        } while (result == 0);
        // Create new ship
        create(Main, coordinates, direction, DESTROYER_SIZE, 'D');
        refresh(Main);
    }
}

