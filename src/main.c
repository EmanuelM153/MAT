#include "main.h"
#include "config.h"

const char *one_selection = "p,d,rref,c";
const char *two_selection = "dup";
const char *no_selection = "help,eval,all,ls,quit";
const char *invalid_names = "(,)";

Mnode *head = NULL;
Mnode *ans = NULL;

int main()
{
        enum Error error;
        char option[OPTION_SIZE];
        char name[NAME_SIZE];
        char name2[NAME_SIZE];

        Matrix *result = NULL;

        initialize_ans(&ans);

        help();
        do {
                error = OK;

                printf("> ");
                scan(option, OPTION_SIZE);

                if (word_inside(option, one_selection)) {
                        scan(name, NAME_SIZE);

                        switch(*option) {
                        case 'p':
                                error = print_matrix(name);
                                break;
                        case 'd':
                                error = delete_matrix(name);
                                break;
                        case 'r':
                                error = rref_matrix(name);
                                break;
                        case 'c':
                                error = create_matrix(name);
                                break;
                        }
                } else if (word_inside(option, two_selection)) {
                        scan(name, NAME_SIZE);
                        scan(name2, NAME_SIZE);

                        switch(*option) {
                        case 'd':
                                error = duplicate_matrix(name, name2);
                                break;
                        }
                } else if (word_inside(option, no_selection)) {
                        switch(*option) {
                        case 'h':
                                help();
                                break;
                        case 'e':
                                error = eval_expr(&result);
                                break;
                        case 'a':
                                all_matrices(&head);
                                break;
                        case 'l':
                                list_matrices(&head);
                                break;
                        case 'q':
                                strncpy(option, "quit", OPTION_SIZE);
                                break;
                        }
                } else {
                        printf("Type (help) for information on usage");
                }

                print_error(error);
                printf("\n");
        } while(0 != strncmp("quit", option, OPTION_SIZE));

        mnode_destroy(&ans);
}

void help()
{
        printf("Options:\n");
        printf("\t(c)reate matrix\n");
        printf("\t(p)rint Matrix\n");
        printf("\tprint (all) matrices\n");
        printf("\tReduced Row Echelon Form (rref)\n");
        printf("\t(ls)ist matrices\n");
        printf("\t(dup)licate matrix\n");
        printf("\t(d)elete matrix\n");
        printf("\t(eval) expression\n");
        printf("\t(help)\n");
        printf("\tQuit (quit)\n");
}

enum Error create_matrix(char *name)
{
        enum Error error = EXISTENT;
        int row_size;
        int col_size;
        Matrix *mat = NULL;
        Mnode *selection = NULL;

        scanf("%d", &row_size);
        scanf("%d", &col_size);

        if (valid_name(name)) {
                selection = find_by_name(name, &ans);

                if (NULL == selection) {
                        if (row_size <= 0 || col_size <= 0) {
                                error = INVALID_SIZE;
                        } else {
                                error = OK;
                                mat = mtrx_create(row_size, col_size);
                                mtrx_fill(mat);
                                add_mnode(mat, name, &head);
                                set_next(ans, head);
                        }
                }
        } else {
                error = INVALID_ENTRY;
        }

        return error;
}

enum Error print_matrix(char *name)
{
        enum Error error = NOT_FOUND;

        Mnode *selection = find_by_name(name, &ans);

        if (NULL != selection) {
                error = OK;
                mtrx_print(selection->data);
        }

        return error;
}

enum Error delete_matrix(char *name)
{
        enum Error error = NOT_FOUND;

        Mnode *selection = find_by_name(name, &head);

        if (NULL != selection) {
                error = OK;
                delete_mnode(selection, &head);
                set_next(ans, head);
        }


        return error;
}

enum Error duplicate_matrix(char *name, char *name2)
{
        enum Error error = NOT_FOUND;

        Mnode *selection = find_by_name(name, &ans);
        Mnode *selection2 = find_by_name(name2, &ans);

        if (NULL != selection) {
                if (NULL == selection2) {
                        error = OK;
                        add_mnode(mtrx_duplicate(selection->data), name2, &head);
                        set_next(ans, head);
                } else {
                        error = EXISTENT;
                }
        }

        return error;
}

enum Error rref_matrix(char *name)
{
        enum Error error = NOT_FOUND;
        Mnode *selection = find_by_name(name, &ans);

        if (NULL != selection) {
                error = OK;

                Matrix *duplicate = mtrx_duplicate(selection->data);
                Matrix *rref = mtrx_rref(duplicate);
                mtrx_print(rref);
                update_ans(ans, rref);
        }

        return error;
}

enum Error eval_expr(Matrix **matrix)
{
        enum Error error = OK;
        char expr[EVAL_SIZE];

        fgets(expr, EVAL_SIZE, stdin);
        expr[strlen(expr) - 1] = '\0';
        error = e_eval(expr, matrix , &ans);

        if (OK == error) {
                update_ans(ans, *matrix);
                mtrx_print(*matrix);
        }

        return error;
}

int valid_name(char *name)
{
        int valid = 1;

        valid = valid && !word_inside(name, unary_op)
                && !word_inside(name, binary_op)
                && !word_inside(name, invalid_names)
                && !isdigit(*name);

        return valid;
}
