#include "street.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void load_streets(street_t** list, size_t* n, FILE* file)
{
	if (*list)
	{
		return;	// Don't override the existing data in memory.
	}

	size_t size = 0;
	const size_t init_capacity = 0;
	size_t capacity = init_capacity;
	float increment_factor = 1.25f;

	// Read one street record at a time.
	char* line;
	while((line = readline(file)) != NULL)
	{
		// Extract street record from the line containing one street record in text form.
		int fromCityID;
        int toCityID;
        int distance;
		sscanf(line, "%d%d%d", &fromCityID, &toCityID, &distance);
        
		// Adjust capacity of the list.
		if (size >= capacity)
		{
			capacity = max(ceil(capacity * increment_factor), 1);
			*list = realloc(*list, sizeof(street_t) * capacity);
		}

		// Insert new area record into the list.
		(*list)[size].fromCityID = fromCityID;
		(*list)[size].toCityID = toCityID;
		(*list)[size].distance = distance;
		
		*n = ++size;

		free(line);
	}
}
