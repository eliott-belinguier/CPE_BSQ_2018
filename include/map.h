#ifndef _BSQ_MAP_H_
#define _BSQ_MAP_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct square_s {
    char *location;
    uint32_t size;
} square_t;

typedef struct map_s {
    void *ptr;
    char *data;
    size_t size;
    size_t nb_line;
    size_t line_size;
} map_t;

int map_read(const char *file_map, map_t *map);
int map_write(map_t *map, square_t *square);

#endif
