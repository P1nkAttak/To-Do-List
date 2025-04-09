#ifndef _GUARD__KANBAN //This is needed; keep this
#define _GUARD__KANBAN

#define MAX_LEN 100

typedef struct item
{
	char element[MAX_LEN];
	struct item *next_item;
} item;

typedef struct board
{
	char element[MAX_LEN];
	struct item *next_item;
	struct board *next_head;
} board;

typedef board *headPtr;
typedef item *itemPtr;

void printList(headPtr *sPtr);
int isEmpty(headPtr *startptr);

void editList(headPtr *sPtr, char list_head[MAX_LEN]);
void editBoard(headPtr *sPtr);

void editItemName(itemPtr *cPtr);
void addItem(itemPtr *cPtr, char value[MAX_LEN]);
void deleteItem(itemPtr *pPtr, itemPtr *cPtr);
void editListName(headPtr *cPtr);
void addList(headPtr *sPtr, char value[MAX_LEN]);
void deleteList(headPtr *pPtr, headPtr *cPtr);

#endif
