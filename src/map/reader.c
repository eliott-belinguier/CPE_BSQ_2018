#include "file.h"
#include "map.h"

static void local_free_map(map_t **ptr)
{
    map_t *map = *ptr;

    if (!map)
        return;
    free(map->ptr);
    map->ptr = 0;
    map->data = 0;
    map->size = 0;
    map->line_size = 0;
    *ptr = 0;
}

static int check_lines(map_t *map)
{
    size_t length;
    size_t index;

    for (length = 0; map->data[length] && map->data[length] != '\n'; length++);
    map->line_size = length + 1;
    for (index = length; index <= map->size; index += map->line_size)
        if (map->data[index] != '\n')
            return -1;
    index -= map->line_size - 1;
    if (index != map->size || index / map->line_size != map->nb_line)
        return -1;
    return 0;
}

static int get_first_number(map_t *map)
{
    char *data;
    size_t result = 0;
    size_t i;

    data = map->ptr;
    for (i = 0; data[i] && data[i] != '\n' && data[i] >= '0' && data[i] <= '9';
    i++) {
        result *= 10;
        result += data[i] - '0';
    }
    if (!data[i] || data[i] != '\n')
        return -1;
    map->nb_line = result;
    map->data = map->ptr + i + 1;
    map->size = map->size - ((size_t) map->data) + ((size_t) map->ptr);
    return (0);
}

int native_map_read(const char *file_map, map_t *map)
{
    map_t *current __attribute__ ((cleanup (local_free_map))) = map;

    if (!file_map || !map)
        return -1;
    current->ptr = file_read_all(file_map, &map->size);
    if (!current->ptr)
        return -1;
    if (get_first_number(map) == -1 || check_lines(map) == -1)
        return -1;
    current = 0;
    return 0;
}

int map_read(const char *file_map, map_t *map)
__attribute__ ((weak, alias ("native_map_read")));