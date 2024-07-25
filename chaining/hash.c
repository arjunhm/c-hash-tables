#include "hash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 * ITEM
 *
 */

Item *alloc_item(char *key, int value) {
    Item *i = malloc(sizeof(Item));
    i->key = malloc(strlen(key) + 1);
    strcpy(i->key, key);
    i->value = value;
    return i;
}

void free_item(Item *item) {
    free(item->key);
    free(item);
}

void print_item(Item *item) { printf("%s=%d\n", item->key, item->value); }

/*
 *
 * NODE
 *
 */

Node *alloc_node(Item *item) {
    Node *n = malloc(sizeof(Node));
    n->item = item;
    n->next = NULL;
    return n;
}

void print_node(Node *n) {
    printf("node=%p\n\t", n);
    print_item(n->item);
    printf("\tnext=%p\n", n->next);
}

void free_node(Node *n) {
    free_item(n->item);
    free(n);
}

/*
 *
 * LINKED LIST
 *
 */

LinkedList *alloc_ll() {
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->head = NULL;
    ll->size = 0;
    return ll;
}

void ll_insert(LinkedList *ll, Node *n) {
    if (ll->head == NULL) {
        ll->head = n;
        return;
    }

    Node *ptr = ll->head;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = n;
    ll->size++;
}

bool ll_delete(LinkedList *ll, char *key) {
    if (ll == NULL || ll->head == NULL)
        return false;

    // if head
    if (*ll->head->item->key == *key) {
        ll->head = ll->head->next;
        ll->size--;
        return true;
    }

    Node *ptr = ll->head;
    Node *prev = ll->head;

    while (ptr) {
        if (*ptr->item->key == *key) {
            prev->next = ptr->next;
            free_item(ptr->item);
            ll->size--;
            return true;
        }
        prev = ptr;
        ptr = ptr->next;
    }

    return false;
}

Item *ll_search(LinkedList *ll, char *key) {
    if (ll == NULL || ll->head == NULL)
        return NULL;

    Node *ptr = ll->head;
    while (ptr) {
        if (*ptr->item->key == *key)
            return ptr->item;
        ptr = ptr->next;
    }
    return NULL;
}

void print_ll(LinkedList *ll) {
    if (ll == NULL || ll->head == NULL)
        return;

    Node *ptr = ll->head;
    while (ptr) {
        print_node(ptr);
        ptr = ptr->next;
    }
}

void free_ll(LinkedList *ll) {
    if (ll == NULL)
        return;

    Node *ptr, *temp;
    ptr = ll->head;
    while (ptr != NULL) {
        temp = ptr;
        free_node(temp);
        ptr = ptr->next;
    }

    free(ptr);
    free(ll);
}

void ll_test() {
    LinkedList *ll = malloc(sizeof(LinkedList));
    Item *i;
    Node *n;

    for (int j = 0; j < 5; j++) {
        char c = (char)(97 + j);
        i = alloc_item(&c, j + 1);
        n = alloc_node(i);
        ll_insert(ll, n);
    }
    ll_delete(ll, (char *)'c');
    ll_delete(ll, (char *)'a');
    ll_delete(ll, (char *)'e');
    print_ll(ll);
}

/*
 *
 * TABLE
 *
 */

Table *alloc_table(int size) {
    Table *t = malloc(sizeof(Table));
    t->size = size;
    t->buckets = malloc(sizeof(LinkedList) * size);
    return t;
}

void print_table(Table *t) {
    for (int i = 0; i < t->size; i++) {
        printf("%d\n", i);
        LinkedList *b = &t->buckets[i];
        if (b != NULL)
            print_ll(b);
        printf("-------\n");
    }
}

void free_table(Table *t) {
    for (int i = 0; i < t->size; i++) {
        LinkedList *b = &t->buckets[i];
        if (b != NULL)
            free_ll(b);
    }
    free(t);
}

int hash(Table *t, char *key) {
    int sum = 0;
    char *p = key;
    while (*p != '\0')
        sum += *p++;
    return sum % t->size;
}

bool table_insert(Table *t, Item *item) {
    int idx = hash(t, item->key);
    Node *n = alloc_node(item);
    ll_insert(&t->buckets[idx], n);
    return true;
}

bool table_delete(Table *t, char *key) {
    int idx = hash(t, key);
    if (t->buckets[idx].head != NULL)
        return ll_delete(&t->buckets[idx], key);
    return false;
}

Item *table_search(Table *t, char *key) {
    int idx = hash(t, key);
    if (&t->buckets[idx] != NULL)
        return ll_search(&t->buckets[idx], key);
    return NULL;
}

void table_test() {
    Table *t = alloc_table(3);
    Item *item = malloc(sizeof(Item));
    for (int i = 0; i < 9; i++) {
        char c[2] = {(char)(97 + i), '\0'};
        item = alloc_item(c, i + 1);
        table_insert(t, item);
    }

    char *ch = "e";
    bool r = table_delete(t, ch);

    print_table(t);
    item = table_search(t, "f");
    print_item(item);
}
