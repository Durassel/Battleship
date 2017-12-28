#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "ship.h"
#include "print.h"

void flush(void)
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

int multipleCoordinates(char inputs[4])
{
    int i;
    for (i = 0; i < 10; i++) {
        if ((int) (inputs[2] - '0') == i)
            return 1;
    }
    return 0;
}

void convertInputsToCoordinates(char inputs[4], int coordinates[2])
{
    char c;
    coordinates[1] = 0;
    for (c = 'A'; c < 'A' + COLUMNS; c++) {
        if (inputs[0] == c)
            break;
        coordinates[1]++;
    }

    if (multipleCoordinates(inputs)) {
        coordinates[0] = ((int) (inputs[1] - '0') * 10) + (int) (inputs[2] - '0');
    } else {
        coordinates[0] = (int) (inputs[1] - '0');
    }
    coordinates[0]--;
}

int check(Cell Main[ROWS][COLUMNS], int coordinates[2])
{
    int result;

    // Check column
    result = 0;
    if (coordinates[1] >= 0 && coordinates[1] < COLUMNS)
        result = 1;
    else
        printf("\t\tError: coordinates are false.\n");
    // Check row
    if (result == 1) {
        result = 0;
        if (coordinates[0] >= 0 && coordinates[0] < ROWS)
            result = 1;
        else
            printf("\t\tError: coordinates are false.\n");
    }
    // Check if cell empty
    if (result == 1) {
        result = 0;
        if (Main[coordinates[0]][coordinates[1]].type != '-') {
            printf("\t\tError: a ship already exists at this position.\n");
            result = 0;
        } else {
            result = 1;
        }
    }

    return result;
}

void selectCoordinates(Cell Main[ROWS][COLUMNS], int coordinates[2])
{
    int result;
    char inputs[4] = {(int) NULL};
    do { // Start coordinates
        printf("\tEnter coordinates (Ex: A1) : ");
        input(inputs, 4);
        convertInputsToCoordinates(inputs, coordinates); // Convert B3 into 2-1 (row - column)
        result = check(Main, coordinates); // Check validity
    } while(result == 0);
}

int selectDirection(Cell Main[ROWS][COLUMNS], int coordinates[2], char direction[2], int size)
{
    int i, result;
    do { // Start coordinates
        result = 0;
        printf("\tVertical or horizontal (v/h) : ");
        input(direction, 2);
        if (direction[0] == 'v' || direction[0] == 'h')
            result = 1;
    } while(result == 0);

    // Check if the ship don't overflow of array
    if (direction[0] == 'v') {
        if (coordinates[0] + size > ROWS) {
            printf("\t\tError: the ship overflow the array.\n");
            return 0;
        } else {
            result = 1;
        }
    } else if (direction[0] == 'h') {
        if (coordinates[1] + size > COLUMNS) {
            printf("\t\tError: the ship overflow the array.\n");
            return 0;
        } else {
            result = 1;
        }
    }
    // Check if the ship don't overcome another ship
    if (direction[0] == 'v') {
        for (i = coordinates[0]; i < coordinates[0] + size; i++) {
            if (Main[i][coordinates[1]].type != '-') {
                printf("\t\tError: a ship already exists at this position.\n");
                return 0;
            }
        }
        result = 1;
    } else if (direction[0] == 'h') {
        for (i = coordinates[1]; i < coordinates[1] + size; i++) {
            if (Main[coordinates[0]][i].type != '-') {
                printf("\t\tError: a ship already exists at this position.\n");
                return 0;
            }
        }
        result = 1;
    }

    return result;
}

void create(Cell Main[ROWS][COLUMNS], int coordinates[2], char direction[2], int size, char type)
{
    int i;
    for (i = 0; i < size; i++) {
        if (direction[0] == 'v') {
            Main[coordinates[0] + i][coordinates[1]].type = type;
            if (i + 1 < size)
                Main[coordinates[0] + i][coordinates[1]].next = &Main[coordinates[0] + i][coordinates[1]];
            if (i > 0)
                Main[coordinates[0] + i][coordinates[1]].prev = &Main[coordinates[0] + i - 1][coordinates[1]];
        } else if (direction[0] == 'h') {
            Main[coordinates[0]][coordinates[1] + i].type = type;
            if (i + 1 < size)
                Main[coordinates[0]][coordinates[1] + i].next = &Main[coordinates[0]][coordinates[1] + i + 1];
            if (i > 0)
                Main[coordinates[0]][coordinates[1] + i].prev = &Main[coordinates[0]][coordinates[1] + i - 1];
        }
    }
}

void setup(Cell Main[ROWS][COLUMNS])
{
    int i, result;
    int coordinates[2] = {0};
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

