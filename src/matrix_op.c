#include "matrix_op.h"

Matrix *mtrx_create(int row_size, int col_size)
{
        Matrix *matrix = malloc(sizeof(Matrix));
        double *data = calloc(row_size * col_size, sizeof(double));

        matrix->row_size = row_size;
        matrix->col_size = col_size;
        matrix->elements = malloc((row_size + 1) * sizeof(double *));

        for (int i = 0; i < row_size; i++)
                matrix->elements[i] = data + i * col_size;

        matrix->elements[row_size] = data + row_size * col_size;

        return matrix;
}

void mtrx_fill(Matrix *matrix)
{
        for (int i = 0; i < matrix->row_size; i++) {
                printf("\t> ");
                for (int j = 0; j < matrix->col_size; j++)
                        scanf("%lf", matrix->elements[i] + j);
        }
}

void mtrx_print(Matrix *matrix)
{
        for (int i = 0; i < matrix->row_size; i++) {
                for (int j = 0; j < matrix->col_size; j++)
                        printf("%5.2lf  ", matrix->elements[i][j]);
                printf("\n");
        }
}

void mtrx_free(Matrix *matrix)
{
        free(*(matrix->elements));
        free(matrix->elements);
        free(matrix);
}

Matrix *mtrx_transpose(Matrix *matrix)
{
        Matrix *transposed = mtrx_create(matrix->col_size, matrix->row_size);

        for (int i = 0; i < matrix->row_size; i++)
                for (int j = 0; j < matrix->col_size; j++)
                        transposed->elements[j][i] = matrix->elements[i][j];

        return transposed;
}

Matrix *mtrxs_add(Matrix *matrix1, Matrix *matrix2)
{
        Matrix *result = NULL;

        if (matrix1->row_size == matrix2->row_size
            && matrix1->col_size == matrix2->col_size) {
                result = mtrx_create(matrix1->row_size, matrix1->col_size);

                for (int i = 0; i < matrix1->row_size; i++) {
                        for(int j = 0; j < matrix1->col_size; j++)
                                result->elements[i][j] = matrix1->elements[i][j]
                                        + matrix2->elements[i][j];
                }
        }

        return result;
}

Matrix *mtrxs_multiply(Matrix *matrix1, Matrix *matrix2)
{
        Matrix *result = NULL;

        if (matrix1->col_size == matrix2->row_size) {
                result = mtrx_create(matrix1->row_size, matrix2->col_size);

                for (int i = 0; i < matrix1->row_size; i++) {
                        for (int j = 0; j < matrix2->col_size; j++) {
                                for (int k = 0; k < matrix1->col_size; k++)
                                        result->elements[i][j] +=
                                                matrix1->elements[i][k]
                                                * matrix2->elements[k][j];
                        }
                }
        }

        return result;
}

Matrix *mtrx_duplicate(Matrix *matrix)
{
        Matrix *duplicate = mtrx_create(matrix->row_size, matrix->col_size);

        int num_byte = matrix->row_size * matrix->col_size * sizeof(double);
        memcpy(*(duplicate->elements), *(matrix->elements), num_byte);

        return duplicate;
}

Matrix *mtrx_multiply(Matrix *matrix, double factor)
{
        for (int i = 0; i < matrix->row_size; i++)
                multiply_row(matrix->elements + i, factor);

        return matrix;
}

Matrix *mtrx_rref(Matrix *matrix)
{
        ref(matrix);

        for (int i = 0; i < matrix->row_size; i++) {
                if (0 != round_num(matrix->elements[i][i], FLOAT_PREC))
                        multiply_row(matrix->elements + i,
                                     1.0 / matrix->elements[i][i]);
        }

        int pivot = matrix->row_size - 1;
        double factor;
        Matrix *row = mtrx_create(1, matrix->col_size);

        while (pivot > 0) {
                if (0 != round_num(matrix->elements[pivot][pivot]
                                   , FLOAT_PREC)) {
                        for (int i = pivot - 1; i >= 0; i--) {
                                factor = matrix->elements[i][pivot]
                                        / matrix->elements[pivot][pivot];

                                memcpy(*row->elements,
                                       *(matrix->elements + pivot),
                                       matrix->col_size * sizeof(double));
                                multiply_row(row->elements, -factor);
                                add_rows(matrix->elements + i, row->elements);
                        }
                }
                pivot--;
        }
        mtrx_free(row);

        return matrix;
}

