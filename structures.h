#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct Cell Cell;
struct Cell
{
    char type;
    Cell *prev;
    Cell *next;
};

#endif // STRUCTURES_H_INCLUDED
