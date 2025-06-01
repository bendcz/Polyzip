#include "../include/hashtable.h"

HashTable *initialize_table()
{
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));

    if (table == NULL)
    {
        print_error_message("initialize_table", ERROR_MEMORY_ALLOCATION);
        return NULL;
    }

    table->capacity = CAPACITY;
    table->length = 0;
    table->entries = (Entry *) calloc(CAPACITY, sizeof(Entry));

    if (table->entries == NULL)
    {
        free(table);
        print_error_message("initialize_table", ERROR_MEMORY_ALLOCATION);
    }

    return table;
}

void free_table(HashTable *table)
{
    if (table == NULL)
    {
        return;
    }
    
    for (size_t i = 0; i != table->capacity; i++)
    {
        free((char *) table->entries[i].key);
    }

    free(table->entries);
    free(table);
}

unsigned char *hash_key(const char *key)
{
    if (key == NULL)
    {
        print_error_message("hash", ERROR_MEMORY_ALLOCATION);
        return NULL;
    }

    // Source: https://wiki.openssl.org/index.php/EVP_Message_Digests
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

	if (mdctx == NULL)
    {
        //handleErrors();
        return NULL;
    }
		
	if (EVP_DigestInit_ex(mdctx, EVP_sha3_512(), NULL) != 1)
    {
        //handleErrors();
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }		

	if (EVP_DigestUpdate(mdctx, key, strlen(key)) != 1)
    {
        //handleErrors();
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    unsigned char *digest =  (unsigned char *) OPENSSL_malloc(EVP_MD_size(EVP_sha3_512()));

	if(digest == NULL)
    {
        //handleErrors();
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    unsigned int s = 512;
	if(EVP_DigestFinal_ex(mdctx, digest, &s) != 1)
    {
        //handleErrors();
        OPENSSL_free(digest);
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
		
	EVP_MD_CTX_free(mdctx);

    return digest;
}

unsigned int hash_to_index(const unsigned char *digest)
{
    unsigned int hash_value = 0;

    for (int i = 0; i < 512; i++)
    {
        hash_value = (hash_value << 8) | digest[i];
    }

    return hash_value % CAPACITY;
}

int find_by_key(HashTable *table, const char *key)
{
    unsigned char *hash = hash_key(key);
    unsigned int index = hash_to_index(hash);

    while (table->entries[index].key != NULL)
    {
        if (strcmp(key, table->entries[index].key) == 0)
        {
            return table->entries[index].value;
        }

        index += 1;

        if (index >= table->capacity)
        {
            index = 0;
        }
    }

    return -1;
}

const char *add_to_table(HashTable *table, const char *key, int value)
{
    if (table == NULL || key == NULL)
    {
        print_error_message("add_to_table", ERROR_MEMORY_ALLOCATION);
        return NULL;
    }

    int existing_value = find_by_key(table, key);
    unsigned char *hash = hash_key(key);
    unsigned int index = hash_to_index(hash);

    if (existing_value != -1)
    {
        table->entries[index].value = value;
        table->length += 1;
        OPENSSL_free(hash);
        return key;
    }

    if (table->length >= table->capacity)
    {
        print_error_message("add_to_table", -1);
        return NULL;
    }

    char *key_copy = strdup(key);

    table->entries[index].key = key_copy;
    table->entries[index].value = value;
    table->length += 1;

    OPENSSL_free(hash);

    return key_copy;
}

const char *find_by_value(HashTable *table, int value)
{
    for (size_t i = 0; i < table->capacity; i++)
    {
        if (table->entries[i].key != NULL && table->entries[i].value == value)
        {
            return table->entries[i].key;
        }
    }

    return NULL;
}