#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 65536

#include <stdlib.h>
#include "errors.h"

typedef struct Entry
{
    char *key;
    unsigned int code;
    struct Entry *next;
} Entry;

typedef struct HashTable
{
    Entry *entries[TABLE_SIZE];
} HashTable;

unsigned int hash(const char *key);
HashTable *initialize_table();
int search_table(HashTable *table, const char *key);
void insert_table(HashTable *table, const char *key, unsigned int code);

#endif