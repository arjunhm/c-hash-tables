#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_item(Item *item) { printf("%s=%d\n", item->key, item->value); }

void print_table(Table *t) {
    printf("----\n");
	for (int i = 0; i < t->size; i++)
        print_item(&t->items[i]);
    printf("----\n");
}

char *generate_word(int len) {

    if (len > 10)
        len = 10;

    int size = (rand() % len) + 1;
    char *word = malloc(sizeof(char) * size);
    if (!word)
        return NULL;

    char ch;
    for (int i = 0; i < size; i++) {
        ch = (rand() % 26) + 97;
        word[i] = ch;
    }
    return word;
}

int generate_int(int max) { return (rand() % max) + 1; }

Table *alloc_table(int size) {
    Table *t = calloc(1, sizeof(Table));
    if (!t) {
        return NULL;
	}

    t->size = size;
    t->items = calloc(1, sizeof(Item) * size);
    if (!t->items) {
		free(t);
        return NULL;
    }

    return t;
}

Item *alloc_item(char *key, int value) {
    Item *x = malloc(sizeof(Item));
    if (!x)
        return NULL;
    x->key = key;
    x->value = value;
    return x;
}

Item *generate_item() {
    Item *i = malloc(sizeof(Item));
    if (!i)
        return NULL;
    i->key = generate_word(6);
    i->value = generate_int(4);
    return i;
}

int hash(Table *t, Item *item) {
    
    int sum = 0;
    char *p = item->key;
    while (*p != '\0')
       sum += *p++;
        return sum % t->size;
    //return item->value % t->size;
}

bool linear_probe(Item *items, int size, Item *item, int idx) {
    int i = 0, c = 0;
    while (i < size) {
        idx = idx % size;
        if (items[idx].key == NULL) {
            items[idx].key = item->key;
            items[idx].value = item->value;
            //printf("%d collisions for %s\n", c, item->key);
            return true;
        }
        c++;
        idx++;
        i++;
    }
    return false;
}

void resize(Table *t) {
    int new_idx;
    int old_size = t->size;
    // update size
    t->size *= 2;

    // create new *items
    Item *new_items = calloc(1, sizeof(Item) * t->size);
    if (!new_items)
        return;

    // insert old items to new items
    for (int i = 0; i < old_size; i++) {
        Item *item = &t->items[i];
        new_idx = hash(t, item);
        linear_probe(new_items, t->size, item, new_idx);
    }

    // assign new items to table
	free(t->items);
    t->items = new_items;
}

bool insert(Table *t, Item *item) {
    int idx = hash(t, item);
    int i = 0;

    bool result = linear_probe(t->items, t->size, item, idx);
    if (result == false) {
        resize(t);
        insert(t, item);
    }
    return true;
}

void free_table(Table *t) {
	for (int i = 0; i < t->size; i++) 
		free(t->items[i].key);
	free(t->items);
	free(t); 
}

int main() {
    srand(time(NULL));
    Table *t = alloc_table(5);
    if (!t) {
        printf("failed");
        return 1;
    }
	Item *item;
    
    int n = 25;
    for (int i = 0; i < n; i++) {
    	item = generate_item();
        insert(t, item);
		free(item);
    }

    print_table(t);
    free_table(t);
    return 1;
}
