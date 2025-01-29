#include "sll.h"

Lnode *add_node(void *data, int size, Lnode **root)
{
        Lnode *new = malloc(size);

        new->data = data;
        new->next = NULL;

        if (NULL == *root) {
                *root = new;
        } else {
                while (NULL != (*root)->next)
                        *root = (*root)->next;

                (*root)->next = new;
        }

        return new;
}

void *delete_node(Lnode *node, Lnode **root)
{
        void *data = NULL;
        Lnode *prev = *root;
        Lnode *current = *root;

        while (NULL != current) {
                if (node == current) {
                        if (current == *root)
                                *root = current->next;
                        else
                                prev->next = current->next;

                        data = current->data;
                        free(current);
                        current = NULL;
                        break;
                }

                prev = current;
                current = current->next;
        }

        return data;
}
