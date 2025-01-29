#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <stdio.h>

enum Error{
        OK,
        NOT_FOUND,
        INVALID_SIZE,
        EXISTENT,
        DIFFERENT_SIZE,
        INVALID_SYNTAX,
        MATH_ERROR,
        INVALID_ENTRY
};

void print_error(enum Error);
#endif
