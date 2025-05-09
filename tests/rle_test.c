#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <openssl/evp.h>
#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include "../include/rle.h"

#define BUFFER_SIZE 1024

void calculate_file_hash(const char *filePath, unsigned char *hash)
{
    FILE *file = fopen(filePath, "rb");

    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    const EVP_MD* checksumAlgorithm = EVP_sha3_512();
    EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
    unsigned char buffer[BUFFER_SIZE];
    int byte;
    unsigned char *digest = NULL;
    

    if (checksumAlgorithm == NULL || mdctx == NULL || EVP_DigestInit_ex(mdctx, checksumAlgorithm, NULL) != 1)
    {
        perror("/!\\ Error during file hash initialization.\n");
        exit(EXIT_FAILURE);
    }

    while ((byte = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        if (EVP_DigestUpdate(mdctx, buffer, byte) != 1)
        {
            perror("/!\\ Error during hash update.\n");
            exit(EXIT_FAILURE);
        }
    }

    int digestLength = EVP_MD_size(checksumAlgorithm);

	if ((digest = (unsigned char *)OPENSSL_malloc(digestLength)) == NULL)
    {
        perror("/!\\ Error during hash allocation.\n");
		exit(EXIT_FAILURE);
	}

	if (EVP_DigestFinal_ex(mdctx, digest, &digestLength) != 1)
    {
		OPENSSL_free(digest);
        // handle errro
	}

	for (int i = 0; i < digestLength; i++) {
		printf("%02x", digest[i]);
	}


    OPENSSL_free(digest);
    EVP_MD_CTX_destroy(mdctx);

    fclose(file);
}

int compare_file_content(const char *inputFunction(const char *, const char *), const char *inputPath,
                          const char *outputFunction(const char *, const char *), const char *outputPath)
{

    unsigned char hash1[512];
    unsigned char hash2[512];

    const char *firstResult = inputFunction(inputPath, outputPath);
    calculate_file_hash(firstResult, hash1);

    printf("firstResult: %s\n", firstResult);

    const char *secondResult = outputFunction(firstResult, inputPath);

    printf("secondResult: %s\n", secondResult);

    calculate_file_hash(secondResult, hash2);

    return memcmp(hash1, hash2, 512);
}

Test(rle, rle_test)
{
    #ifdef _WIN32
    #elif __unix__
        cr_assert_eq(compare_file_content(compress_rle, "/home/user/Desktop/polyzip/tests/samples/rle/test.txt", decompress_rle, "/home/user/Desktop/polyzip/tests/samples/rle"), 0);
    #endif
}