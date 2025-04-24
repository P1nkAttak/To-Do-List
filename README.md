# Software Engineering Project 1 - Assignment 3
Senan O'Connor & Benjamin Power

# Design Choices
## Loading a Board from a File

## Editing Lists & Items
To edit the board or a list, The user enters the respective option, bringing up the menu for changing the lists or items.

1. When they want to edit the name of a list or item, the user enters the name, and the program searches through the linked list. When found, the user simply overwrites the old name with the new one.

2. When adding a new list or item, the user enters a name & the program creates a new node to add it on to the start of the list or board.

3. When deleting a list or item, the user enters the name, and the program searches through the board or list. When found, it passes the previous node, the current node, and the starting node of the list to the function. It checks where in the list the node is (the start, end or centre) and adjusts the pointers of the previous pointer appropriately.


## Saving a Board to a File


## ASCII Art




# Repository
https://csgitlab.ucd.ie/sep_3/assignment-3
