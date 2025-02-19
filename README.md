# DLIST (Dynamic List in C)
Lightweight list implementation in C.

## Usage
You can look at examples inside test.c file

```c
#include "dynlist.h"

...

dlist integer_arr = DLIST_CREATE(int, 10); // Creates a dynamic array to store 10 integers

...

// To push elements to the array
DLIST_PUSH(&integer_arr, int, 5);
DLIST_PUSH(&integer_arr, int, 1);
DLIST_PUSH(&integer_arr, int, 9);
DLIST_PUSH(&integer_arr, int, 100);

...

// To push pointers to the array
int x = 10;
dlist pointer_arr = DLIST_CREATE(int*, 4);
DLIST_PUSH_PTR(&integer_arr, int*, &x);
DLIST_PUSH_PTR(&integer_arr, int*, &x);
DLIST_PUSH_PTR(&integer_arr, int*, &x);
DLIST_PUSH_PTR(&integer_arr, int*, &x);

...

// Access elements from the array
for (int i = 0; i < integer_arr.count; i++)
{
    int* data = DLIST_GET(&integer_arr, i);
    printf("%d\n", *data);
}

...

// Make sure to free the dlist memory regions after use
dlist integer_arr = DLIST_CREATE(int, 10); 

// Your operations
...

free_dlist(&integer_arr);

```