#ifndef HASHTABLE_H
#define HASHTABLE_H

#define CAPACITY 4096

#include <stdbool.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include "errors.h"

typedef struct Entry
{
    const char *key;
    int value;
} Entry;

typedef struct HashTable
{
    Entry *entries;
    size_t capacity;
    size_t length;
} HashTable;

HashTable *initialize_table();
void free_table(HashTable *table);
unsigned char *hash_key(const char *key);
unsigned int hash_to_index(const unsigned char *digest);
int find_by_key(HashTable *table, const char *key);
const char *add_to_table(HashTable *table, const char *key, int value);
const char *find_by_value(HashTable *table, int value);

#endif