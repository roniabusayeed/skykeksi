#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "city.h"
#include "area.h"
#include "street.h"


// Prototypes.
area_t find_area_struct(int id, int area_list_size, area_t* area_list);
int find_country_id(area_t area , int area_list_size, area_t* area_list);


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
	
	
	for(int i = 0; i < city_list_size; i++)
	{	
		city_t current_city = city_list[i];
		int current_city_area_id = current_city.areaID;
		area_t current_city_area = find_area_struct(current_city_area_id, area_list_size, area_list);
		int current_country_id = find_country_id(current_city_area, area_list_size, area_list);
		
		int current_city_connected[256];
		int current_city_connected_size = 0;
		
		for(int streetIt = 0; streetIt < street_list_size; streetIt++)
		{
			street_t current_street = street_list[streetIt];
			if(current_street.fromCityID == current_city.cityID)
			{
				current_city_connected[current_city_connected_size] = current_street.toCityID;
				current_city_connected_size++;
			}else if(current_street.toCityID == current_city.cityID)
			{
				current_city_connected[current_city_connected_size] = current_street.fromCityID;
				current_city_connected_size++;
			}	
		}
		
		int flag = 0;
		
		for(int j = 0; j < city_list_size; j++)
		{
			if(i != j)
			{
				city_t next_city = city_list[j];
				int next_city_area_id = next_city.areaID;
				area_t next_city_area = find_area_struct(next_city_area_id, area_list_size, area_list);
				int next_country_id = find_country_id(next_city_area, area_list_size, area_list);
				
				if(current_country_id != next_country_id)
				{
					for(int current_streetIt = 0; current_streetIt < current_city_connected_size; current_streetIt++){
						if(current_city_connected[current_streetIt] == next_city.cityID)
						{
							flag = 1;
							break;
						}
					}
				}
			}
		}
		
		if(flag == 0){
			printf("%s\n", current_city.name);
		}
	}
	
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


area_t find_area_struct(int id, int area_list_size, area_t* area_list)
{
	for(int areaIt = 0; areaIt < area_list_size; areaIt ++)
	{
		if(area_list[areaIt].areaID == id)
		{
			return area_list[areaIt];
		}
	}
}


int find_country_id(area_t area , int area_list_size, area_t* area_list)
{
	if (area.type == 'L')
	{
		return area.areaID;
	}
	else if(area.type == 'R')
	{
		area_t temp = find_area_struct(area.IDupperArea, area_list_size, area_list);
		return temp.areaID;
	}
	return 0;
}
