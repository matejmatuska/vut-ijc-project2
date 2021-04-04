#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "io.h"

int read_word(char *s, int max, FILE *f)
{
    if (max < 1)
    {
        fprintf(stderr, "Error: read_word: max must be > 0\n");
        return 0;
    }
    if (f == NULL)
    {
        fprintf(stderr, "Error: read_word: f is NULL\n");
        return 0;
    }

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

