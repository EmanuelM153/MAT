#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include <stdlib.h>
#include "error.h"
#include "matrix_op.h"
#include "stack.h"
#include "mnode.h"
#include "util_text.h"

static const char *binary_op = "+,*,&,^";
static const char *unary_op = "det,T";

enum Error e_eval(char *, Matrix **, Mnode **);
Matrix *calc_determinant(Matrix *);
Matrix *calc_exponent(Matrix *, int);
#endif



