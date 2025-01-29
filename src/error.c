#include "error.h"

void print_error(enum Error error)
{
        switch (error) {
        case NOT_FOUND:
                printf("Matrix not found");
                break;
        case INVALID_SIZE:
                printf("Invalid size");
                break;
        case EXISTENT:
                printf("Existent matrix");
                break;
        case DIFFERENT_SIZE:
                printf("Incorrect matrix sizes");
                break;
        case INVALID_SYNTAX:
                printf("Syntax Error");
                break;
        case MATH_ERROR:
                printf("Math Error");
                break;
        case INVALID_ENTRY:
                printf("Invalid Entry");
                break;
        default:
                break;
        }
}
