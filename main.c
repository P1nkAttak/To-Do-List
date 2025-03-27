/*
 * main.c
 *
 *  Created on: 26 Mar 2025
 *      Author: Senan O'Connor & Benjamin Power
 */

#include <stdio.h>
#include <string.h>
#include "kanban_board.h"

int main(void)
{
	int choice;

	printf("Menu:\n\t1. Display board\n\t2. Load board from a file\n\t3. Edit List\n\t");
	printf("4. Edit Board\n\t5. Save board to a file\n\t6. Quit\n");
	fflush(stdout);

	printf("Enter your choice (1 - 6)");
	fflush(stdout);
	scanf("%d", &choice);
}
