#include <criterion/criterion.h>

#include "malloc.h"

#include "map.h"

static void local_free_map(map_t *map)
{
    free(map->ptr);
    *map = (map_t) {0, 0, 0, 0, 0};
}

Test(map_reader, parameter_first_null)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read(0, &map), -1);
    cr_assert_eq(map.ptr, 0);
    cr_assert_eq(map.data, 0);
    cr_assert_eq(map.size, 0);
    cr_assert_eq(map.nb_line, 0);
    cr_assert_eq(map.line_size, 0);
    local_free_map(&map);
}

Test(map_reader, parameter_second_null)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("resource/mouli_maps/intermediate_map_34_137_empty",
    0), -1);
    cr_assert_eq(map.ptr, 0);
    cr_assert_eq(map.data, 0);
    cr_assert_eq(map.size, 0);
    cr_assert_eq(map.nb_line, 0);
    cr_assert_eq(map.line_size, 0);
    local_free_map(&map);
}

Test(map_reader, correct_parameter)
{
    map_t map __attribute__ ((cleanup (local_free_map))) = {
    0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps/"
    "intermediate_map_34_137_empty", &map), 0);
    cr_assert_neq(map.ptr, 0, "Error ptr is null");
    cr_assert_eq(map.data, (map.ptr + 4), "Error data incorrect value got %lu"
    " except %d", map.data - (char *) map.ptr, 4);
    cr_assert_eq(map.size, 4795, "Error incorrect size got %lu except %u",
    map.size, 4795);
    cr_assert_eq(map.nb_line, 137, "Error incorrect number line got %lu except"
    " %u", map.nb_line, 137);
    cr_assert_eq(map.line_size, 35, "Error incorrect line size got %lu except"
    " %u", map.line_size, 35);
}

Test(map_reader, libc_crash)
{
    map_t map __attribute__ ((cleanup (local_free_map))) = {
    0, 0, 0, 0, 0};

    malloc_error_test = 1;
    cr_assert_eq(map_read("tests/resource/mouli_maps/"
    "intermediate_map_34_137_empty", &map), -1);
    cr_assert_eq(map.ptr, 0);
    cr_assert_eq(map.data, 0);
    cr_assert_eq(map.size, 0);
    cr_assert_eq(map.nb_line, 0);
    cr_assert_eq(map.line_size, 0);
}

Test(map_reader, no_first_line)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_no_first_line", &map), -1);
    local_free_map(&map);
}

Test(map_reader, no_break_line)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_no_break_line", &map), -1);
    local_free_map(&map);
}

Test(map_reader, bad_break_line_2)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_no_break_line_3", &map), -1);
    local_free_map(&map);
}

Test(map_reader, bad_break_line)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_no_break_line_2", &map), -1);
    local_free_map(&map);
}

Test(map_reader, incorrect_number)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_incorrect_number", &map), -1);
    local_free_map(&map);
}

Test(map_reader, bad_number)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_bad_number", &map), -1);
    local_free_map(&map);
}

Test(map_reader, bad_number_2)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_bad_number_2", &map), -1);
    local_free_map(&map);
}

Test(map_reader, juste_number)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_just_number", &map), -1);
    local_free_map(&map);
}

Test(map_reader, bad_character)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_character", &map), -1);
    local_free_map(&map);
}

Test(map_reader, bad_map)
{
    map_t map = {0, 0, 0, 0, 0};

    cr_assert_eq(map_read("tests/resource/mouli_maps_error/"
    "intermediate_map_bad", &map), -1);
    local_free_map(&map);
}