#include "util_text.h"

int word_inside(char *option, const char *options)
{
        int found = 0;

        char temp[strlen(options) + 1];
        char *token;
        strncpy(temp, options, strlen(options) + 1);
        char *rest = temp;

        while (token = strtok_r(rest, ",", &rest)) {
                if (!strcmp(token, option)) {
                        found = 1;
                        break;
                }
        }

        return found;
}

int scan(char *buffer, int size)
{
        char format[32];

        snprintf(format, sizeof(format), "%%%ds", size - 1);
        return scanf(format, buffer);
}

int is_number(char *num)
{
        int it_is = 1;

        for(int i = 0; i < (int) strlen(num); i++) {
                if ('-' != num[i] && '.' != num[i])
                    it_is  = it_is && isdigit(num[i]);
        }

        return it_is;
}
