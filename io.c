#include <stdio.h>
#include <ctype.h>

#include "io.h"

int read_word(char *s, int max, FILE *f)
{
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
            // exceeded max chars, read remaining chars
            int ch = fgetc(f); //TODO myabe use the one from while
            while (!isspace(ch) && ch != EOF)
                ch = fgetc(f);

            s[len + 1] = '\0';
            return len;
        }

        s[len++] = c;
    }

    return EOF;
}

