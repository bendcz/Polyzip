#include "../include/lzw.h"

char *dictionary[4096];

int compress_lzw(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "lzw");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("compress_lzw", ERROR_FILE_ALLOCATION);
    }

    HashTable *table = initialize_table();

    for (int i = 0; i != 256; i++)
    {
        char key[2];
        key[0] = (char) i;
        key[1] = '\0';

        add_to_table(table, key, i);
    }

    char current_sequence[1024] = "";
    int current_code = 256; 
    int c;

    while ((c = fgetc(files->inputFile)) != EOF)
    {
        char next_char = (char)c;
        char new_sequence[1024];
        snprintf(new_sequence, sizeof(new_sequence), "%s%c", current_sequence, next_char);
        
        if (find_by_key(table, new_sequence) != -1)
        {
            strcpy(current_sequence, new_sequence);
        }
        else
        {
            int code = find_by_key(table, current_sequence);
            fwrite(&code, sizeof(int), 1, files->outputFile);
            add_to_table(table, new_sequence, current_code++);
            current_sequence[0] = next_char;
            current_sequence[1] = '\0';
        }
    }

    if (strlen(current_sequence) > 0)
    {
        int code = find_by_key(table, current_sequence);
        fwrite(&code, sizeof(int), 1, files->outputFile);
    }

    free_table(table);
    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);

    return EXIT_SUCCESS;
}

int decompress_lzw(const char *inputPath, const char *outputPath)
{
    struct Files *files = get_files(inputPath, outputPath, "txt2");

    if (files == NULL || files->inputFile == NULL || files->outputFile == NULL)
    {
        return print_error_message("decompress_lzw", ERROR_FILE_ALLOCATION);
    }

    for (int i = 0; i < 256; i++)
    {
        char *entry = malloc(2);

        if (entry == NULL)
        {
            fclose(files->inputFile);
            fclose(files->outputFile);
            free(files);
            return print_error_message("decompress_lzw", ERROR_MEMORY_ALLOCATION);
        }

        entry[0] = (char) i;
        entry[1] = '\0';
        dictionary[i] = entry;
    }

    int current_code = 256;
    int prev_code;

    if (fread(&prev_code, sizeof(int), 1, files->inputFile) != 1)
    {
        print_error_message("decompress_lzw", ERROR_FILE_READ);
        fclose(files->inputFile);
        fclose(files->outputFile);
        free(files);
        return EXIT_FAILURE;
    }

    fputs(dictionary[prev_code], files->outputFile);
    char *prev_str = dictionary[prev_code];
    int code;

    while (fread(&code, sizeof(int), 1, files->inputFile) == 1)
    {
        char *entry;
        
        if (dictionary[code])
        {
            entry = dictionary[code];
        }
        else
        {
            size_t len = strlen(prev_str);
            entry = (char *) malloc(len + 2);

            if (entry == NULL)
            {
                fclose(files->inputFile);
                fclose(files->outputFile);
                free(files);
                return print_error_message("decompress_lzw", ERROR_MEMORY_ALLOCATION);
            }

            snprintf(entry, len + 2, "%s%c", prev_str, prev_str[0]);
            dictionary[code] = entry;
        }

        fputs(entry, files->outputFile);

        size_t len = strlen(prev_str) + 2;
        char *new_str = (char *) malloc(len);

        if (new_str == NULL)
        {
            fclose(files->inputFile);
            fclose(files->outputFile);
            free(files);
            return print_error_message("decompress_lzw", ERROR_MEMORY_ALLOCATION);
        }

        snprintf(new_str, len, "%s%c", prev_str, entry[0]);
        dictionary[current_code++] = new_str;

        prev_str = entry;
    }

    for (int i = 0; i < current_code; i++)
    {
        free(dictionary[i]);
    }

    fclose(files->inputFile);
    fclose(files->outputFile);
    free(files);
    
    return EXIT_SUCCESS;
}