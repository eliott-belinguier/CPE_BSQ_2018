#include <stdint.h>

#include "map.h"
#include "bsq.h"

static void local_free_ptr(void **ptr)
{
    free(*ptr);
    *ptr = 0;
}

static void local_swap_buffer(uint32_t *buffer[2])
{
    uint32_t *tmp = buffer[0];

    buffer[0] = buffer[1];
    buffer[1] = tmp;
}

static int local_fill_buffer(char *location, uint32_t *buffer[2], size_t size,
square_t *square)
{
    for (size_t i = 0; i < size; i++, location++) {
        if (*location != CHAR_WALL && *location != CHAR_VOID)
            return -1;
        if (*location == CHAR_WALL)
            buffer[0][i] = 0;
        else if (i == 0)
            buffer[0][i] = 1;
        else
            buffer[0][i] = MIN3(buffer[0][i - 1], buffer[1][i - 1],
            buffer[1][i]) + 1;
        if (buffer[0][i] > square->size) {
            square->location = location;
            square->size = buffer[0][i];
        }
    }
    local_swap_buffer(buffer);
    return 0;
}

int native_bsq_solve(map_t *map, square_t *square)
{
    void *ptr __attribute__ ((cleanup (local_free_ptr))) = 0;
    size_t buffer_size;
    char *location;
    uint32_t *buffer[2] = {(void *) 0, (void *) 0};

    if (!map || !square)
        return -1;
    buffer_size = map->line_size - 1;
    ptr = malloc(sizeof(uint32_t) * (buffer_size * 2));
    if (!ptr)
        return -1;
    buffer[0] = (uint32_t *) ptr;
    buffer[1] = (uint32_t *) ptr + buffer_size;
    for (size_t i = 0; i < buffer_size; i++)
        buffer[1][i] = 0;
    location = map->data;
    for (size_t i = 0; i < map->nb_line; i++, location += map->line_size)
        if (local_fill_buffer(location, buffer, buffer_size, square) == -1)
            return -1;
    return 0;
}

int bsq_solve(map_t *map, square_t *square)
__attribute__ ((weak, alias ("native_bsq_solve")));