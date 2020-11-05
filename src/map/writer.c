#include "map.h"
#include "bsq.h"

int native_map_write(map_t *map, square_t *square)
{
    char *location;

    if (!map || !map->data || !square || (!square->location && square->size))
        return -1;
    else if (!square->size)
        return 0;
    location = square->location;
    for (size_t y = 0; y < square->size; y++) {
        for (size_t x = 0; x < square->size; x++, location--)
            *location = CHAR_FILL;
        location -= map->line_size - square->size;
    }
    return 0;
}

int map_write(map_t *map, square_t *square)
__attribute__ ((weak, alias ("native_map_write")));
