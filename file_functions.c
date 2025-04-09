/*
 * Written: 27/03/25
 * Author: Ben Power
 * Description: Definitions for the prototypes declared in file_functions.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Kanban_Board.h"
#include "file_functions.h"

/*
 * This function saves a linked list board to the specified file.
 *
 * ARGS:
 * start_board: The first board of the linked list
 * file_name: A string; the name of the file to save the list to
 */
void SaveToFile()
{
}

/*
 * This function reads a linked list board from the specified file.
 *
 * ARGS:
 * file_name: A string; the name of the file to read the list from
 *
 * RETURNS:
 * A pointer to the first board of the newly created linked list
 */
void ReadFromFile(headPtr *board_ptr)
{
	getchar(); // Clears input stream

	// Read a file name
	printf("\nEnter a file name: ");
	fflush(stdout);
	char file_name[20];
	fgets(file_name, 20, stdin);

	// We need to sanitise the file name to remove the newline character
	for (int i = 0; i < 20; i++)
	{
		char this_char = file_name[i];
		if (this_char == '\n')
		{
			file_name[i] = '\0';
			break;
		}
	}

	// Attempt to find the file
	FILE *opened_file;
	opened_file = fopen(file_name, "r");

	if (opened_file == NULL)
	{
		perror("Could not find the specified file");
		fflush(stdout);
		return;
	}

	// We need to read the data from the file now
	// Names are separated by a | delimiter
	// The first name on a line is the board name, and the rest are item names
	// A newline character indicates the end of a board
	char temp_string[MAX_LEN];
	int temp_string_index = 0;

	// We start by reading the first board separately
	headPtr first_board_ptr = malloc(sizeof(board));

	bool reading_board_name = true;
	bool is_first_item = true;
	itemPtr previous_item;

	while (!feof(opened_file))
	{
		char read_char = fgetc(opened_file);

		// Newline, so we are finished with this board
		if (read_char == '\n')
		{
			temp_string[temp_string_index] = '\0';
			temp_string_index = 0;

			// We are reading the board name and not an item
			if (reading_board_name)
			{
				strcpy(first_board_ptr->element, temp_string);
				first_board_ptr->next_head = NULL;
				first_board_ptr->next_item = NULL;
				reading_board_name = false;
			}
			// We are reading an item
			else
			{
				itemPtr new_item = malloc(sizeof(item));
				strcpy(new_item->element, temp_string);
				new_item->next_item = NULL;
				// This is the first item, so we have to link it to the board
				if (is_first_item)
				{
					first_board_ptr->next_item = new_item;
					is_first_item = false;
				}
				// We have to link this item to the previous item
				else
				{
					previous_item->next_item = new_item;
				}

				// Update the previous item indicator
				previous_item = new_item;
			}
			break;
		}

		// Delimiter, so we are finished with this string
		if (read_char == '|')
		{
			temp_string[temp_string_index] = '\0';
			temp_string_index = 0;

			// We are reading the board name and not an item
			if (reading_board_name)
			{
				strcpy(first_board_ptr->element, temp_string);
				first_board_ptr->next_head = NULL;
				first_board_ptr->next_item = NULL;
				reading_board_name = false;
			}
			// We are reading an item
			else
			{
				itemPtr new_item = malloc(sizeof(item));
				strcpy(new_item->element, temp_string);
				new_item->next_item = NULL;

				// This is the first item, so we have to link it to the board
				if (is_first_item)
				{
					first_board_ptr->next_item = new_item;
					is_first_item = false;
				}
				// We have to link this item to the previous item
				else
				{
					previous_item->next_item = new_item;
				}

				// Update the previous item indicator
				previous_item = new_item;
			}
			continue;
		}

		// We are reading part of the string
		temp_string[temp_string_index++] = read_char;
	}

	// Close the file and update the linked list pointer
	fclose(opened_file);
	*board_ptr = first_board_ptr;
}
