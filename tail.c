#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 512

// creates string buffer of the specified size
// returns the buffer or NULL if error occured
char** buffer_create(unsigned size)
{
    char **buffer = malloc(size * sizeof(char*));
    if (buffer == NULL)
        return NULL;

    for (unsigned i = 0; i < size; i++)
    {
        char *line = malloc(MAX_LEN);
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
    unsigned i = n - 1;
    do
    {
        printf("%s", buffer[i--]);
    } while (i != 0);
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

void tail(unsigned n, FILE *file)
{
    unsigned buff_size = ++n;

    char **buffer = buffer_create(buff_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate buffer!\n");
        //return EXIT_FAILURE;
        return; //TODO error handling
    }

    unsigned lines_read = 0;
    while (fgets(buffer[0], MAX_LEN, file))
    {
        if (lines_read < buff_size)
            lines_read++;

        // push all lines down by 1 in the buffer
        for (unsigned i = buff_size - 1; i > 0; i--)
            strcpy(buffer[i], buffer[i - 1]);
    }

    buffer_print(buffer, lines_read);
    buffer_free(buffer, buff_size);
}

void from_line(unsigned line_num, FILE *file)
{
    unsigned line = 0; // 1 based
    char buff[MAX_LEN];
    while (fgets(buff, MAX_LEN, file))
    {
        line++;
        if (line >= line_num)
            printf("%s", buff);
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
            filename = argv [3];
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
        tail(n, file);

    if (!from_stdin)
        fclose(file);

    return EXIT_SUCCESS;
}
