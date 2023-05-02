/*!
@file       test-1-allocate_and_destroy.c
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 9
@date       20/11/2020
@brief      This test driver tests implementation of the following functions:
			* create_map()
			* set_tile()
			* destroy_map()

			The driver is not used during grading. You can compare its output
			with the file expected-output-1.txt.

            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#include <stdlib.h>		// srand(), rand()
#include <stdlib.h>		// EXIT_FAILURE, EXIT_SUCCESS
#include <stdio.h>		// file I/O
#include <time.h>		// time()

#include "minesweeper-utils.h"

int main(void)
{
	// Run 1000 tests
	const int TEST_NUM = 1000;
	// Run 100 Random Access Per Test
	const int TEST_ACCESS_NUM = 1000;

	const unsigned short int MAX_WIDTH = 100;
	const unsigned short int MAX_HEIGHT = 100;

	/*
		Use the current time as seed to generate a different random sequence
		every time this code runs.
	*/
	srand((unsigned int)time(NULL));
	for (int i = 0; i < TEST_NUM; ++i)
	{
		const unsigned short int width =
			(unsigned short int)(rand() % MAX_WIDTH + 1);
		const unsigned short int height =
			(unsigned short int)(rand() % MAX_HEIGHT + 1);
		Map* map = create_map(width, height);
		if (!map)
		{
			return EXIT_FAILURE;
		}
		for (int j = 0; j < TEST_ACCESS_NUM; ++j)
		{
			const unsigned short int c = (unsigned short int)(rand() % width);
			const unsigned short int r = (unsigned short int)(rand() % height);
			set_tile(map, c, r, '0', true);
		}
		destroy_map(map);
		map = NULL;
	}
	printf("Success\n");
	return EXIT_SUCCESS;
}
