#include "area.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void load_areas(area_t** list, size_t* n, FILE* file)
{
	if (*list)
	{
		return;	// Don't override the existing data in memory.
	}

	size_t size = 0;
	const size_t init_capacity = 0;
	size_t capacity = init_capacity;
	float increment_factor = 1.25f;

	// Read one area record at a time.
	char* line;
	while((line = readline(file)) != NULL)
	{
		// Extract area record from the line containing one area record in text form.
		int areaID;
        char name[256];
        int IDupperArea;
        char type;
		sscanf(line, "%d%s%d %c", &areaID, name, &IDupperArea, &type);
        
		// Adjust capacity of the list.
		if (size >= capacity)
		{
			capacity = max(ceil(capacity * increment_factor), 1);
			*list = realloc(*list, sizeof(area_t) * capacity);
		}

		// Insert new area record into the list.
		(*list)[size].areaID = areaID;
		strcpy((*list)[size].name, name);
		(*list)[size].IDupperArea = IDupperArea;
		(*list)[size].type = type;

		*n = ++size;

		free(line);
	}
}