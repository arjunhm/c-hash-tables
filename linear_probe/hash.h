#include <stdbool.h>

typedef struct Item {
    char *key;
    int value;
} Item;

typedef struct Table {
    int size;
    Item *items;
} Table;
