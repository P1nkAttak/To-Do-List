## Software Engineering Project 1 - Assignment 3
Senan O'Connor & Benjamin Power

## Design Choices
1. Loading a Board from a File

2. Editing Lists & Items:
To edit the board, The user enters 4 as the option, bringing up the menu for changing the lists.
When they want to edit the name of a list, the user enters the name, and the program searches through the linked list. When found, the user simply overwrites the old name with the new one.
When adding a new list, the user enters the new list name & the program creates a new node to add it on to the start of the linked list.
When deleting a list, the user enters the name, and the program searches through the linked list. When found, it passes the previous node, the current node, and the starting node of the list to the function. 

