#ifndef MNODE_H_INCLUDED
#define MNODE_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "matrix_op.h"
#include "sll.h"
#define NAME_SIZE 15
#define ANS "ANS"

typedef struct
{
        void *data;
        void *next;
        char name[NAME_SIZE];
} Mnode;

void add_mnode(Matrix *, char *, Mnode **);
Mnode *find_by_name(char *, Mnode **);
void delete_mnode(Mnode *, Mnode **);
void mnode_destroy(Mnode **);
void list_matrices(Mnode **);
void all_matrices(Mnode **);
void set_next(Mnode *, Mnode *);
void initialize_ans(Mnode **);
void update_ans(Mnode *, Matrix *);
#endif
