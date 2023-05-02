/*!
@file       minesweeper-utils.c
@author     Timothy Lee (timothykexin.lee@digipen.edu.sg)
@course     RSE 1201
@section    Assignment 11
@Assignment Dynamic Memory Allocation
@date       02/12/2021
@brief      This file contains definitions of various functions that utilizes structures and
            2D arrays to create a minewsweeper game. During a game the player reveals tiles 
            one by one. The player wins the game when they reveal all the tiles without bombs, 
            and loses when a bomb is revealed. In some implementations an empty tile indicates 
            that the tile has not been revealed yet.

*//*________________________________________________________________________________________*/
#include "minesweeper-utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char state;
    bool is_visible;
} Tile;
typedef Tile* Row;

struct Map{
    unsigned short int width;
    unsigned short int height;
    Row* grid;
};

/*!
@brief  This function allocates the map with a dynamic array of height pointers to dynamic
        arrays (Row objects) of width count of Tile objects.

@param  map is a pointer to a struct
        i is of type int
        
@return map
*//*_______________________________________________________________________________________*/
Map* create_map(unsigned short int width, unsigned short int height) {
	Map *map = malloc(height * sizeof(Row) * width);
	(*map).width = width;
	(*map).height = height;
	(*map).grid = malloc(height * sizeof(Row));
	for(int i = 0; i < height; i++) {
		(*map).grid[i] = malloc(width * sizeof(Tile));
	}
	return map;
}

/*!
@brief  This function deallocates all the memory allocated for the map.

@param  i is of type int
        
@return nothing
*//*_______________________________________________________________________________________*/
void destroy_map(Map* map) {
	for(int i = 0; i < (*map).height; i++) {
		free((*map).grid[i]);
	}
	free((*map).grid);
	free(map);	
}

/*!
@brief  This function sets the initial state of a tile for testing purposes by assigning
        struct grid with the state and visiblity. State represents either an ASCII code of 
        a digit with the number of bombs adjacent to the tile, or 'X' indicating the bomb 
        on the tile itself.  is_visible data member indicates whether the tile has been 
        revealed (true) or remains hidden (false).

@param  Function parameters to perform tasks for this function.
        
@return nothing
*//*_______________________________________________________________________________________*/
void set_tile(Map* map, unsigned short int column, unsigned short int row,
	          char state, bool is_visible) {
	(*map).grid[row][column].state = state;
	(*map).grid[row][column].is_visible = is_visible;
}

/*!
@brief  This function prints the tiles in row by row.

@param  col, row are of type int.
        
@return nothing
*//*_______________________________________________________________________________________*/
void print_map(Map const* map) {
	printf(" ");
	for(int col = 0; col < (*map).width; col++) {
		printf(" %d", col);
	}
	printf("\n");
	for(int row = 0; row < (*map).height; row++) {
		printf("%d|", row);
		for(int col = 0; col < (*map).width; col++) {
			if((*map).grid[row][col].is_visible) {
				printf("%c|", (*map).grid[row][col].state);
			} else {
				printf(" |");
			}
		}
		printf("\n");
	}
}

/*!
@brief  This function takes in a map that has been allocated and fills it with values for 
        each tile.

@param  i, j, x, y are of type int
        bombcnt is of type char 
        
@return nothing
*//*_______________________________________________________________________________________*/
void initialize_map(Map* map, float probability) {
	char bombcnt = '0';
	for(int i = 0; i < (*map).height; i++) {
		for(int j = 0; j < (*map).width; j++) {
			(*map).grid[i][j].is_visible = false;
			if(rand()%100 >= probability * 100) {
				(*map).grid[i][j].state = BOMB;
			} else {
				(*map).grid[i][j].state = '0';
			}
		}
	}
	for(int i = 0; i < (*map).height; i++) {
		for(int j = 0; j < (*map).width; j++) {
			if((*map).grid[i][j].state != BOMB) {
				for(int x = i - 1; x <= i + 1; x++) {
					if(x >= 0 && x < (*map).height) {
						for(int y = j - 1; y <= j + 1; y++) {
							if(y >= 0 && y < (*map).width) {
								if((*map).grid[x][y].state == BOMB) {
									(int)bombcnt++;
								}
							}
						}
					}
				}
				(*map).grid[i][j].state = bombcnt;
				bombcnt = '0';
			}
		}
	}
}

/*!
@brief  This function sets all tiles of a map as visible. 

@param  i, j is of type int
        
@return nothing
*//*_______________________________________________________________________________________*/
void reveal_all_tiles(Map* map) {
	for(int i = 0; i < (*map).height; i++) {
		for(int j = 0; j < (*map).width; j++) {
			(*map).grid[i][j].is_visible = true;
		}
	}
}

/*!
@brief  This function n tests whether all non-bomb tiles have been revealed. It returns true 
        if and only if all non-bomb tiles are visible (bomb tiles can be visible or not); 
        otherwise, it returns false.

@param  i, j are of type int
        
@return boolean expression, true or false
*//*_______________________________________________________________________________________*/
bool all_empty_tiles_visible(Map const* map) {
	for(int i = 0; i < (*map).height; i++) {
		for(int j = 0; j < (*map).width; j++) {
			if((*map).grid[i][j].state != BOMB) {
				if((*map).grid[i][j].is_visible == false) {
					return false;
				}
			}
		}
	}
	return true;
}

/*!
@brief  This function reveals the tile at the specified column and row (both indexed from 0). 
        If the tile contains a bomb, the function returns true ; otherwise, it returns false.

@param  Function parameters to perform tasks for this function.
        
@return boolean expression, true or false
*//*_______________________________________________________________________________________*/
bool is_bomb_tile(Map* map, unsigned short int column, unsigned short int row) {
	if(column < (*map).width && row < (*map).height) {
		(*map).grid[row][column].is_visible = true;
		if((*map).grid[row][column].state == BOMB) {
			return true;
		} else {
			return false;
		}
	} else {
		printf("Error: wrong column or row specified.\n");
		return false;
	}
}
