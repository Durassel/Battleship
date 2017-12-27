#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "structures.h"

void flush();
int input(char *str, int size);
int multipleCoordinates(char coordinates[4]);
int convertColumnToInt(char column);
int check(Cell Main[ROWS][COLUMNS], char coordinates[4]);
void selectCoordinates(Cell Main[ROWS][COLUMNS], char coordinates[4]);
int selectDirection(Cell Main[ROWS][COLUMNS], char coordinates[4], char direction[2], int size);
void create(Cell Main[ROWS][COLUMNS], char coordinates[4], char direction[2], int size, char type);
void setup(Cell Main[ROWS][COLUMNS]);

#endif // SHIP_H_INCLUDED


