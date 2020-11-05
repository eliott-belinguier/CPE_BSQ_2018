#include <stdlib.h>
#include <stdarg.h>

int read_error_test = 0;

int __read(int fd, void *buf, size_t count);

ssize_t test_read(int fd, void *buf, size_t count)
{
    if (read_error_test == -1 || read_error_test > 0) {
        read_error_test -= (read_error_test > 0) ? 1 : 0;
        return -1;
    } else if (read_error_test < -1)
        read_error_test += (read_error_test == -2) ? 3 : 1;
    return __read(fd, buf, count);
}

ssize_t read(int fd, void *buf, size_t count)
__attribute__((alias ("test_read")));