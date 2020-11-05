#include <unistd.h>

#include "map.h"
#include "bsq.h"

static void local_free_map(map_t *map)
{
    free(map->ptr);
    map->ptr = 0;
    map->data = 0;
    map->size = 0;
    map->line_size = 0;
}

int main(int argc, char **argv)
{
    map_t map __attribute__ ((cleanup (local_free_map))) = {0};
    square_t square = {0};

    if (argc != 2 || map_read(argv[1], &map) == -1
    || bsq_solve(&map, &square) == -1 || map_write(&map, &square) == -1)
        return 84;
    write(1, map.data, map.size);
    return 0;
}