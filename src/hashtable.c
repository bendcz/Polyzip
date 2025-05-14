#include "../include/hashtable.h"

unsigned int hash(const char *key)
{
    unsigned long int value = 0;
    
    for (int i = 0; key[i] != '\0'; i++)
    {
        value = value * 37 + key[i];
    }
    
    return value % TABLE_SIZE;
}

HashTable *initialize_table()
{
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));

    if (table == NULL)
    {
        print_error_message("initialize_table", ERROR_MEMORY_ALLOCATION);
        return NULL;
    }

    for (int i = 0; i != TABLE_SIZE; i++)
    {
        table->entries[i] = NULL;
    }

    for (int i = 0; i != 256; i++)
    {
        char *key = (char *) malloc(2);

        if (key == NULL)
        {
            print_error_message("initialize_table", ERROR_MEMORY_ALLOCATION);
            return NULL;
        }

        key[0] = (char) i;
        key[1] = '\0';

        unsigned int index = hash(key);

        Entry *entry = (Entry *) malloc(sizeof(Entry));

        if (entry == NULL)
        {
            print_error_message("initialize_table", ERROR_MEMORY_ALLOCATION);
            return NULL;
        }

        entry->key = key;
        entry->code = i;
        entry->next = table->entries[index];
        table->entries[index] = entry;
    }

    return table;
}

int search_table(HashTable *table, const char *key)
{
    return EXIT_SUCCESS;
}

void insert_table(HashTable *table, const char *key, unsigned int code)
{

}

