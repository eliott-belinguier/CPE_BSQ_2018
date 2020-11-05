#include <stdlib.h>
#include <stdarg.h>

int open_error_test = 0;

int __open(const char *pathname, int oflag, ...);

int test_open(const char *pathname, int oflat, ...)
{
    va_list list;
    mode_t mode;

    va_start(list, oflat);
    mode = va_arg(list, mode_t);
    va_end(list);
    if (open_error_test == -1 || open_error_test > 0) {
        open_error_test -= (open_error_test > 0) ? 1 : 0;
        return -1;
    } else if (open_error_test < -1)
        open_error_test += (open_error_test == -2) ? 3 : 1;
    return __open(pathname, oflat, mode);
}

int open(const char *pathname, int oflat, ...)
__attribute__((alias ("test_open")));