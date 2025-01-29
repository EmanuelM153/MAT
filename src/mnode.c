#include "mnode.h"

void add_mnode(Matrix *matrix, char *name, Mnode **root)
{
        Mnode *new = (Mnode *) add_node(matrix, sizeof(Mnode), (Lnode **) root);
        strncpy(new->name, name, NAME_SIZE - 1);
}

Mnode *find_by_name(char *name, Mnode **root)
{
        Mnode *found = NULL;
        Mnode *current = *root;

        while (NULL != current) {
                if (!strncmp(current->name, name, NAME_SIZE)) {
                        found = current;
                        break;
                }

                current = current->next;
        }

        return found;
}

void delete_mnode(Mnode *mnode, Mnode **root)
{
        Matrix *mat = (Matrix *) delete_node((Lnode *) mnode, (Lnode **) root);
        mtrx_free(mat);
}

void mnode_destroy(Mnode **root)
{
        while (NULL != *root)
                delete_mnode(*root, root);
}

void list_matrices(Mnode **root)
{
        Mnode *current = *root;
        Matrix *data = NULL;

        while (NULL != current) {
                data = (Matrix *) current->data;
                printf("%s(%d, %d)\t", current->name,
                       data->row_size,
                       data->col_size);

                current = current->next;
        }
}

void all_matrices(Mnode **root)
{
        Mnode *current = *root;

        while (NULL != current) {
                printf("%s:\n", current->name);
                mtrx_print(current->data);
                printf("\n");

                current = current->next;
        }
}

void set_next(Mnode *mnode, Mnode *next)
{
        mnode->next = next;
}

void initialize_ans(Mnode **ans)
{
        double _ans[4][4] = { {1, 14, 14, 4},
                              {11, 7, 6, 9},
                              {8, 10, 10, 5},
                              {13, 2, 3, 15} };
        Matrix *ans_matrix = mtrx_create(4, 4);

        memcpy(*ans_matrix->elements, *_ans, sizeof(double) * 16);

        add_mnode(ans_matrix, ANS, ans);
}

void update_ans(Mnode *ans, Matrix *matrix)
{
        mtrx_free(ans->data);
        ans->data = matrix;
}
