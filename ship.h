#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "structures.h"

char lower(char c);
void flush(void);
int input(char *str, int size);
int multipleCoordinates(char inputs[4]);
void convertInputsToCoordinates(char inputs[4], int coordinates[2]);
int checkCoordinates(int coordinates[2]);
int checkCell(Cell Main[ROWS][COLUMNS], int coordinates[2], char c);
void selectCoordinates(Cell Main[ROWS][COLUMNS], int coordinates[2], char message[100]);
int selectDirection(Cell Main[ROWS][COLUMNS], int coordinates[2], char direction[2], int size);
void create(Cell Main[ROWS][COLUMNS], int coordinates[2], char direction[2], int size, char type);
void setup(Cell Main[ROWS][COLUMNS]);
int check(Cell Main[ROWS][COLUMNS], int coordinates[2]);

#endif // SHIP_H_INCLUDED


