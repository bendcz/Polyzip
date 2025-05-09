#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include "../include/rle.h"

Test(utils, get_file_extension_test)
{
    #ifdef _WIN32
    #elif __unix__
    #endif
}