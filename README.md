# Run the code:
- mkdir build
- cd build
- cmake ..
- make
- ./manage_library


## for windows:
- make
- manage_library.exe


## Overview

This C++ program manages items in a library database. 
It provides functionalities to check availability, update status, and search for books and journals.

## Usage
1) itemExists(filename, itemName): Checks if an item exists and is available.

2) updateItemStatus(filename, itemName): Updates the status of an item.

3) searchBooksByTitle(filename, userRole, userName): Searches for books by title.

4) searchJournals(filename, userRole, userName): Searches for journals.

## Classes and Functions
ItemManagement Class

- itemExists: Checks if an item exists and is available.
- updateItemStatus: Updates the status of an item.
- toLowercase: Converts a string to lowercase.
- getRandomIndex: Generates random indexes.
- searchBooksByTitle: Searches for books by title.
- searchJournals: Searches for journals.
## Compilation

Ensure you have a C++ compiler installed.

1) Use g++ ItemManagement.cpp -o ItemManagement to compile.
2) Run with ./ItemManagement.
3) Please refer to comments in "ItemManagement.cpp" for more details.

