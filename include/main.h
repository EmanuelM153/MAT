#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sll.h"
#include "matrix_op.h"
#include "eval.h"
#include "error.h"
#include "mnode.h"
#include "util_text.h"

#if HAVE_CONFIG_H
#include "config.h"
#endif

#define EVAL_SIZE 300
#define OPTION_SIZE 11

void help();
enum Error create_matrix(char *);
enum Error print_matrix(char *);
enum Error delete_matrix(char *);
enum Error duplicate_matrix(char *, char *);
enum Error rref_matrix(char *);
enum Error eval_expr(Matrix **);
int valid_name(char *);
