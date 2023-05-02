/*!
@file       test-2-print.c
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 9
@date       20/11/2020
@brief      This test driver tests implementation of the following functions:
			* create_map()
			* set_tile()
			* print_map()
			* destroy_map()

			The driver is not used during grading. You can compare its output
			with the file expected-output-2.txt.

            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#include <stdlib.h>		// EXIT_FAILURE, EXIT_SUCCESS
#include <stdio.h>		// file I/O

#include "minesweeper-utils.h"

int main(void)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("Testcase %d\n", i);
		char filename[20];
		sprintf(filename, "in-2-%d.txt", i);
		FILE* pf = fopen(filename, "rt");
		if (!pf)
		{
			printf("file open error");
			return 0;
		}
		unsigned short int width, height;
		if (fscanf(pf, "%hu %hu ", &width, &height) != 2)
		{
			fclose(pf);
			return EXIT_FAILURE;
		}
		Map* map = create_map(width, height);
		if (!map)
		{
			fclose(pf);
			return EXIT_FAILURE;
		}
		for (unsigned short int r = 0; r < height; ++r)
		{
			for (unsigned short int c = 0; c < width; ++c)
			{
				char state;
				if (fscanf(pf, "%c", &state) != 1)
				{
					destroy_map(map);
					map = NULL;
					fclose(pf);
					return EXIT_FAILURE;
				}
				int is_visible = fgetc(pf);
				if (is_visible == EOF)
				{
					destroy_map(map);
					map = NULL;
					fclose(pf);
					return EXIT_FAILURE;
				}
				set_tile(map, c, r, (state == '9') ? BOMB : (char)state, is_visible != '0');
			}
		}
		print_map(map);
		destroy_map(map);
		map = NULL;
		fclose(pf);
	}
	return EXIT_SUCCESS;
}
