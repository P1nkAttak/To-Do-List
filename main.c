#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Kanban_Board.h"
#include "file_functions.h"

int main(void)
{
	int choice = 0;
	char list_name[MAX_LEN];
	headPtr sPtr = NULL;

	while (choice != 6)
	{
		printf("Menu:\n\t1. Display board\n\t2. Load board from a file\n\t3. Edit List\n\t");
		printf("4. Edit Board\n\t5. Save board to a file\n\t6. Quit\n");
		fflush(stdout);

		printf("Enter your choice (1 - 6)\n");
		fflush(stdout);
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			displayBoard(sPtr);
			break;
		case 2:
			ReadFromFile(&sPtr);
			break;
		case 3:
			printf("Enter name of list to edit\n");
			fflush(stdout);
			scanf("%s", list_name);

			editList(sPtr, list_name);
			break;
		case 4:
			editBoard(sPtr);
			break;
		case 5:
			printf("saveBoard()\n");
			fflush(stdout);
			break;
		case 6:
			break;
		default:
			printf("Invalid Input. Please re-enter option\n");
			fflush(stdout);
			break;
		}
	}
}

