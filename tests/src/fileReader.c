#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/stat.h>

#include "malloc.h"
#include "open.h"
#include "read.h"

#include "file.h"

static int is_correct_file_path(const char *file_path)
{
    char *content = file_read_all(file_path, 0);
    int result = content != 0;

    free(content);
    return result;
}

static void test_correct_file_path_read(const char *file_path)
{
    FILE *file;
    struct stat stats = {0};
    char *result;
    size_t size;

    if (stat(file_path, &stats) == -1) {
        cr_assert(0, "can't view stats of %s file", file_path);
        return;
    }
    file = fopen(file_path, "r");
    if (!file) {
        cr_assert(0, "can't open %s file", file_path);
        return;
    }
    result = file_read_all(file_path, &size);
    if (!result) {
        fclose(file);
        cr_assert(0, "The function returns null value for %s file", file_path);
        return;
    }
    cr_assert_eq(size, (size_t) stats.st_size,
    "Incorrect size for %s file got %ld excepted %ld", file_path, size,
    stats.st_size);
    cr_assert_file_contents_eq_str(file, result,
    "There are some differences for %s file", file_path);
    free(result);
}

static void test_correct_file_path(const char *file_path)
{
    cr_assert(is_correct_file_path(file_path),
    "The function returns a null value for %s file", file_path);
    test_correct_file_path_read(file_path);
}

Test(file_reader, parameter_null)
{
    cr_assert_eq(is_correct_file_path(0), 0);
}

Test(file_reader, parameter_bad)
{
    cr_assert_eq(is_correct_file_path("ffdsfsdfs ''("), 0);
}

Test(file_reader, libc_malloc_crash)
{
    malloc_error_test = 1;
    cr_assert_eq(is_correct_file_path("./Makefile"), 0,
    "Error malloc management");
}

Test(file_reader, libc_open_crash)
{
    open_error_test = 1;
    cr_assert_eq(is_correct_file_path("./Makefile"), 0,
    "Error open management");
}

Test(file_reader, libc_read_crash)
{
    read_error_test = 1;
    cr_assert_eq(is_correct_file_path("./Makefile"), 0,
    "Error read management");
}

Test(file_reader, correct_file_path_map)
{
    test_correct_file_path("./src/fileReader.c");
}

Test(file_reader, correct_file_path_makefile)
{
    test_correct_file_path("./Makefile");
}