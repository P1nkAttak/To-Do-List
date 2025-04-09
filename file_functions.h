/*
 * Written: 27/03/25
 * Author: Ben Power
 * Description: Function prototypes for reading from/writing to files
 */


#ifndef _GUARD_FF // Protect against repeat/recursive inclusions
#define _GUARD_FF

#include "kanban_board.h" // Needed to define the types for our linked list

void SaveToFile();
void ReadFromFile(headPtr *board_ptr);

#endif
