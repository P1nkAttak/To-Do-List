# Software Engineering Project 1 - Assignment 3
Senan O'Connor & Benjamin Power

# Design Choices
## Loading a Board from a File

## Editing Lists & Items
To edit the board, The user enters 4 as the option, bringing up the menu for changing the lists.

1. When they want to edit the name of a list, the user enters the name, and the program searches through the linked list. When found, the user simply overwrites the old name with the new one.

2. When adding a new list, the user enters the new list name & the program creates a new node to add it on to the start of the linked list.

3. When deleting a list, the user enters the name, and the program searches through the linked list. When found, it passes the previous node, the current node, and the starting node of the list to the function. It checks where in the list the node is (the start, end or centre) and adjusts the pointers of the previous pointer appropriately.


## Saving a Board to a File


## ASCII Art




# Repository
https://csgitlab.ucd.ie/sep_3/assignment-3
