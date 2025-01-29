#ifndef SLL_H_INCLUDED
#define SLL_H_INCLUDED

#include <stdlib.h>

typedef struct
{
        void *data;
        void *next;
} Lnode;

Lnode *add_node(void *, int, Lnode **);
void *delete_node(Lnode *, Lnode **);
#endif
