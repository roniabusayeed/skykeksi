#ifndef STREET_H
#define STREET_H
#include <stddef.h>
#include <stdio.h>

typedef struct street_t
{
    int fromCityID;
    int toCityID;
    int distance;
}street_t;


void load_streets(street_t** list, size_t* n, FILE* file);

#endif // STREET_H