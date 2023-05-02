/*!
@file       test-3-initialize.c
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 9
@date       20/11/2020
@brief      This test driver tests implementation of the following functions:
			* create_map()
			* initialize_map()
			* reveal_all_tiles()
			* destroy_map()

			The driver is not used during grading. You can compare its output
			with the file expected-output-3.txt.

            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#include <stdlib.h>		// srand(), rand()
#include <stdio.h>		// file I/O

#include "minesweeper-utils.h"

void test(
	unsigned short int width,
	unsigned short int height,
	float probability
)
{
	Map* map = create_map(width, height);
	if (!map)
	{
		return;
	}
	initialize_map(map, probability);
	reveal_all_tiles(map);
	print_map(map);
	destroy_map(map);
}

int main(void)
{
	srand(1);
	printf("Testcase 0\n");
	test(9, 7, 0.3368f);
	printf("Testcase 1\n");
	test(4, 1, 0.415f);
	printf("Testcase 2\n");
	test(10, 10, 0.2495f);
	printf("Testcase 3\n");
	test(10, 8, 0.3896f);
	printf("Testcase 4\n");
	test(8, 8, 0.2714f);
	printf("Testcase 5\n");
	test(2, 10, 0.0f);
}
