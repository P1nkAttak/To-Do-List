/*
 * Written: 27/03/25
 * Author: Ben Power
 * Description: Contains the structs used for the kanban board
 */


#ifndef _GUARD_KB // Protect against repeat/recursive inclusions
#define _GUARD_KB

// An item within a board
typedef struct Item
{
	char Name[80];
	struct Item *Next_Item;
} Item;

// A board, to be filled with items
typedef struct Board
{
	char Name[80];
	struct Board *Next_Board;
	Item *First_Item;
} Board;

#endif
