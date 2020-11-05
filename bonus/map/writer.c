#include "map.h"
#include "bsq.h"

#include "string.h"

static int set_color_map_data(char *new_data, map_t *map, square_t *square)
{
    size_t index = square->location
    - ((square->size - 1) * (map->line_size + 1)) - map->data;

    memcpy(new_data, map->data, index);
    for (size_t i = 1; i <= square->size; i++) {
        memcpy(new_data + index, "\033[31m", 5);
        index += 5;
        memset(new_data + index, CHAR_FILL, square->size);
        index += square->size;
        memcpy(new_data + index, "\033[39m", 5);
        index += 5;
        memcpy(new_data + index, map->data + index - (10 * i),
        map->line_size - square->size);
        index += map->line_size - square->size;
    }
    memcpy(new_data + index , map->data + index - (10 * square->size),
    map->size - index + (10 * square->size));
    return 0;
}

static int bonus_map_write(map_t *map, square_t *square)
{
    size_t new_size;
    char *new_data;

    if (!map || !map->data || !square || (!square->location && square->size))
        return -1;
    else if (!square->size)
        return 0;
    new_size = map->size + (square->size * 10) + 1;
    new_data = malloc(new_size);
    if (!new_data)
        return -1;
    set_color_map_data(new_data, map, square);
    free(map->ptr);
    map->ptr = new_data;
    map->data = map->ptr;
    map->size = new_size;
    return 0;
}

int map_write(map_t *map, square_t *square)
__attribute__ ((alias ("bonus_map_write")));
