#ifndef CITY_H
#define CITY_H

#include <stddef.h>
#include <stdio.h>

typedef struct city_t
{
    int cityID;
    char name[256];
    int citizen;
    int areaID;
    int sealevel;

}city_t;

void load_cities(city_t** list, size_t* n, FILE* file);

#endif // CITY_H