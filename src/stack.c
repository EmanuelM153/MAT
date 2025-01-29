#include "stack.h"

int is_empty(Snode *root)
{
        int empty = 1;
        if (root != NULL)
                empty = 0;

        return empty;
}

void *stck_pop(Snode **root)
{
        void *data = NULL;
        Snode *old_node = NULL;

        if (!is_empty(*root)) {
                old_node = *root;
                data = (*root)->data;
                *root = (*root)->next;
                free(old_node);
        }

        return data;
}

void stck_push(Snode **root, void *data)
{
        Snode *new = malloc(sizeof(Snode));
        new->data = data;
        new->next = *root;
        *root = new;
}

void *stck_top(Snode **root)
{
        void *data = NULL;

        if (!is_empty(*root))
                data = (*root)->data;

        return data;
}


