// tail.c
// Řešení IJC-DU2, příklad 1), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 512 // 510 + \n + \0

// creates string buffer of the specified size
// returns the buffer or NULL if error occured
char** buffer_create(unsigned size)
{
    char **buffer = malloc(size * sizeof(char*));
    if (buffer == NULL)
        return NULL;

    for (unsigned i = 0; i < size; i++)
    {
        char *line = calloc(MAX_LEN, 1); // initialize the memory
        if (line == NULL)
            return NULL;

        buffer[i] = line;
    }
    return buffer;
}

// prints buffer to stdout
// prints in reverse order
void buffer_print(char **buffer, unsigned n)
{
    do
    {
        printf("%s", buffer[n--]);
    } while (n != 0);
}

// frees the buffer
void buffer_free(char **buffer, unsigned buff_size)
{
    for (unsigned i = 0; i < buff_size; i++)
        free(buffer[i]);

    free(buffer);
}

void usage()
{
    fprintf(stderr, "Usage: tail [-n number] [file]\n");
}

int read_line(char *buff, unsigned max, FILE *f)
{
    static bool warn = true;
    unsigned len = 0;
    int c;

    while ((c = fgetc(f)) != EOF)
    {
        if (len < max - 2)
        {
            buff[len++] = c;
            if (c == '\n')
            {
                buff[len++] = '\0';
                return len;
            }
        }
        else
        {
            if (warn)
            {
                fprintf(stderr, "Exceeded line lenght limit!\n");
                warn = false;
            }

            // consume remaining chars
            while ((c = fgetc(f)) != EOF && c != '\n');

            buff[len++] = '\n';
            buff[len++] = '\0';
            return len;
        }
    }
    return EOF;
}

// return true on success, false on failure
bool tail(unsigned n, FILE *file)
{
    unsigned buff_size = n + 1; // we need one more line to read into

    char **buffer = buffer_create(buff_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate buffer!\n");
        return false;
    }

    unsigned lines_read = 0;
    while (read_line(buffer[0], MAX_LEN, file) != EOF)
    {
        if (lines_read < buff_size - 1)
            lines_read++;

        // push all lines down by 1 in the buffer
        for (unsigned i = buff_size - 1; i > 0; i--)
            strcpy(buffer[i], buffer[i - 1]);
    }

    buffer_print(buffer, lines_read);
    buffer_free(buffer, buff_size);
    return true;
}

// prints all lines beggining from line number "line num"
void from_line(unsigned line_num, FILE *file)
{
    unsigned line = 1;
    char buff[MAX_LEN];
    while (fgets(buff, MAX_LEN, file))
    {
        if (line >= line_num)
            printf("%s", buff);

        line++;
    }
}

int main(int argc, char *argv[])
{
    int n = 10;
    bool from_stdin = true;
    bool start_mode = false;

    char *filename;

    if (argc > 2 && argc <= 4)
    {
        if (strcmp("-n", argv[1]) == 0)
        {
            if (argv[2][0] == '+')
                start_mode = true;

            char *rest;
            n = strtol(argv[2], &rest, 10);
            if (*rest != '\0')
            {
                fprintf(stderr, "Error: Option -n requires integer argument!\n");
                return EXIT_FAILURE;
            }
        }
        else
        {
            fprintf(stderr, "Error: unexpected argument %s!\n", argv[1]);
            return EXIT_FAILURE;
        }

        if (argc == 4)
        {
            from_stdin = false;
            filename = argv[3];
        }
    }
    else if (argc == 2)
    {
        from_stdin = false;
        filename = argv[1];
    }
    else if (argc != 1)
    {
        fprintf(stderr, "Error: Too many arguments!\n");
        return EXIT_FAILURE;
    }

    FILE *file;
    if (from_stdin)
        file = stdin;
    else
    {
        file = fopen(filename, "r");
        if (file == NULL)
        {
            perror("tail");
            return EXIT_FAILURE;
        }
    }

    if (start_mode)
        from_line(n, file);
    else 
    {
        if (!tail(n, file))
        {
            fprintf(stderr, "Error: Memory allocation failed!\n");
            return EXIT_FAILURE;
        }
    }

    if (!from_stdin)
        fclose(file);

    return EXIT_SUCCESS;
}
