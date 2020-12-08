#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "city.h"
#include "area.h"
#include "street.h"


int main(int argc, char** argv)
{
	// Ensure proper usage.
	if (argc != 4)
	{
		printf("Usage: %s CITY_FILE AREA_FILE STREET_FILE\n", argv[0]);
		return 1;
	}

	// Remember input file paths.
	const char* city_file_path = argv[1];
	const char* area_file_path = argv[2];
	const char* street_file_path = argv[3];

	// Open files for reading.
	FILE* city_file = fopen(city_file_path, "r");
	if (! city_file)
	{
		printf("Couldn't open %s for reading\n", city_file_path);
		return 2;
	}
	FILE* area_file = fopen(area_file_path, "r");
	if (! area_file)
	{
		printf("Couldn't open %s for reading\n", area_file_path);
		fclose(city_file);
		return 2;
	}
	FILE* street_file = fopen(street_file_path, "r");
	if (! street_file)
	{
		printf("Couldn't open %s for reading", street_file_path);
		fclose(city_file);
		fclose(area_file);
		return 2;
	}

	// Load cities into memory.
	city_t* city_list = NULL;
	size_t city_list_size;
	load_cities(&city_list, &city_list_size, city_file);

	// Load areas into memory.
	area_t* area_list = NULL;
	size_t area_list_size;
	load_areas(&area_list, &area_list_size, area_file);

	// Load streets into memory.
	street_t* street_list = NULL;
	size_t street_list_size;
	load_streets(&street_list, &street_list_size, street_file);

	
	
	
	// Free memory.
	free(city_list);
	free(area_list);
	free(street_list);

	// Close files.
	fclose(city_file);
	fclose(area_file);
	fclose(street_file);

	// Success.
	return 0;
}
