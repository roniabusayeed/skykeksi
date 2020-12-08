#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char* readline(FILE* stream)
{
    char* line = NULL;
    size_t size = 0;
    ssize_t line_len;
    if((line_len = getline(&line ,&size, stream)) != EOF)
    {
        line[line_len - 1] = '\0';
        return line;
    }

    free(line);
    return NULL;
}
