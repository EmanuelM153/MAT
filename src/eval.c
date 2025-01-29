#include "eval.h"

enum Error e_eval(char *expr, Matrix **matrix, Mnode **head)
{
        enum Error error = OK;
        char *token = NULL;
        Snode *root = NULL;
        Matrix *result;

        Matrix *mat1 = NULL;
        Matrix *mat2 = NULL;
        Mnode *wrapper = NULL;

        while (token = strtok_r(expr, " ", &expr)) {
                result = NULL;
                if (word_inside(token, binary_op)) {
                        mat1 = stck_pop(&root);
                        mat2 = stck_pop(&root);

                        switch (*token) {
                        case '+':
                                result = mtrxs_add(mat1, mat2);
                                break;
                        case '*':
                                result = mtrxs_multiply(mat1, mat2);
                                break;
                        case '&':
                                result = mtrxs_augment(mat2, mat1);
                                break;
                        case '^':
                                result = calc_exponent(mat2, **mat1->elements);
                                break;
                        }

                        mtrx_free(mat1);
                        mtrx_free(mat2);

                        if (NULL == result) {
                                error = MATH_ERROR;
                                break;
                        } else {
                                stck_push(&root, result);
                        }
                } else if (word_inside(token, unary_op)) {
                        mat1 = stck_pop(&root);

                        switch(*token) {
                        case 'd':
                                result = calc_determinant(mat1);
                                break;
                        case 'T':
                                result = mtrx_transpose(mat1);
                                break;
                        }

                        mtrx_free(mat1);

                        if (NULL == result) {
                                error = MATH_ERROR;
                                break;
                        } else {
                                stck_push(&root, result);
                        }
                } else {
                        wrapper = find_by_name(token, head);

                        if (NULL != wrapper) {
                                stck_push(&root, mtrx_duplicate(wrapper->data));
                        } else if (is_number(token)) {
                                mat1 = stck_top(&root);

                                mat2 = mtrx_identity((mat1 == NULL)
                                                     ? 1 : mat1->row_size);

                                mtrx_multiply(mat2, atof(token));

                                stck_push(&root, mat2);
                        } else {
                                error = NOT_FOUND;
                                break;
                        }
                }
        }

        *matrix = stck_pop(&root);

        return error;
}
Matrix *calc_determinant(Matrix *mat)
{
        Matrix *result = NULL;
        double determinant;

        determinant = mtrx_determine(mat);
        if (-1 != determinant) {
                result = mtrx_create(1, 1);
                **result->elements = determinant;
        }

        return result;
}

Matrix *calc_exponent(Matrix *mat, int num)
{
        Matrix *result = NULL;
        Matrix *aux = NULL;

        if (-1 == num) {
                result = mtrx_inverse(mat);
        } else if (0 == num) {
                result = mtrx_identity(mat->row_size);
        } else if (num > 0) {
                result = mtrx_duplicate(mat);
                for (int i = 0; i < num - 1; i++) {
                        aux = result;
                        result = mtrxs_multiply(result, mat);
                        mtrx_free(aux);
                }
        }

        return result;
}
