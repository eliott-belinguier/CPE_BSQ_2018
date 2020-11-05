#ifndef _BSQ_H_
#define _BSQ_H_

#define MIN(a, b)  ((b < a) ? b : a)
#define MIN3(a, b, c) (MIN(MIN(a, b), c))

#define CHAR_FILL 'x'
#define CHAR_WALL 'o'
#define CHAR_VOID '.'

int bsq_solve(map_t *map, square_t *square);

#endif
