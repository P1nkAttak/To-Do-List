/*
 * Written: 09/04/25
 * Author: Ben Power
 * Description: Function definitions for the output.h header
 */

#include <stdio.h>
#include <stdbool.h>
#include "Kanban_Board.h"
#include "output.h"

void displayBoard(headPtr first_board)
{
	headPtr this_board = first_board;

	// Exit early if the board is empty
	if (this_board == NULL)
	{
		printf("The board is empty.\n");
		fflush(stdout);
		return;
	}

	// Loop through every board
	do
	{
		printf("%s:\n", this_board->element); // Print the name

		// Print the board's items
		if (this_board->next_item == NULL)
		{
			printf("  This board is empty...\n");
		}
		else
		{
			itemPtr this_item = this_board->next_item;

			// Loop through the items
			do
			{
				printf("  - %s\n", this_item->element);

				// Prepare the next item
				this_item = this_item->next_item;
			}
			while (this_item != NULL);
		}

		// Prepare the next board
		this_board = this_board->next_head;
	}
	while (this_board != NULL);
	fflush(stdout);
}
