#include "criterion/criterion.h"
#include "criterion/new/assert.h"
#include "../include/utils.h"

Test(utils, get_file_extension_test)
{
    #ifdef _WIN32
        cr_assert_str_eq(get_file_extension("\\path\\to\\file.pdf"), "pdf");
        cr_assert_str_eq(get_file_extension("\\path\\to\\file"), "");
        cr_assert_str_eq(get_file_extension("\\path\\to\\file.archive.tar.gz"), "archive.tar.gz");
        cr_assert_str_eq(get_file_extension("\\path\\to\\.hiddenfile"), "");
    #elif __unix__
        cr_assert_str_eq(get_file_extension(""), "");
        cr_assert_str_eq(get_file_extension("file"), "");
        cr_assert_str_eq(get_file_extension("file.txt"), "txt");
        cr_assert_str_eq(get_file_extension("archive.tar.gz"), "tar.gz");
        cr_assert_str_eq(get_file_extension(".hiddenfile"), "");
        cr_assert_str_eq(get_file_extension("file."), "");
        cr_assert_str_eq(get_file_extension("/path/to/file.pdf"), "pdf");
        cr_assert_str_eq(get_file_extension("/path/to/file"), "");
        cr_assert_str_eq(get_file_extension("/path/to/file.archive.tar.gz"), "archive.tar.gz");
        cr_assert_str_eq(get_file_extension("/path/to/.hiddenfile"), "");
    #endif
}

Test(utils, get_path_without_extension_test)
{
    #ifdef _WIN32
    #elif __unix__
        cr_assert_str_eq(get_path_without_extension("file.txt"), "file");
        cr_assert_str_eq(get_path_without_extension("/path/to/file.txt"), "/path/to/file");
        cr_assert_str_eq(get_path_without_extension("file"), "file");
        cr_assert_str_eq(get_path_without_extension("archive.tar.gz"), "archive.tar");
        cr_assert_str_eq(get_path_without_extension("/folder.subfolder/file.ext"), "/folder.subfolder/file");
        cr_assert_str_eq(get_path_without_extension(""), "");
        cr_assert_str_eq(get_path_without_extension("file."), "file");
        cr_assert_str_eq(get_path_without_extension("/path/to/file."), "/path/to/file");
    #endif
}