double mtrx_determine(Matrix *matrix)
{
        double determinant = -1;

        if (matrix->row_size == matrix->col_size) {
                determinant = 1;
                int num_swaps = ref(matrix);

                for (int i = 0; i < matrix->row_size; i++)
                        determinant *= matrix->elements[i][i];

                if (1 == num_swaps % 2)
                        determinant *= -1.0;
        }

        return determinant;
}

Matrix *mtrx_identity(int size)
{
        Matrix *identity = mtrx_create(size, size);

        for (int i = 0; i < size; i++)
                identity->elements[i][i] = 1;

        return identity;
}

Matrix *mtrxs_augment(Matrix *matrix1, Matrix *matrix2)
{
        Matrix *result = NULL;

        if (matrix1->row_size == matrix2->row_size) {
                result = mtrx_create(matrix1->row_size,
                                       matrix1->col_size + matrix2->col_size);

                for (int i = 0; i < matrix1->row_size; i++) {
                        memcpy(result->elements[i], matrix1->elements[i],
                               matrix1->col_size * sizeof(double));
                        memcpy(result->elements[i] + matrix1->col_size,
                               matrix2->elements[i],
                               matrix2->col_size * sizeof(double));
                }
        }

        return result;
}

Matrix *mtrx_inverse(Matrix *matrix)
{
        Matrix *inverse = NULL;

        if (matrix->col_size == matrix->row_size) {
                Matrix *identity = mtrx_identity(matrix->row_size);
                Matrix *gaussian_result = mtrxs_augment(matrix, identity);
                inverse = mtrx_create(matrix->row_size, matrix->col_size);

                mtrx_rref(gaussian_result);

                for (int i = 0; i < matrix->row_size; i++)
                        memcpy(inverse->elements[i],
                               gaussian_result->elements[i] + matrix->col_size,
                               matrix->col_size * sizeof(double));

                mtrx_free(identity);
                mtrx_free(gaussian_result);
        }

        return inverse;
}

double round_num(double num, int precision)
{
        double value = (int) (num * precision);

        return (double) value / precision;
}

int ref(Matrix *matrix)
{
        int pivot = 0;
        int pivot_not_zero;
        double factor;
        int num_swaps = 0;
        Matrix *row = mtrx_create(1, matrix->col_size);

        while (pivot < matrix->row_size) {
                pivot_not_zero = -1;

                for (int i = pivot; i < matrix->row_size; i++) {
                        if (0 != round_num(matrix->elements[i][pivot],
                                          FLOAT_PREC)) {
                                pivot_not_zero = i;
                                break;
                        }
                }

                if (-1 != pivot_not_zero) {
                        if (pivot != pivot_not_zero) {
                                swap_rows(matrix->elements + pivot,
                                          matrix->elements + pivot_not_zero);
                                num_swaps++;
                        }

                        for (int i = pivot + 1; i < matrix->row_size; i++) {
                                factor = matrix->elements[i][pivot]
                                        / matrix->elements[pivot][pivot];

                                memcpy(*row->elements,
                                        *(matrix->elements + pivot),
                                       matrix->col_size * sizeof(double));
                                multiply_row(row->elements, -factor);
                                add_rows(matrix->elements + i, row->elements);
                        }
                }
                pivot++;
        }
        mtrx_free(row);

        return num_swaps;
}

int col_size(double **row)
{
        return *(row + 1) - *row;
}

void add_rows(double **row1, double **row2)
{
        for (int i = 0; i < col_size(row1); i++)
                *(*row1 + i) += *(*row2 + i);
}

void multiply_row(double **row, double factor)
{
        for (int i = 0; i < col_size(row); i++)
                *(*row + i) *= factor;
}

void swap_rows(double **row1, double **row2)
{
        int num_byte = col_size(row1) * sizeof(double);
        double *temp = malloc(num_byte);

        memcpy(temp, *row1, num_byte);
        memcpy(*row1, *row2, num_byte);
        memcpy(*row2, temp, num_byte);

        free(temp);
}
