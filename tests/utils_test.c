#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include "../include/utils.h"

Test(utils, get_file_extension_test)
{
    cr_assert_str_eq(get_file_extension(""), "");
    cr_assert_str_eq(get_file_extension("file"), "");
    cr_assert_str_eq(get_file_extension("file.txt"), "txt");
    cr_assert_str_eq(get_file_extension("archive.tar.gz"), "gz");
    cr_assert_str_eq(get_file_extension(".hiddenfile"), "");
    cr_assert_str_eq(get_file_extension("file."), "");
    cr_assert_str_eq(get_file_extension("/path/to/file.pdf"), "pdf");
    cr_assert_str_eq(get_file_extension("/path/to/file"), "");
    cr_assert_str_eq(get_file_extension("/path/to/file.archive.tar.gz"), "gz");
    cr_assert_str_eq(get_file_extension("/path/to/.hiddenfile"), "");
    
}