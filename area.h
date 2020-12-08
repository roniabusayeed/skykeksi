#ifndef AREA_H
#define AREA_H

#include <stddef.h>
#include <stdio.h>

typedef struct area_t
{
    int areaID;
    char name[256];
    int IDupperArea;
    char type;
}area_t;

// type characters meanings:
// R = Region
// L = Country
// K = Continent

void load_areas(area_t** list, size_t* n, FILE* file);

#endif // AREA_H