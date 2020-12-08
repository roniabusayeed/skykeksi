#include "city.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <math.h>
#include <string.h>


void load_cities(city_t** list, size_t* n, FILE* file)
{
	if (*list)
	{
		return;	// Don't override the existing data in memory.
	}

	size_t size = 0;
	const size_t init_capacity = 0;
	size_t capacity = init_capacity;
	float increment_factor = 1.25f;

	// Read one city record at a time.
	char* line;
	while((line = readline(file)) != NULL)
	{
		// Extract city record from the line containing one city record in text form.
		int cityID;
		char name[256];
		int citizen;
		int areaID;
		int sealevel;
		sscanf(line, "%d%s%d%d%d", &cityID, name, &citizen, &areaID, &sealevel);

		// Adjust capacity of the list.
		if (size >= capacity)
		{
			capacity = max(ceil(capacity * increment_factor), 1);
			*list = realloc(*list, sizeof(city_t) * capacity);
		}

		// Insert new city record into the list.
		(*list)[size].cityID = cityID;
		strcpy((*list)[size].name, name);
		(*list)[size].citizen = citizen;
		(*list)[size].areaID = areaID;
		(*list)[size].sealevel = sealevel;

		*n = ++size;

		free(line);
	}
}
