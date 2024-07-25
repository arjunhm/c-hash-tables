#include <stdbool.h>

typedef struct Item {
    char *key;
    int value;
} Item;

Item *alloc_item(char *key, int value);
void free_item(Item *item);
void print_item(Item *item);

typedef struct Node {
    Item *item;
    struct Node *next;
} Node;

Node *alloc_node(Item *item);
void print_node(Node *n);
void free_node(Node *n);

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

LinkedList *alloc_ll();
void ll_insert(LinkedList *ll, Node *n);
bool ll_delete(LinkedList *ll, char *key);
Item *ll_search(LinkedList *ll, char *key);
void print_ll(LinkedList *ll);
void free_ll(LinkedList *ll);
void ll_test();

typedef struct Table {
    int size;
    LinkedList *buckets;
} Table;

Table *alloc_table(int size);
void print_table(Table *t);
void free_table(Table *t);
int hash(Table *t, char *key);
bool table_insert(Table *t, Item *item);
bool table_delete(Table *t, char *key);
Item *table_search(Table *t, char *key);
void table_test();
