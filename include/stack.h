#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

typedef struct
{
        void *data;
        void *next;
} Snode;

int is_empty(Snode *);
void *stck_pop(Snode **);
void stck_push(Snode **, void *);
void *stck_top(Snode **);
#endif

