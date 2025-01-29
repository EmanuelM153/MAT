#ifndef MATRIX_OP_H_INCLUDED
#define MATRIX_OP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FLOAT_PREC 1000000

typedef struct
{
        int row_size;
        int col_size;
        double **elements;
} Matrix;

Matrix *mtrx_create(int, int);
void mtrx_fill(Matrix *);
void mtrx_print(Matrix *);
void mtrx_free(Matrix *);
Matrix *mtrx_transpose(Matrix *);
Matrix *mtrxs_add(Matrix *, Matrix *);
Matrix *mtrxs_multiply(Matrix *, Matrix *);
Matrix *mtrx_duplicate(Matrix *);
Matrix *mtrx_multiply(Matrix *, double);
Matrix *mtrx_rref(Matrix *);
double mtrx_determine(Matrix *);
Matrix *mtrx_identity(int);
Matrix *mtrxs_augment(Matrix *, Matrix *);
Matrix *mtrx_inverse(Matrix *);

double round_num(double, int);
int ref(Matrix *);
int col_size(double **);
void add_rows(double **, double **);
void multiply_row(double **, double);
void swap_rows(double **, double **);
#endif
