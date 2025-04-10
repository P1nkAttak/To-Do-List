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

void printList(headPtr *sPtr)
{
	headPtr cPtr = *sPtr;
	itemPtr icPtr;

	if (cPtr == NULL)
	{
		printf("List is empty\n\n");
		fflush(stdout);
		return;
	}

	while (cPtr != NULL)
	{
		printf("%s --> ", cPtr->element);
	    fflush(stdout);

	    if (cPtr->next_item == NULL)
	    {
	    	printf("No Items --> ");
	    	fflush(stdout);
	    }
	    else
	    {
	    	icPtr = cPtr->next_item;
	    	while (icPtr != NULL)
	    	{
	    	  	printf("%s --> ", icPtr->element);
	    	  	fflush(stdout);
	    	  	icPtr = icPtr->next_item;
	    	}
	    }

	    printf("NULL\n");
	    fflush(stdout);

	    if (cPtr->next_head == NULL)
	    {
	    	printf("\nEND OF LIST\n\n");
	    	cPtr = NULL;
	    }
	    else
	    {
	    	cPtr = cPtr->next_head;
	    }
	}

    return;
}


void editList(headPtr *sPtr, char heading[100])
{
	headPtr currPtr = *sPtr;
	itemPtr icurrPtr;
	int option = 0;
	char item[MAX_LEN];

	strcpy(item, "\0");

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
			printf("Options\n1. Edit an item\n2. Add a new item\n3. Delete an item\n4. Return to main menu\n");
			fflush(stdout);
			scanf("%d", &option);

			switch (option)
			{
			case 1:
				icurrPtr = currPtr->next_item;

				printf("Enter name of item to edit\n");
				fflush(stdout);
				scanf("%s", item);

				while ((icurrPtr != NULL) && (strcmp(item, icurrPtr->element) != 0))
				{
					icurrPtr = icurrPtr->next_item;
				}
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
				icurrPtr = currPtr->next_item;

				printf("Enter name of item to add\n");
				fflush(stdout);
				scanf("%s", item);

				addItem(&icurrPtr, item);

				break;
			case 3:
				//deleteItem();
				break;

			case 4:
				break;
			default:
				printf("Invalid Entry\n");
				break;
			}
		}
	}
}

void editItemName(itemPtr *cPtr)
{
	char rename[MAX_LEN];
	char old_name[MAX_LEN];

	strcpy(old_name, (*cPtr)->element);

	printf("Enter new name of list\n");
	fflush(stdout);
	scanf("%s", rename);

	strcpy((*cPtr)->element, rename);

	printf("%s is now %s\n", old_name, (*cPtr)->element);
}


void addItem(itemPtr *cPtr, char value[MAX_LEN])
{
	itemPtr newPtr; /* create node */
	itemPtr checkPtr;

	newPtr = (board *) malloc(sizeof(board));

	if (newPtr != NULL)
	{
		strcpy(newPtr->element, value); /* place value in node */

	    /* insert new node at start*/
	    newPtr->next_item = (*cPtr)->next_item;
	    (*cPtr)->next_item = newPtr;

	    printf("Start is %s of %d\n", (*cPtr)->element, strlen((*cPtr)->element));
	    fflush(stdout);

	    if ((*cPtr)->next_item != NULL)
	    {
	    	checkPtr = (*cPtr)->next_item;
	    	printf("Next is %s\n", checkPtr->element);
	    	fflush(stdout);
	    }
	}
	else
	{
		printf( "%s not inserted. No memory available.\n", value);
	    fflush(stdout);
	}

	 return;
}


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
			//getstring(list_name);
			scanf("%s", list_name);
			/*
			printf("\n%s %d\n", list_name, strlen(list_name));
			fflush(stdout);
			*/
			if (*sPtr == NULL || strlen((*sPtr)->element) == 0)
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
					printf("\n%s %d\n", currPtr->element, strlen(currPtr->element));// currPtr->element, strlen(currPtr->element));
					fflush(stdout);
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
			scanf("%s", list_name);

			addList(sPtr, list_name);

			break;

		case 3:
			printf("Enter name of list to delete\n");
			fflush(stdout);
			scanf("%s", list_name);

			if (*sPtr == NULL)
			{
				printf("List is empty");
			}
			else
			{
				currPtr = *sPtr;
				prevPtr = NULL;

				// Find location of List to be deleted
				while (currPtr->next_head != NULL && strcmp(currPtr->element, list_name) != 0)
				{
					printf("\n%s %d\n", currPtr->element, strlen(currPtr->element));
					fflush(stdout);
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
					deleteList(&prevPtr, &currPtr);
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

void editListName(headPtr *cPtr)
{
	char rename[MAX_LEN];
	char old_name[MAX_LEN];

	strcpy(old_name, (*cPtr)->element);

	printf("Enter new name of list\n");
	fflush(stdout);
	scanf("%s", rename);

	strcpy((*cPtr)->element, rename);

	printf("%s is now %s\n", old_name, (*cPtr)->element);
}


void addList(headPtr *sPtr, char value[100])
{
	headPtr newPtr; /* create node */
	headPtr checkPtr;

    newPtr = (board *) malloc(sizeof(board));

    if (newPtr != NULL)
    {
        strcpy(newPtr->element, value); /* place value in node */

        /* insert new node at start*/
        newPtr->next_head = *sPtr;
       	*sPtr = newPtr;

       	printf("Start is %s of %d\n", (*sPtr)->element, strlen((*sPtr)->element));
       	fflush(stdout);

       	if ((*sPtr)->next_head != NULL)
       	{
       		checkPtr = (*sPtr)->next_head;
       		printf("Next is %s\n", checkPtr->element);
       		fflush(stdout);
       	}
    }
    else
    {
        printf("%s not inserted. No memory available.\n", value);
        fflush(stdout);
    }

    //printList(*sPtr);
    return;
}

void deleteList(headPtr *pPtr, headPtr *cPtr)
{
	if (*pPtr == NULL)
	{
		strcpy((*cPtr)->element, "\0");
	}
	else
	{
		if ((*cPtr)->next_head == NULL)
		{
			(*pPtr)->next_head = NULL;
			free(cPtr);
		}
		else
		{
			(*pPtr)->next_head = (*cPtr)->next_head;
			free(cPtr);
		}
	}
}
