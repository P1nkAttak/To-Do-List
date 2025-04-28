/*
 * Kanban_board.c
 *
 *  Created on: 1 Apr 2025
 *      Author: Senan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kanban_Board.h"

// Obtain and cleanse user string input
void getstring(char value[MAX_LEN])
{
	// Clear input buffer
	fgetc(stdin);

	// Scan string
	strcpy(value, "\0");
	fgets(value, MAX_LEN - 1, stdin);
	value[(strlen(value) - 1)] = '\0';

	// Ensure user input is valid
	while (strlen(value) < 1)
	{
		printf("Invalid Entry. Please Re-enter input\n");
		fflush(stdout);
		fgets(value, MAX_LEN - 1, stdin);
		value[strlen(value) - 1] = '\0';
	}

	//printf("\n%s %d\n", value, strlen(value));
	//fflush(stdout);
}

// Display Board
void printList(headPtr *sPtr)
{
	headPtr cPtr = *sPtr;
	itemPtr icPtr;

	// Check if list is empty
	if (cPtr == NULL)
	{
		printf("List is empty\n\n");
		fflush(stdout);
		return;
	}

	while (cPtr != NULL)
	{
		// Print heading of the List
		printf("\n%s:\n", cPtr->element);
	    fflush(stdout);

		// Check Items of list
	    if (cPtr->next_item == NULL)
	    {
	    	printf("No Items --> ");
	    	fflush(stdout);
	    }
	    else
	    {
			// Print items
	    	icPtr = cPtr->next_item;
	    	while (icPtr != NULL)
	    	{
	    	  	printf("\t%s\n", icPtr->element);
	    	  	fflush(stdout);
	    	  	icPtr = icPtr->next_item;
	    	}
	    }

		// Check if the board is finished
	  	if (cPtr->next_head == NULL)
	    {
	    	printf("\nEND OF BOARD\n\n");
	    	cPtr = NULL;
	    }
	    else
	    {
			// Move to next list
	    	cPtr = cPtr->next_head;
	    }
	}

    return;
}

// Function for editing a given list's elements
void editList(headPtr *sPtr, char heading[MAX_LEN])
{
	headPtr currPtr = *sPtr;
	itemPtr icurrPtr, iprevPtr = NULL;
	int option = 0;
	char item[MAX_LEN];

	// Find location of List to be edited
	while ((currPtr != NULL) && (strcmp(heading, currPtr->element) != 0))
	{
		currPtr = currPtr->next_head;
	}

	if (currPtr == NULL)
	{
		printf("List entry not found.\n");
		fflush(stdout);
	}
	else
	{
		while (option != 4)
		{
			// Re-initialise item
			strcpy(item, "\0");

			printf("Options\n1. Edit an item\n2. Add a new item\n3. Delete an item\n4. Return to main menu\n");
			fflush(stdout);
			scanf("%d", &option);

			switch (option)
			{
			case 1:
				// Edit an item name
				icurrPtr = currPtr->next_item;

				printf("Enter name of item to edit\n");
				fflush(stdout);
				getstring(item);

				// Find the node
				while ((icurrPtr != NULL) && (strcmp(item, icurrPtr->element) != 0))
				{
					icurrPtr = icurrPtr->next_item;
				}

				// Edit the name if found
				if (icurrPtr == NULL)
				{
					printf("Item not found\n");
					fflush(stdout);
				}
				else
				{
					editItemName(&icurrPtr);
				}
				break;

			case 2:
				// Add item at the start of the list
				printf("Enter name of item to add\n");
				fflush(stdout);
				getstring(item);

				addItem(&currPtr, item);
				break;

			case 3:

				icurrPtr = currPtr->next_item;
				iprevPtr = NULL;

				printf("Enter name of item to delete\n");
				fflush(stdout);
				getstring(item);

				// Find node
				while ((icurrPtr != NULL) && (strcmp(item, icurrPtr->element) != 0))
				{
					iprevPtr = icurrPtr;
					icurrPtr = icurrPtr->next_item;
				}

				// Delete item
				if (icurrPtr == NULL)
				{
					printf("Item not found\n");
					fflush(stdout);
				}
				else
				{
					deleteItem(&iprevPtr, &icurrPtr, &currPtr);
				}
				break;

			case 4:
				// Return to main menu
				break;

			default:
				printf("Invalid Entry\n");
				break;
			}
		}
	}
}

// Function for editing the name of an item
void editItemName(itemPtr *cPtr)
{
	char rename[MAX_LEN];
	char old_name[MAX_LEN];

	// Save old name
	strcpy(old_name, (*cPtr)->element);

	printf("Enter new name of list\n");
	fflush(stdout);
	getstring(rename);

	// Replace name
	strcpy((*cPtr)->element, rename);

	printf("%s is now %s\n", old_name, (*cPtr)->element);
}

// Function to add items to the list
void addItem(headPtr *cPtr, char value[MAX_LEN])
{
	// Create new node
	itemPtr newPtr;

	// Allocate memory for new item
	newPtr = (item *) malloc(sizeof(item));

	// Check if memory is available
	if (newPtr != NULL)
	{
		// Place value in node
		strcpy(newPtr->element, value);

		// If the item is the first item added
		if ((*cPtr)->next_item == NULL)
		{
			newPtr->next_item = NULL;
			(*cPtr)->next_item = newPtr;
		}
		else
		{
			// Link node
			newPtr->next_item = (*cPtr)->next_item;
			(*cPtr)->next_item = newPtr;
		}
	}
	else
	{
		printf( "%s not inserted. No memory available.\n", value);
	    fflush(stdout);
	}
	 return;
}

// Function to remove items from the list
void deleteItem(itemPtr *pPtr, itemPtr *cPtr, headPtr *lPtr)
{
	char deleted[MAX_LEN];

	// If item is only element of the list
	if ((*pPtr == NULL) && ((*cPtr)->next_item == NULL))
	{
		strcpy(deleted, (*cPtr)->element);
		// Free memory and clean dangling pointer
		free((*cPtr));
		*cPtr = NULL;
	}
	else
	{
		// If the item is at the end of the list
		if ((*cPtr)->next_item == NULL)
		{
			// Cut the list of at previous item
			(*pPtr)->next_item = NULL;
			strcpy(deleted, (*cPtr)->element);
			free((*cPtr));
			*cPtr = NULL;
		}
		// If the item is at the start of the list
		else if (*pPtr == NULL)
		{
			// Second item moved to first
			(*lPtr)->next_item = (*cPtr)->next_item;
			strcpy(deleted, (*cPtr)->element);
			free((*cPtr));
			*cPtr = NULL;
		}
		// If the item is anywhere else
		else
		{
			// Link previous item with item after the current one
			(*pPtr)->next_item = (*cPtr)->next_item;
			strcpy(deleted, (*cPtr)->element);
			free((*cPtr));
			*cPtr = NULL;
		}
	}
	printf("%s deleted\n", deleted);
}


// Function to edit the linked list of lists
void editBoard(headPtr *sPtr)
{
	int option = 0;
	char list_name[MAX_LEN];
	headPtr currPtr, prevPtr;

	while (option != 4)
	{
		strcpy(list_name, "\0");

		printf("Options\n1. Edit the name of a list\n2. Add a new list\n3. Delete a list\n4. Return to main menu\n");
		fflush(stdout);
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			if (*sPtr == NULL)
			{
				printf("List is empty\n");
				fflush(stdout);
				break;
			}

			printf("Enter name of list to edit\n");
			fflush(stdout);
			getstring(list_name);
			
			if (*sPtr == NULL)
			{
				printf("List is empty\n");
			}
			else
			{
				currPtr = *sPtr;
				prevPtr = NULL;

				// Find location of List to be edited
				while (currPtr != NULL && strcmp(currPtr->element, list_name) != 0)
				{
					prevPtr = currPtr;
					currPtr = currPtr->next_head;
				}

				if (currPtr == NULL)
				{
					printf("List entry not found.\n");
					fflush(stdout);
				}
				else
				{
					editListName(&currPtr);
				}
			}
			break;

		case 2:
			printf("Enter name of list to add\n");
			fflush(stdout);
			getstring(list_name);

			addList(sPtr, list_name);
			break;

		case 3:
			if (*sPtr == NULL)
			{
				printf("List is empty\n");
			}
			else
			{
				printf("Enter name of list to delete\n");
				fflush(stdout);
				getstring(list_name);

				currPtr = *sPtr;
				prevPtr = NULL;

				// Find location of List to be deleted
				while (currPtr->next_head != NULL && strcmp(currPtr->element, list_name) != 0)
				{
					prevPtr = currPtr;
					currPtr = currPtr->next_head;
				}

				if (currPtr->next_head == NULL && strcmp(currPtr->element, list_name) != 0)
				{
					printf("List entry not found.\n");
					fflush(stdout);
				}
				else
				{
					deleteList(&prevPtr, &currPtr, sPtr);
				}
			}
			break;

		case 4:
			break;

		default:
			printf("Invalid Entry\n");
			fflush(stdout);
			break;
		}
	}
	return;
}

// Function to edit the name of a list
void editListName(headPtr *cPtr)
{
	char rename[MAX_LEN];
	char old_name[MAX_LEN];

	strcpy(old_name, (*cPtr)->element);

	printf("Enter new name of list\n");
	fflush(stdout);
	getstring(rename);

	strcpy((*cPtr)->element, rename);

	printf("%s is now %s\n", old_name, (*cPtr)->element);
}

// Function to create a new list
void addList(headPtr *sPtr, char value[MAX_LEN])
{
	headPtr newPtr; /* create node */

    newPtr = (board *) malloc(sizeof(board));

    if (newPtr != NULL)
    {
        strcpy(newPtr->element, value); /* place value in node */

        /* insert new node at start*/
		newPtr->next_item = NULL;
        newPtr->next_head = *sPtr;
       	*sPtr = newPtr;
    }
    else
    {
        printf("%s not inserted. No memory available.\n", value);
        fflush(stdout);
    }

    //printList(*sPtr);
    return;
}

// Function to remove a list
void deleteList(headPtr *pPtr, headPtr *cPtr, headPtr *sPtr)
{
	char deleted[MAX_LEN];

	// If the list is the only element of the board
	if ((*pPtr == NULL) && ((*cPtr)->next_head == NULL))
	{
		strcpy(deleted, (*cPtr)->element);
		free((*cPtr));
		*cPtr = NULL;
	}
	else
	{
		// If the list is the last list
		if ((*cPtr)->next_head == NULL)
		{
			(*pPtr)->next_head = NULL;
			strcpy(deleted, (*cPtr)->element);
			free((*cPtr));
			*cPtr = NULL;
		}
		// If the list is the start of the board
		else if (*pPtr == NULL)
		{
			*sPtr = (*cPtr)->next_head;
			strcpy(deleted, (*cPtr)->element);
			free((*cPtr));
			*cPtr = NULL;
		}
		else
		{
			strcpy(deleted, (*cPtr)->element);
			(*pPtr)->next_head = (*cPtr)->next_head;
			free(cPtr);
			*cPtr = NULL;
		}
	}

	printf("%s deleted\n", deleted);
}
