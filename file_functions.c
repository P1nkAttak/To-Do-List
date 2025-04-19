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
 * (INTERNAL)
 * This function reads a single line from a file and writes it to the given board
 *
 * ARGS:
 * board_ptr: A headPtr that the line will be read into
 * read_from: The file to read from
 *
 * RETURNS:
 * A bool specifying whether anything was read
 */
static bool ReadLine(headPtr board_ptr, FILE *read_from)
{
	char temp_string[MAX_LEN];
	int temp_string_index = 0;
	bool reading_board_name = true;
	bool is_first_item = true;
	itemPtr previous_item;

	while (!feof(read_from))
	{
		char read_char = fgetc(read_from);

		// Check an actual character was read
		if (read_char == EOF)
		{
			return false;
		}

		// Newline, so we are finished with this board
		if (read_char == '\n')
		{
			temp_string[temp_string_index] = '\0';
			temp_string_index = 0;

			// We are reading the board name and not an item
			if (reading_board_name)
			{
				strcpy(board_ptr->element, temp_string);
				board_ptr->next_head = NULL;
				board_ptr->next_item = NULL;
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
					board_ptr->next_item = new_item;
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
				strcpy(board_ptr->element, temp_string);
				board_ptr->next_head = NULL;
				board_ptr->next_item = NULL;
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
					board_ptr->next_item = new_item;
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

	return true;
}

/*
 * (INTERNAL)
 * This function writes a single word to a file
 * It does not write the null terminator
 *
 * ARGS:
 * to_write: The string to write
 * write_to: The file to write to
 *
 */
static void WriteWord(char *to_write, FILE *write_to)
{
	for (int i = 0; i < MAX_LEN; i++)
	{
		char this_char = to_write[i];

		// End at the null terminator
		if (this_char == '\0')
		{
			return;
		}

		// Else write the character
		fputc(this_char, write_to);
	}
}

/*
 * (INTERNAL)
 * This function writes an entire board to the given file
 *
 * ARGS:
 * board_ptr: The board to write
 * write_to: The file to write to
 */
static void WriteLine(headPtr board_ptr, FILE *write_to)
{
	// First write the board name
	WriteWord(board_ptr->element, write_to);

	// Now loop through every item
	itemPtr this_item = board_ptr->next_item;

	while (this_item != NULL)
	{
		// Write the delimiter
		fputc('|', write_to);

		// Write the item name
		WriteWord(this_item->element, write_to);

		// Proceed to next word
		this_item = this_item->next_item;
	}

	// Finally, write the newline character
	fputc('\n', write_to);
}

/*
 * This function saves a linked list board to the specified file.
 *
 * ARGS:
 * first_board: The first board of the linked list
 */
void SaveToFile(headPtr first_board)
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
	opened_file = fopen(file_name, "w");

	if (opened_file == NULL)
	{
		perror("Could not open/create the specified file");
		fflush(stdout);
		return;
	}

	// Loop through every board
	headPtr curr_board = first_board;

	while (curr_board != NULL)
	{
		WriteLine(curr_board, opened_file);
		curr_board = curr_board->next_head;
	}

	// Close the file
	fclose(opened_file);
}

/*
 * This function reads a linked list board from the specified file.
 *
 * ARGS:
 * board_ptr: A pointer to the pointer of the first board of the linked list
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
	// We start by reading the first board separately
	headPtr first_board_ptr = malloc(sizeof(board));
	ReadLine(first_board_ptr, opened_file);

	// Now we loop through the rest of the file
	headPtr last_board_ptr = first_board_ptr;

	while(!feof(opened_file))
	{
		headPtr this_board = malloc(sizeof(board));
		bool anything_read = ReadLine(this_board, opened_file);

		if (!anything_read)
		{
			free(this_board);
			break;
		}
		else
		{
			// Link the new board
			last_board_ptr->next_head = this_board;
			last_board_ptr = this_board;
		}
	}

	// Close the file and update the linked list pointer
	fclose(opened_file);
	*board_ptr = first_board_ptr;
}
