#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// Reads an entire line from the stream and returns the address of the 
// buffer containing the text. Returns NULL on failure to read a line (in-
// cluding end of file condition).

// getline() will allocate a buffer  for  storing  the  line. This  buffer
// should  be freed by the user program.

// The buffer is null terminated and doesn't include the newline character
// if one was found.
char* readline(FILE* stream);

#define max(a, b) (((a) > (b)) ? (a) : (b))

#endif  // UTILS_H