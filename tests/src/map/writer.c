#include <criterion/criterion.h>

#include "map.h"

Test(map_writer, correct_parameter)
{
    map_t map = {0, (char [12]) {"...\n...\n...\n"}, 12, 3, 4};
    square_t square = {map.data + 10, 3};

    cr_assert_eq(map_write(&map, &square), 0);
    cr_assert_neq(map.data, 0);
    cr_assert_str_eq(map.data, "xxx\nxxx\nxxx\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, map.data + 10);
    cr_assert_eq(square.size, 3);
}

Test(map_writer, bad_parater_null)
{
    char data[12] = "xxx\nxxx\nxxx\n";
    square_t square = {data + 10, 3};

    cr_assert_eq(map_write(0, &square), -1);
    cr_assert_str_eq(data, "xxx\nxxx\nxxx\n");
    cr_assert_eq(square.location, data + 10);
    cr_assert_eq(square.size, 3);
}

Test(map_writer, bad_parater_null_1)
{
    map_t map = {0, 0, 12, 3, 4};
    square_t square = {map.data + 10, 3};

    cr_assert_eq(map_write(&map, &square), -1);
    cr_assert_eq(map.data, 0);
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, map.data + 10);
    cr_assert_eq(square.size, 3);
}

Test(map_writer, bad_parater_null_2)
{
    map_t map = {0, (char [12]) {"...\n...\n...\n"}, 12, 3, 4};

    cr_assert_eq(map_write(&map, 0), -1);
    cr_assert_neq(map.data, 0);
    cr_assert_str_eq(map.data, "...\n...\n...\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
}

Test(map_writer, no_square)
{
    map_t map = {0, (char [12]) {"...\n...\n...\n"}, 12, 3, 4};
    square_t square = {map.data + 10, 0};

    cr_assert_eq(map_write(&map, &square), 0);
    cr_assert_neq(map.data, 0);
    cr_assert_str_eq(map.data, "...\n...\n...\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, map.data + 10);
    cr_assert_eq(square.size, 0);
}

Test(map_writer, no_square_1)
{
    map_t map = {0, (char [12]) {"...\n...\n...\n"}, 12, 3, 4};
    square_t square = {0, 0};

    cr_assert_eq(map_write(&map, &square), 0);
    cr_assert_neq(map.data, 0);
    cr_assert_str_eq(map.data, "...\n...\n...\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, 0);
    cr_assert_eq(square.size, 0);
}

Test(map_writer, no_square_2)
{
    map_t map = {0, (char [12]) {"...\n...\n...\n"}, 12, 3, 4};
    square_t square = {0, 3};

    cr_assert_eq(map_write(&map, &square), -1);
    cr_assert_neq(map.data, 0);
    cr_assert_str_eq(map.data, "...\n...\n...\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, 0);
    cr_assert_eq(square.size, 3);
}


