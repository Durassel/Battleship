#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "structures.h"

void flush();
int read(char *str, int size);
int tens(char coordinates[4]);
int testCoordinates(char start[4], Cell Main[ROWS][COLUMNS]);
void coordinates(char *start, Cell Main[ROWS][COLUMNS]);
int selectDirection(Cell Main[ROWS][COLUMNS], char *direction, char *start, int size);
int convertColumnToInt(char column);
void createShip(int size, char type, char start[4], char direction[2], Cell Main[ROWS][COLUMNS]);
void initShips(Cell Main[ROWS][COLUMNS]);

#endif // SHIP_H_INCLUDED


