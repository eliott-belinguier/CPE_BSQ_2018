#include <criterion/criterion.h>

#include "malloc.h"

#include "map.h"
#include "bsq.h"

Test(bsq_solver, correct_parameter)
{
    map_t map = {0, (char [12]) {"...\n...\n.o.\n"}, 12, 3, 4};
    square_t square = {0, 0};

    cr_assert_eq(bsq_solve(&map, &square), 0);
    cr_assert_eq(map.ptr, 0);
    cr_assert_str_eq(map.data, "...\n...\n.o.\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, map.data + 5);
    cr_assert_eq(square.size, 2);
}

Test(bsq_solver, bad_parameter)
{
    square_t square = {0, 0};

    cr_assert_eq(bsq_solve(0, &square), -1);
    cr_assert_eq(square.location, 0);
    cr_assert_eq(square.size, 0);
}

Test(bsq_solver, bad_parameter_1)
{
    map_t map = {0, (char [12]) {"...\n...\n.o.\n"}, 12, 3, 4};

    cr_assert_eq(bsq_solve(&map, 0), -1);
    cr_assert_eq(map.ptr, 0);
    cr_assert_str_eq(map.data, "...\n...\n.o.\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
}

Test(bsq_solver, bad_character)
{
    map_t map = {0, (char [12]) {"...\n.x.\n...\n"}, 12, 3, 4};
    square_t square = {0, 0};

    cr_assert_eq(bsq_solve(&map, &square), -1);
    cr_assert_eq(map.ptr, 0);
    cr_assert_neq(map.data, 0);
    cr_assert_str_eq(map.data, "...\n.x.\n...\n");
}

Test(bsq_solver, libc_crash)
{
    map_t map = {0, (char [12]) {"...\n...\n.o.\n"}, 12, 3, 4};
    square_t square = {0, 0};

    malloc_error_test = 1;
    cr_assert_eq(bsq_solve(&map, &square), -1);
    cr_assert_eq(map.ptr, 0);
    cr_assert_str_eq(map.data, "...\n...\n.o.\n");
    cr_assert_eq(map.size, 12);
    cr_assert_eq(map.nb_line, 3);
    cr_assert_eq(map.line_size, 4);
    cr_assert_eq(square.location, 0);
    cr_assert_eq(square.size, 0);
}


