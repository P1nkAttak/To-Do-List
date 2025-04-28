# Software Engineering Project 1 - Assignment 3
Senan O'Connor & Benjamin Power

# Design Choices
## Loading a Board from a File
Loading a board was somewhat difficult, since we can't directly save a linked list to a file as you can a variable or struct. Instead, I had to serialise the data. I decided to do this using delimiters and the newline character. Each line in the file represents a board, with the first item on the line being the board's name and the rest being the names of items. The end of the names is indicated by the '|' symbol. The load function then constructs a linked list based on these parameters.

Once a suitable file is found, the existing linked list is freed using a recursive free() function. This is done to avoid memory leaks, and it is done after a suitable file is found to avoid deleting a user's existing list prematurely.

## Editing Lists & Items
To edit the board or a list, The user enters the respective option, bringing up the menu for changing the lists or items.

1. When they want to edit the name of a list or item, the user enters the name, and the program searches through the linked list. When found, the user simply overwrites the old name with the new one.

2. When adding a new list or item, the user enters a name & the program creates a new node to add it on to the start of the list or board.

3. When deleting a list or item, the user enters the name, and the program searches through the board or list. When found, it passes the previous node, the current node, and the starting node of the list to the function. It checks where in the list the node is (the start, end or centre) and adjusts the pointers of the previous pointer appropriately.


## Saving a Board to a File
Saving the board was simple after creating the loading function. It is basically just the same serialisation as the load function, but in reverse. The name of each board/item is written to the file, with new item pointers being separated by '|' and new board pointers being separated by newlines. 


## ASCII Art - Ben Power
My ASCII art is of a galaxy. I chose this because I find space very fascinating to learn about.


# Repository
https://csgitlab.ucd.ie/sep_3/assignment-3
