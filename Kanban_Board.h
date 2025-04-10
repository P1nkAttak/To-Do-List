#ifndef KANBAN_BOARD_H_
#define KANBAN_BOARD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef struct
{
	char element[MAX_LEN];
	struct item *next_item;
} item;

typedef struct
{
	char element[MAX_LEN];
	struct item *next_item;
	struct board *next_head;
} board;

typedef board *headPtr;
typedef item *itemPtr;

void printList(headPtr *sPtr);

void editList(headPtr *sPtr, char list_head[MAX_LEN]);
void editBoard(headPtr *sPtr);

void editItemName(itemPtr *cPtr);
void addItem(headPtr *cPtr, char value[MAX_LEN]);
void deleteItem(itemPtr *pPtr, itemPtr *cPtr, headPtr *lPtr);
void editListName(headPtr *cPtr);
void addList(headPtr *sPtr, char value[MAX_LEN]);
void deleteList(headPtr *pPtr, headPtr *cPtr, headPtr *sPtr);

#endif /* KANBAN_BOARD_H_ */
