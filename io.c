// io.c
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "io.h"

int read_word(char *s, int max, FILE *f)
{
    if (max < 1 || f == NULL)
        return -1;

    static bool warn = true;

    int len = 0;
    int c;
    while ((c = fgetc(f)) != EOF)
    {
        if (isspace(c))
        {
            if (len == 0)
            {
                // skip leading whitespace
                continue;
            }
            else
            {
                // reached end of the word
                s[len] = '\0';
                return len;
            }
        }

        if (len == max - 1)
        {
            // exceeded max chars
            if (warn)
            {
                fprintf(stderr, "Warning: read_word: word exceeded max word lenght!\n");
                warn = false;
            }

            // read remaining chars
            while ((c = fgetc(f)) != EOF && !isspace(c));

            s[len + 1] = '\0';
            return len;
        }

        s[len++] = c;
    }

    return EOF;
}

